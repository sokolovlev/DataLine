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
#include "ConfigClass.h"

namespace fs = std::filesystem;


class ManagerClass
{
private:
    inline static constexpr std::string_view ramTooLow = "for this file ram to small";
    inline static constexpr std::string_view dataUnitTooBig = "Data unit too big, program support csv with (8 bytes) number or smaller";
    inline static constexpr std::string_view fileOpenError = "Cannot open file: ";

    inline static constexpr std::string_view success = "mission complete";
    inline static constexpr std::string_view filed = "something go wrong, we fix this problem in future";

    ConfigClass& config;
    fs::path inDir;
    fs::path inName;

    uint64_t ramLmt;
    size_t bufSz;

public:

    ManagerClass(ConfigClass& configLink);
    uint64_t getLen() const;

    bool isEnoughMemory() const;
    void run() const;
};


#endif //DATALINE_MANAGERCLASS_H