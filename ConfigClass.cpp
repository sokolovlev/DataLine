//
// Created by Lev on 12.05.2026.
//

#include "ConfigClass.h"


ConfigClass::ConfigClass(const std::vector<uint64_t>& params,const fs::path& inputName,
                         const fs::path& outputName)
{
    inName = inputName;
    outName = outputName;

    readT = params[0];
    writeT = params[1];

    moveT = params[2];
    longMoveT = params[3];

    ramLmt = params[4];
    bufSz = 0;
}