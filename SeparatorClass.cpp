


#include "SeparatorClass.h"

SeparatorClass::SeparatorClass(const ConfigClass& config)

            : success(false)
            , inDir(techOps::inputDir)
            , tDir(techOps::techDir)
            , outDir(techOps::outputDir)

            , inName(config.getInName())
            , outName(config.getOutName())
            , bufSz(config.getBufSz())

            , READ_TIME(config.getRTime())
            , WRITE_TIME(config.getWTime())
            , MOVE_TIME(config.getMTime())
            , LONG_MOVE_TIME(config.getLMTime())

{
    shrdBuf.resize(bufSz);
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
        std::cout << techOps::kFileOpenError << inDir << std::endl;
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
            {
                std::this_thread::sleep_for(READ_TIME);
                shrdBuf[i] = std::stoull(token);
            }
            std::this_thread::sleep_for(MOVE_TIME);
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
        fs::path partedName = techOps::kEndNameForSeparated + std::to_string(num++) + ".csv";
        fs::path outputPath = tDir / partedName;
        std::ofstream file(outputPath);

        std::unique_lock lock(bufMtx);
        cv_w.wait(lock,[this]{return rGo.load() == false && wGo.load() == true;});

        std::ranges::sort(shrdBuf);
        for (uint64_t i = 0; i < bufSz; i++)
        {
            file << shrdBuf[i];
            std::this_thread::sleep_for(WRITE_TIME);
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



