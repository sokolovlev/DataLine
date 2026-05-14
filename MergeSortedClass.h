//
// Created by Lev on 11.05.2026.
//

#ifndef DATALINE_MERGESORTEDCLASS_H
#define DATALINE_MERGESORTEDCLASS_H


#include <filesystem>
#include <fstream>
#include <iostream>
#include <thread>

#include <vector>
#include <queue>
#include "ConfigClass.h"

namespace fs = std::filesystem;
namespace chrn = std::chrono;

class MergeSortedClass
{
private:
    const fs::path inDir;
    const fs::path tDir;
    const fs::path outDir;

    const fs::path inName;
    const fs::path outName;

    uint64_t bufSz;
    bool success;

    inline static constexpr std::string_view inputIsEmpty = "Input directory is empty\n";
    inline static constexpr std::string_view techIsEmpty = "Tech directory is empty\n";
    inline static constexpr std::string_view createOutputFailed = "error make outputFile\n";

    const chrn::milliseconds READ_TIME;
    const chrn::milliseconds WRITE_TIME;
    const chrn::milliseconds MOVE_TIME;
    const chrn::milliseconds LONG_MOVE_TIME;

public:

    MergeSortedClass(const ConfigClass& config);
    ~MergeSortedClass();

    void run();
    void mergeFiles(std::vector<std::ifstream>& files) const;

    static bool readNextNum(std::ifstream& file, uint64_t& value);
    bool is_success() const;
};

#endif //DATALINE_MERGESORTEDCLASS_H