


#ifndef DATALINE_MERGESORTEDCLASS_H
#define DATALINE_MERGESORTEDCLASS_H


#include <filesystem>
#include <fstream>
#include <iostream>
#include <thread>
#include "techOps.h"

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

    const uint64_t bufSz;
    bool success;

    const chrn::milliseconds READ_TIME;
    const chrn::milliseconds WRITE_TIME;
    const chrn::milliseconds MOVE_TIME;
    const chrn::milliseconds LONG_MOVE_TIME;

public:

    explicit MergeSortedClass(const ConfigClass& config);
    ~MergeSortedClass();

    void run();
    void mergeFiles(std::vector<std::ifstream>& files) const;

    static bool readNextNum(std::ifstream& file, uint64_t& value);
    [[nodiscard]] bool is_success() const;
};

#endif //DATALINE_MERGESORTEDCLASS_H