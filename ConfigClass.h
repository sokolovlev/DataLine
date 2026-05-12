//
// Created by Lev on 12.05.2026.
//

#ifndef DATALINE_PARAMETERS_H
#define DATALINE_PARAMETERS_H

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

    void setBufSz(uint64_t len);
    void setRTime(uint64_t readTime);

    uint64_t getBufSz() const;
    uint64_t getRTime() const;      //Ms
    uint64_t getWTime() const;     //Ms

    uint64_t getLMTime() const;  //Ms
    uint64_t getMTime() const;      //Ms
    uint64_t getRamLmt() const;      //MB
};


#endif //DATALINE_PARAMETERS_H