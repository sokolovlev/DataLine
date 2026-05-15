


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
{

}