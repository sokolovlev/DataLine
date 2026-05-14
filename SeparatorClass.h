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
#include "techOps.h"


namespace fs = std::filesystem;
namespace chrn = std::chrono;

class SeparatorClass
{
private:
    bool success;
    std::mutex bufMtx;

    std::condition_variable cv_r;
    std::condition_variable cv_w;

    std::atomic<bool> rGo = true;
    std::atomic<bool> wGo = false;
    std::atomic<bool> stopRead = false;

    const fs::path inDir;
    const fs::path tDir;
    const fs::path outDir;

    const fs::path inName;
    const fs::path outName;

    std::vector<uint64_t> shrdBuf;
    uint64_t bufSz;

    const chrn::milliseconds READ_TIME;
    const chrn::milliseconds WRITE_TIME;
    const chrn::milliseconds MOVE_TIME;
    const chrn::milliseconds LONG_MOVE_TIME;

public:

    explicit SeparatorClass(const ConfigClass& config);
    void ctrl();
    void read();

    void write();
    [[nodiscard]] bool is_success() const;
};

#endif //UNTITLED26_SEPARATORCLASS_H