//
// Created by Lev on 11.05.2026.
//

#ifndef DATALINE_MERGESORTEDCLASS_H
#define DATALINE_MERGESORTEDCLASS_H


#include <filesystem>
#include <fstream>
#include <iostream>

#include <vector>
#include <queue>
#include "ConfigClass.h"

namespace fs = std::filesystem;
using cfg = ConfigClass;

class MergeSortedClass
{
private:
    fs::path inDir;
    fs::path outDir;

    fs::path inName;
    fs::path outName;

    uint64_t bufSz;
    bool success;

    inline static constexpr std::string_view outputName = "sorted_result.csv";
    inline static constexpr std::string_view inputIsEmpty = "Input directory is empty";
    inline static constexpr std::string_view createOutputFailed = "error make outputFile\n";
public:
    MergeSortedClass(const fs::path& inputDir, const fs::path& outputDir,
        const cfg* config, const fs::path& inputName, const fs::path& outputName);
    ~MergeSortedClass();

    void run();
    void mergeFiles(std::vector<std::ifstream>& files) const;
    bool readNextNum(std::ifstream& file, uint64_t& value) const;
    bool is_success() const;
};

#endif //DATALINE_MERGESORTEDCLASS_H