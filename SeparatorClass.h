//
// Created by Lev on 07.05.2026.
//

#ifndef UNTITLED26_SEPARATORCLASS_H
#define UNTITLED26_SEPARATORCLASS_H


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
#include "ConfigClass.h"


namespace fs = std::filesystem;

class SeparatorClass
{
private:

    inline static constexpr std::string_view notFound = "File not found: ";
    inline static constexpr std::string endName = "SortedPartN";  //end of partedName

    bool success;
    std::mutex bufMtx;

    std::condition_variable cv_r;
    std::condition_variable cv_w;

    std::atomic<bool> rGo = true;
    std::atomic<bool> wGo = false;
    std::atomic<bool> stopRead = false;

    fs::path inDir;
    fs::path tDir;
    fs::path outDir;

    fs::path inName;
    fs::path outName;

    std::vector<uint64_t> shrdBuf;
    uint64_t bufSz;

public:

    SeparatorClass(const ConfigClass *config);
    void ctrl();
    void read();

    void write();
    bool is_success() const;
};

#endif //UNTITLED26_SEPARATORCLASS_H