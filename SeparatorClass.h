//
// Created by Lev on 07.05.2026.
//

#ifndef UNTITLED26_READERCLASS_H
#define UNTITLED26_READERCLASS_H


#include <thread>
#include <mutex>
#include <condition_variable>
#include "iostream"
#include <fstream>
#include <cstdint>
#include <vector>
#include <filesystem>
#include <atomic>
#include <algorithm>
#include "ParametersClass.h"

class SeparatorClass
{
private:

    inline static constexpr std::string_view notFound = "File not found: ";
    inline static constexpr std::string endName = "SortedPartN";  //end of partedName
    bool success;
    std::mutex bufferMutex;
    std::condition_variable cv_reader;
    std::condition_variable cv_writer;

    std::atomic<bool> readerGo = true;
    std::atomic<bool> writerGo = false;
    std::atomic<bool> stopRead = false;

    std::filesystem::path inputDir;
    std::filesystem::path outputDir;

    std::filesystem::path inName;
    std::filesystem::path outName;

    std::vector<uint64_t> sharedBuffer;
    uint64_t bufferLen;
public:
    SeparatorClass(const std::filesystem::path& inputDirectory, const std::filesystem::path& outputDirectory, ParametersClass* parametersData, const uint64_t bufferLength, const std::filesystem::path& inputName, const std::filesystem::path& outputName);
    void controller();
    void read();

    void write();
    bool is_success() const;
};

#endif //UNTITLED26_READERCLASS_H