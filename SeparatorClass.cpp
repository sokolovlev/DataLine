//
// Created by Lev on 07.05.2026.
//

#include "SeparatorClass.h"

SeparatorClass::SeparatorClass(const std::filesystem::path& inputDirectory, const std::filesystem::path& outputDirectory, ParametersClass* parametersData ,uint64_t bufferLength, const std::filesystem::path& inputName, const std::filesystem::path& outputName)
{
    inputDir = inputDirectory;
    outputDir = outputDirectory;

    inName = inputName;
    outName = outputName;

    bufferLen = bufferLength;
    sharedBuffer.resize(bufferLen);
    success = false;
}

void SeparatorClass::controller()
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
    std::filesystem::path inputPath = inputDir / inName;
    std::ifstream file(inputPath);

    if (!file.is_open())
    {
        std::cout << notFound << inputDir << std::endl;
        exit(1);
    }

    while (true)
    {
        std::string token;
        size_t iterator = 0;

        std::unique_lock lock(bufferMutex);
        cv_reader.wait(lock,[this]{return readerGo.load() == true && writerGo.load() == false;});

        while (std::getline(file, token, ',') && iterator != bufferLen)
        {
            if (!token.empty())
                sharedBuffer[iterator] = std::stoull(token);
            iterator++;
        }

        readerGo = false;
        writerGo = true;

        if (file.eof())
        {
            bufferLen = iterator;
            sharedBuffer.resize(bufferLen);
            stopRead = true;

            cv_writer.notify_one();
            break;
        }
        cv_writer.notify_one();
    }
}

void SeparatorClass::write()
{
    uint64_t num = 0;
    while (true)
    {
        std::filesystem::path partedName = endName + std::to_string(num++) + ".csv";
        std::filesystem::path outputPath = outputDir / partedName;
        std::ofstream file(outputPath);

        std::unique_lock lock(bufferMutex);
        cv_writer.wait(lock,[this]{return readerGo.load() == false && writerGo.load() == true;});

        std::ranges::sort(sharedBuffer);
        for (uint64_t i = 0; i < bufferLen; i++)
        {
            file << sharedBuffer[i];
            if (i + 1 < bufferLen)
                file << ',';
        }

        writerGo = false;
        readerGo = true;

        if (stopRead == true)
            break;
        cv_reader.notify_one();
    }
}

bool SeparatorClass::is_success() const
{
    return success;
}



