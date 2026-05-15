


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
#include "techOps.h"

namespace fs = std::filesystem;

class ManagerClass
{
private:
    const ConfigClass& config;
    const fs::path inName;
    const uint64_t ramLmt;
    const size_t bufSz;
public:
    explicit ManagerClass(const ConfigClass& configLink);
    [[nodiscard]] uint64_t getLen() const;
    [[nodiscard]] bool isEnoughMemory() const;
    void run() const;
};

#endif //DATALINE_MANAGERCLASS_H