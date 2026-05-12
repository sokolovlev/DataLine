//
// Created by Lev on 12.05.2026.
//

#ifndef DATALINE_PARAMETERS_H
#define DATALINE_PARAMETERS_H

#include <cstdint>

class ParametersClass
{
private:
    uint64_t readTime;      //Ms
    uint64_t writeTime;     //Ms

    uint64_t longMoveTime;  //Ms
    uint64_t moveTime;      //Ms

    uint64_t ramLimit;      //MB
    uint64_t bufferLen;

public:

    ParametersClass(const uint64_t readT, const uint64_t writeT, const uint64_t longMoveT, const uint64_t moveT, const uint64_t ramLim);
    void setBufferLen(uint64_t len);
    uint64_t getBufferLen() const;

    uint64_t getReadTime() const;      //Ms
    uint64_t getWriteTime() const;     //Ms

    uint64_t getLongMoveTime() const;  //Ms
    uint64_t getMoveTime() const;      //Ms
    uint64_t getRamLimit() const;      //MB
};


#endif //DATALINE_PARAMETERS_H