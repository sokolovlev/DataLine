


#include "ManagerClass.h"
#include "SeparatorClass.h"
#include "ConfigClass.h"
#include "techOps.h"


ManagerClass::ManagerClass(const ConfigClass& configLink)

            : config(configLink)
            , inName(config.getInName())

            , ramLmt(config.getRamLmt())
            , bufSz(config.getBufSz())

{setLimit(ramLmt);}

uint64_t ManagerClass::getLen() const  // number of data (without delimiters and '\n' symbols)
{
    std::ifstream file(techOps::inputDir / inName);
    if (!file.is_open())
    {
        std::cerr << techOps::kFileOpenError << techOps::inputDir / inName << std::endl;
        exit(1);
    }

    uint64_t cnt = 0;
    uint64_t len = 0;
    char ch;

    while (file.get(ch))
    {
        if (ch == techOps::kDelimiter)
        {
            if (len > techOps::kSizeULL)
            {
                std::cout << techOps::kDataUnitTooBig << std::endl;
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
    uint64_t value = config.getValue();
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
            std::cout << techOps::kSuccess << std::endl;
    }
    else
        std::cout << techOps::kFailed << std::endl;
}