


#include "ConfigClass.h"


ConfigClass::ConfigClass(const std::vector<uint64_t>& params,
                         const fs::path& inputName,
                         const fs::path& outputName)

        : inName(inputName)
        , outName(outputName)

        , readT(chrn::milliseconds(params[0]))
        , writeT(chrn::milliseconds(params[1]))

        , moveT(chrn::milliseconds(params[2]))
        , longMoveT(chrn::milliseconds(params[3]))

        , ramLmt(params[4] * 1024 * 1024)
        , bufSz(0)
        , value(0)

{
    calcBufSz();
    maxFileParts();
}


void ConfigClass::calcBufSz()
{
    if (ramLmt < techOps::kMin)
    {
        std::cout << techOps::kRamTooLow << std::endl;
        std::cout << ramLmt;
        exit(1);
    }
    else if (ramLmt < techOps::kMid)
        bufSz = 0.26 * ramLmt  / techOps::kSizeULL;
    else if (ramLmt < techOps::kHigh)
        bufSz = 0.45 * ramLmt  / techOps::kSizeULL;
    else if (ramLmt < techOps::kExtrm)
        bufSz = 0.56 * ramLmt  / techOps::kSizeULL;
    else
        bufSz = 0.68 * ramLmt  / techOps::kSizeULL;
}

void ConfigClass::maxFileParts()
{
    value = ((ramLmt / 1024) - 3072) / (8.3);      // max value of files
}