//
// Created by Lev on 12.05.2026.
//

#include "ParametersClass.h"

ParametersClass::ParametersClass(const uint64_t readT, const uint64_t writeT, const uint64_t longMoveT, const uint64_t moveT, const uint64_t ramLim)
{
    readTime = readT;
    writeTime = writeT;

    longMoveTime = longMoveT;
    moveTime = moveT;
    ramLimit = ramLim;
}

uint64_t ParametersClass::getReadTime() const
{
    return readTime;
}

uint64_t ParametersClass::getWriteTime() const
{
    return writeTime;
}

uint64_t ParametersClass::getLongMoveTime() const
{
    return longMoveTime;
}

uint64_t ParametersClass::getMoveTime() const
{
    return moveTime;
}

uint64_t ParametersClass::getRamLimit() const
{
    return ramLimit;
}

void ParametersClass::setBufferLen(uint64_t len)
{
    bufferLen = len;
}
uint64_t ParametersClass::getBufferLen() const
{
    return bufferLen;
}