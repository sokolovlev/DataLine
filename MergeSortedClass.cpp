//
// Created by Lev on 11.05.2026.
//

#include "MergeSortedClass.h"

MergeSortedClass::MergeSortedClass(const ConfigClass* config)
{
    inDir = config -> getInDir();
    inDir = config -> getTDir();
    outDir = config -> getOutDir();
    bufSz = config -> getBufSz();

    inName = config -> getInName();
    outName = config -> getOutName();
    success = false;

    READ_TIME = config -> getRTime();
    WRITE_TIME = config -> getWTime();
    MOVE_TIME = config -> getMTime();
    LONG_MOVE_TIME = config -> getLMTime();
}

MergeSortedClass::~MergeSortedClass()
{
    if (fs::exists(tDir))
    {
        using dirIter = std::filesystem::directory_iterator;
        for (const auto& entry : dirIter(tDir))
            if (fs::is_regular_file(entry.path()))
                fs::remove(entry.path());
    }
}

void MergeSortedClass::run()
{
    std::vector<std::ifstream> inFiles;
    uint64_t num = 0;

    while (true)
    {
        fs::path sortedN = "SortedPartN" + std::to_string(num++) + ".csv";
        fs::path inPath = inDir / sortedN;
        std::ifstream file(inPath);

        if (file.is_open())
        {
            file.peek();

            if (file.eof())
                continue;
            else
                inFiles.push_back(std::move(file));
        }
        else
            break;
    }

    if (inFiles.empty())
        std::cout << inputIsEmpty << inDir << std::endl;
    else
        mergeFiles(inFiles);
    success = true;
}

void MergeSortedClass::mergeFiles(std::vector<std::ifstream>& files) const
{
    using Element = std::pair<uint64_t, size_t>;
    std::priority_queue<Element, std::vector<Element>, std::greater<Element>> minHeap;

    using  msc = MergeSortedClass;

    for (size_t i = 0; i < files.size(); i++)
    {
        uint64_t value;

        if (msc::readNextNum(files[i], value))
            minHeap.push({value, i});

        std::this_thread::sleep_for(READ_TIME);
    }

    fs::path outPath = outDir / outName;
    std::ofstream output(outPath);

    if (!output.is_open())
    {
        std::cerr << createOutputFailed;
        return;
    }

    bool isFirst = true;
    while (!minHeap.empty())
    {
        auto [value, fileIndex] = minHeap.top();
        minHeap.pop();

        if (!isFirst)
            output << ",";

        std::this_thread::sleep_for(WRITE_TIME);
        output << value;
        isFirst = false;

        uint64_t nextVal;
        if (msc::readNextNum(files[fileIndex],nextVal))
            minHeap.push({nextVal, fileIndex});
    }
    output.close();
}

bool MergeSortedClass::readNextNum(std::ifstream& file, uint64_t& value)
{
    if (!(file >> value))
        return false;

    if (file.peek() == ',')
        file.ignore();

    return true;
}

bool MergeSortedClass::is_success() const
{
    return success;
}

