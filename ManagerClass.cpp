//
// Created by Lev on 07.05.2026.
//

#include "ManagerClass.h"
#include "SeparatorClass.h"
#include "ConfigClass.h"

ManagerClass::ManagerClass(ConfigClass& configLink)
            : config(configLink)
            , inDir(configLink.getInDir())

            , inName(configLink.getInName())
            , ramLmt(configLink.getRamLmt() * 1024 * 1024)

{
    constexpr int min = 30 * 1024 * 1024;
    constexpr int mid = 40 * 1024 * 1024;

    constexpr int high = 50 * 1024 * 1024;
    constexpr int extrm = 70 * 1024 * 1024;

    constexpr size_t sizeULL = sizeof(uint64_t);
    setLimit(ramLmt);

    if (ramLmt < min)
    {
        std::cout << ramTooLow << std::endl;
        exit(1);
    }
    else if (ramLmt < mid)
        bufSz = 0.26 * ramLmt  / sizeULL;
    else if (ramLmt < high)
        bufSz = 0.45 * ramLmt  / sizeULL;
    else if (ramLmt < extrm)
        bufSz = 0.56 * ramLmt  / sizeULL;
    else
        bufSz = 0.68 * ramLmt  / sizeULL;

    config.setBufSz(bufSz);
}

uint64_t ManagerClass::getLen() const  // number of data (without delimiters and '\n' symbols)
{
    constexpr char delimiter = ',';
    constexpr size_t unitLen = sizeof(uint64_t);

    std::ifstream file(inDir / inName);
    if (!file.is_open())
    {
        std::cerr << fileOpenError << inDir / inName << std::endl;
        exit(1);
    }

    uint64_t cnt = 0;
    uint64_t len = 0;
    char ch;

    while (file.get(ch))
    {
        if (ch == delimiter)
        {
            if (len > unitLen)
            {
                std::cout << dataUnitTooBig << std::endl;
                exit(1);
            }
            len = 0;
            cnt++;
        }
        else if (ch != '\n')
            len++;
    }

    cnt++;
    return cnt;
}

bool ManagerClass::isEnoughMemory() const
{
    uint64_t value = ((ramLmt / 1024) - 3072) / (8.3);   // max value of files
    uint64_t fileSz = getLen();
    uint64_t maxBufSz = ceil(fileSz / value);

    if ((fileSz / maxBufSz) < value)
        return true;
    else
        return false;
}

void ManagerClass::run() const
{
    SeparatorClass separator(config);
    separator.ctrl();

    if (separator.is_success())
    {
        MergeSortedClass merge(config);
        merge.run();

        if (merge.is_success())
            std::cout << success << std::endl;
    }
    else
        std::cout << filed << std::endl;
}