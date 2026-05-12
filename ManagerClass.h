//
// Created by Lev on 07.05.2026.
//

#ifndef DATALINE_MANAGERCLASS_H
#define DATALINE_MANAGERCLASS_H


#include <filesystem>
#include <iostream>
#include "setLimit.h"
#include <atomic>
#include <cstdint>
#include <cmath>
#include "MergeSortedClass.h"
#include "ParametersClass.h"

class ManagerClass
{
private:
    inline static constexpr std::string_view ramTooLow = "for this file ram to small";
    inline static constexpr std::string_view dataUnitTooBig = "Data unit too big, program support csv with (8 bytes) number or smaller";
    inline static constexpr std::string_view fileOpenError = "Cannot open file: ";

    inline static constexpr std::string_view success = "mission complete";
    inline static constexpr std::string_view filed = "something go wrong, we fix this problem in future";

    inline static std::atomic<bool> isContinue{true};

    std::filesystem::path inputDir;
    std::filesystem::path techDir;
    std::filesystem::path outputDir;

    std::filesystem::path inName;
    std::filesystem::path outName;

    size_t bufferLen;
    uint64_t ramLimit;
    ParametersClass *parameters;

public:

    ManagerClass(const std::filesystem::path& inputDirectory, const std::filesystem::path& outputDirectory, const std::filesystem::path& techDirectory, ParametersClass* parametersData, const std::filesystem::path& inputName, const std::filesystem::path& outputName);
    uint64_t getLen() const;

    bool isEnoughMemory() const;
    void run();
};


#endif //DATALINE_MANAGERCLASS_H