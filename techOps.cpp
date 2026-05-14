//
// Created by Lev on 14.05.2026.
//
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
}