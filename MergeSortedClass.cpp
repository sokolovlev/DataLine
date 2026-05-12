//
// Created by Lev on 11.05.2026.
//

#include "MergeSortedClass.h"

MergeSortedClass::MergeSortedClass(const std::filesystem::path& inputDirectory, const std::filesystem::path& outputDirectory, ParametersClass* parametersData, const std::filesystem::path& inputName, const std::filesystem::path& outputName)
{
    inputDir = inputDirectory;
    outputDir = outputDirectory;
    bufferLen = parametersData -> getBufferLen();

    inName = inputName;
    outName = outputName;
    success = false;
}

MergeSortedClass::~MergeSortedClass()
{
    if (std::filesystem::exists(inputDir))
    {
        for (const auto& entry : std::filesystem::directory_iterator(inputDir))
            if (std::filesystem::is_regular_file(entry.path()))
                std::filesystem::remove(entry.path());
    }
}

void MergeSortedClass::run()
{
    std::vector<std::ifstream> inputFiles;
    uint64_t num = 0;

    while (true)
    {
        std::filesystem::path sortedName = "SortedPartN" + std::to_string(num++) + ".csv";
        std::filesystem::path inputPath = inputDir / sortedName;
        std::ifstream file(inputPath);

        if (file.is_open())
        {
            file.peek();

            if (file.eof())
                continue;
            else
                inputFiles.push_back(std::move(file));
        }
        else
            break;
    }

    if (inputFiles.empty())
        std::cout << inputIsEmpty << inputDir << std::endl;
    else
        mergeFiles(inputFiles);
    success = true;
}

void MergeSortedClass::mergeFiles(std::vector<std::ifstream>& files) const
{
    using Element = std::pair<uint64_t, size_t>;
    std::priority_queue<Element, std::vector<Element>, std::greater<Element>> minHeap;

    for (size_t i = 0; i < files.size(); i++)
    {
        uint64_t value;
        if (readNextNum(files[i], value))                 //files[i] >> value
            minHeap.push({value, i});
    }

    std::filesystem::path outputPath = outputDir / outName;
    std::ofstream output(outputPath);

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

        uint64_t nextValue;
        if (readNextNum(files[fileIndex],nextValue))
            minHeap.push({nextValue, fileIndex});
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

