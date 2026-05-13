//
// Created by Lev on 12.05.2026.
//

#ifndef DATALINE_CONFIGCLASS_H
#define DATALINE_CONFIGCLASS_H

#include <cstdint>
#include "vector"
#include <filesystem>

namespace fs = std::filesystem;

class ConfigClass
{
private:
    fs::path inDir = "input";
    fs::path outDir = "output";
    fs::path tDir = "tech";

    fs::path inName;
    fs::path outName;

    uint64_t readT;      //Ms
    uint64_t writeT;     //Ms

    uint64_t longMoveT;  //Ms    relocate for x positions (x > 1)
    uint64_t moveT;      //Ms  relocate for 1 position

    uint64_t ramLmt;      //MB
    uint64_t bufSz;

public:

    ConfigClass(const std::vector<uint64_t>& params,const fs::path& inputName,
        const fs::path& outputName);

    void setBufSz(uint64_t len) {bufSz = len;}
    void setRTime(uint64_t readTime) {readT = readTime;}

    fs::path getInName() const {return inName;}
    fs::path getOutName() const {return outName;}

    fs::path getInDir() const {return inDir;}
    fs::path getOutDir() const {return outDir;}
    fs::path getTDir() const {return tDir;}

    uint64_t getBufSz() const {return bufSz;}
    uint64_t getRTime() const {return readT;}        //Ms
    uint64_t getWTime() const {return writeT;}       //Ms

    uint64_t getLMTime()  const {return longMoveT;}  //Ms
    uint64_t getMTime() const {return moveT;}        //Ms
    uint64_t getRamLmt() const {return ramLmt;}      //MB
};


#endif //DATALINE_CONFIGCLASS_H