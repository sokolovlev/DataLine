//
// Created by Lev on 12.05.2026.
//

#include "ManagerClass.h"
#include "ConfigClass.h"

std::filesystem::path inputDir = "input";
std::filesystem::path techDir = "tech";
std::filesystem::path outputDir = "output";

std::filesystem::path inputName = "source.csv";
std::filesystem::path outputName = "tech";

ConfigClass parameters();


ManagerClass manager(inputDir, outputDir,techDir, parameters,inputName,outputName)


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