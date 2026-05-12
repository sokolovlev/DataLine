//
// Created by Lev on 11.05.2026.
//

#include "MergeSortedClass.h"

MergeSortedClass::MergeSortedClass(const fs::path& inputDir, const fs::path& outputDir,
    const cfg* config, const fs::path& inputName, const fs::path& outputName)
{
    inDir = inputDir;
    outDir = outputDir;
    bufSz = config -> getBufSz();

    inName = inputName;
    outName = outputName;
    success = false;
}

MergeSortedClass::~MergeSortedClass()
{
    if (fs::exists(inDir))
    {
        using dirIter = std::filesystem::directory_iterator;
        for (const auto& entry : dirIter(inDir))
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

    for (size_t i = 0; i < files.size(); i++)
    {
        uint64_t value;
        if (readNextNum(files[i], value))
            minHeap.push({value, i});
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

        output << value;
        isFirst = false;

        uint64_t nextVal;
        if (readNextNum(files[fileIndex],nextVal))
            minHeap.push({nextVal, fileIndex});
    }
    output.close();
}

bool MergeSortedClass::readNextNum(std::ifstream& file, uint64_t& value) const
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

