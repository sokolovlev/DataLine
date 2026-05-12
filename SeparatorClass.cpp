//
// Created by Lev on 07.05.2026.
//

#include "SeparatorClass.h"

SeparatorClass::SeparatorClass(const fs::path& inputDir, const fs::path& outputDir,
    const cfg* config ,uint64_t bufSize, const fs::path& inputName, const fs::path& outputName)
{
    inDir = inputDir;
    outDir = outputDir;

    inName = inputName;
    outName = outputName;

    bufSz = bufSize;
    shrdBuf.resize(bufSz);
    success = false;
}

void SeparatorClass::ctrl()
{
    std::thread readerThread([this]
    {this -> read();});

    std::thread writerThread([this]
    {this -> write();});

    readerThread.join();
    writerThread.join();
    success = true;
}

void SeparatorClass::read()
{
    fs::path inputPath = inDir / inName;
    std::ifstream file(inputPath);

    if (!file.is_open())
    {
        std::cout << notFound << inDir << std::endl;
        exit(1);
    }

    while (true)
    {
        std::string token;
        size_t i = 0;

        std::unique_lock lock(bufMtx);
        cv_r.wait(lock,[this]{return rGo.load() == true && wGo.load() == false;});

        while (std::getline(file, token, ',') && i != bufSz)
        {
            if (!token.empty())
                shrdBuf[i] = std::stoull(token);
            i++;
        }

        rGo = false;
        wGo = true;

        if (file.eof())
        {
            bufSz = i;
            shrdBuf.resize(bufSz);
            stopRead = true;

            cv_w.notify_one();
            break;
        }
        cv_w.notify_one();
    }
}

void SeparatorClass::write()
{
    uint64_t num = 0;
    while (true)
    {
        fs::path partedName = endName + std::to_string(num++) + ".csv";
        fs::path outputPath = outDir / partedName;
        std::ofstream file(outputPath);

        std::unique_lock lock(bufMtx);
        cv_w.wait(lock,[this]{return rGo.load() == false && wGo.load() == true;});

        std::ranges::sort(shrdBuf);
        for (uint64_t i = 0; i < bufSz; i++)
        {
            file << shrdBuf[i];
            if (i + 1 < bufSz)
                file << ',';
        }

        wGo = false;
        rGo = true;

        if (stopRead)
            break;
        cv_r.notify_one();
    }
}

bool SeparatorClass::is_success() const
{
    return success;
}



