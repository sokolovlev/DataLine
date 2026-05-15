


#ifndef DATALINE_CONFIGCLASS_H
#define DATALINE_CONFIGCLASS_H

#include <cstdint>
#include <vector>
#include <filesystem>
#include "techOps.h"

namespace fs = std::filesystem;
namespace chrn = std::chrono;

class ConfigClass
{
private:
    const fs::path inName;
    const fs::path outName;

    const chrn::milliseconds readT;      //Ms
    const chrn::milliseconds writeT;     //Ms

    const chrn::milliseconds moveT;      //Ms  relocate for 1 position
    const chrn::milliseconds longMoveT;  //Ms    relocate for x positions (x > 1)

    uint64_t ramLmt;                     //MB
    uint64_t bufSz;
    uint64_t value;

    void calcBufSz();
    void maxFileParts();
public:
    ConfigClass(const std::vector<uint64_t>& params,
                const fs::path& inputName,
                const fs::path& outputName);

    [[nodiscard]] fs::path getInName() const {return inName;}
    [[nodiscard]] fs::path getOutName() const {return outName;}

    [[nodiscard]] uint64_t getBufSz() const {return bufSz;}
    [[nodiscard]] chrn::milliseconds getRTime() const {return readT;}        //Ms
    [[nodiscard]] chrn::milliseconds getWTime() const {return writeT;}       //Ms

    [[nodiscard]] chrn::milliseconds getLMTime()  const {return longMoveT;}  //Ms
    [[nodiscard]] chrn::milliseconds getMTime() const {return moveT;}        //Ms
    [[nodiscard]] uint64_t getRamLmt() const {return ramLmt;}                //MB
    [[nodiscard]] uint64_t getValue() const {return value;}
};


#endif //DATALINE_CONFIGCLASS_H