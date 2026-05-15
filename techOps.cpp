


#include "techOps.h"


namespace techOps
{
    size_t calcBufSz(const ConfigClass& config)
    {
        size_t ramLmt = config.getRamLmt();
        size_t bufSz;

        if (ramLmt < kMin)
        {
            std::cout << kRamTooLow << std::endl;
            std::cout << ramLmt;
            exit(1);
        }
        else if (ramLmt < kMid)
            bufSz = 0.26 * ramLmt  / kSizeULL;
        else if (ramLmt < kHigh)
            bufSz = 0.45 * ramLmt  / kSizeULL;
        else if (ramLmt < kExtrm)
            bufSz = 0.56 * ramLmt  / kSizeULL;
        else
            bufSz = 0.68 * ramLmt  / kSizeULL;

        return bufSz;
    }


    uint64_t maxFileParts(const ConfigClass& config)
    {
        const uint64_t ramLmt = config.getRamLmt();
        const uint64_t value = ((ramLmt / 1024) - 3072) / (8.3);      // max value of files
        return value;
    }
}

