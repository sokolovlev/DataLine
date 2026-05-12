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
#include "ParametersClass.h"

class MergeSortedClass
{
private:
    std::filesystem::path inputDir;
    std::filesystem::path outputDir;

    std::filesystem::path inName;
    std::filesystem::path outName;

    uint64_t bufferLen;
    bool success;
    inline static constexpr std::string_view outputName = "sorted_result.csv";
    inline static constexpr std::string_view inputIsEmpty = "Input directory is empty";
    inline static constexpr std::string_view createOutputFailed = "error make outputFile\n";
public:
    MergeSortedClass(const std::filesystem::path& inputDirectory, const std::filesystem::path& outputDirectory, ParametersClass* parametersData, const std::filesystem::path& inName, const std::filesystem::path& outName);
    ~MergeSortedClass();

    void run();
    void mergeFiles(std::vector<std::ifstream>& files) const;
    bool readNextNum(std::ifstream& file, uint64_t& value) const;
    bool is_success() const;
};

#endif //DATALINE_MERGESORTEDCLASS_H