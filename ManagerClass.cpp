//
// Created by Lev on 07.05.2026.
//

#include "ManagerClass.h"
#include "SeparatorClass.h"
#include "ParametersClass.h"

ManagerClass::ManagerClass(const std::filesystem::path& inputDirectory, const std::filesystem::path& outputDirectory,const std::filesystem::path& techDirectory, ParametersClass* parametersData, const std::filesystem::path& inputName, const std::filesystem::path& outputName)
{
    constexpr int minRam = 30 * 1024 * 1024;
    constexpr int midRam = 40 * 1024 * 1024;
    constexpr int heightRam = 50 * 1024 * 1024;
    constexpr int bigRam = 70 * 1024 * 1024;

    inputDir = static_cast<std::filesystem::path>(inputDirectory);
    techDir = static_cast<std::filesystem::path>(techDirectory);
    outputDir = static_cast<std::filesystem::path>(outputDirectory);

    inName = static_cast<std::filesystem::path>(inputName);
    outName = static_cast<std::filesystem::path>(outputName);

    ramLimit = parametersData -> getRamLimit() * 1024 * 1024;
    std::cout << ramLimit << std::endl;
    setLimit(ramLimit);

    if (ramLimit < minRam)
    {
        std::cout << ramTooLow << std::endl;
        exit(1);
    }
    else if (ramLimit < midRam)
        bufferLen = 0.26 * ramLimit  / sizeof(uint64_t);
    else if (ramLimit < heightRam)
        bufferLen = 0.45 * ramLimit  / sizeof(uint64_t);
    else if (ramLimit < bigRam)
        bufferLen = 0.56 * ramLimit  / sizeof(uint64_t);
    else
        bufferLen = 0.68 * ramLimit  / sizeof(uint64_t);

    parametersData -> setBufferLen(bufferLen);
    parametersData -> getBufferLen();
}

uint64_t ManagerClass::getLen() const  // number of data (without delimiters and '\n' symbols)
{
    constexpr char delimiter = ',';
    constexpr size_t unitLen = sizeof(uint64_t);

    std::filesystem::path inputFilePath = inputDir / "source.csv";
    std::ifstream file(inputFilePath);

    if (!file.is_open())
    {
        std::cerr << fileOpenError << inputFilePath << std::endl;
        exit(1);
    }

    uint64_t count = 0;
    uint64_t len = 0;
    char ch;

    while (file.get(ch))
    {
        if (ch == delimiter)
        {
            if (len > unitLen)
            {
                std::cout << dataUnitTooBig << std::endl;
                exit(1);
            }
            len = 0;
            count++;
        }
        else if (ch != '\n')
            len++;
    }

    count++;
    return count;
}

bool ManagerClass::isEnoughMemory() const
{
    uint64_t value = ((ramLimit / 1024) - 3072) / (8.3);   // max value of files
    uint64_t FileLen = getLen();
    uint64_t maxBufferLen = ceil(FileLen / value);

    if ((FileLen / maxBufferLen) < value)
        return true;
    else
        return false;
}

void ManagerClass::run()
{
    SeparatorClass separator(inputDir,techDir,parameters,bufferLen,inName,outName);
    separator.controller();

    if (separator.is_success())
    {
        MergeSortedClass merge(techDir,outputDir,parameters,inName,outName);
        merge.run();

        if (merge.is_success())
            std::cout << success << std::endl;
    }
    else
        std::cout << filed << std::endl;
}