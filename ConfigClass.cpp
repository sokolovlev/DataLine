//
// Created by Lev on 12.05.2026.
//

#include "ConfigClass.h"


ConfigClass::ConfigClass(const std::vector<uint64_t>& cfg,const fs::path& inputName,
                         const fs::path& outputName)
{
    inName = inputName;
    outName = outputName;

    readT = cfg[0];
    writeT = cfg[1];

    moveT = cfg[2];
    longMoveT = cfg[3];

    ramLmt = cfg[4];
    bufSz = 0;
}

void ConfigClass::setBufSz(uint64_t len)
{
    bufSz = len;
}

void ConfigClass::setRTime(uint64_t readTime)
{
    readT = readTime;
}

uint64_t ConfigClass::getBufSz() const
{
    return bufSz;
}

uint64_t ConfigClass::getRTime() const
{
    return readT;
}

uint64_t ConfigClass::getWTime() const
{
    return writeT;
}

uint64_t ConfigClass::getMTime() const
{
    return moveT;
}

uint64_t ConfigClass::getLMTime() const
{
    return longMoveT;
}

uint64_t ConfigClass::getRamLmt() const
{
    return ramLmt;
}
