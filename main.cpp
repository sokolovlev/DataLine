#include <iostream>
#include "ManagerClass.h"
#include "cstdint"
#include <istream>
#include "ConfigClass.h"
#include "techOps.h"


int main()
{
    constexpr int len = 6;
    std::ifstream config("input/config.csv");

    std::vector<uint64_t> tokens(len);
    if (config.is_open())
    {
        constexpr int parametersNum = 5;
        std::string token;
        for (int i = 0; i < parametersNum; i++)
        {
            std::getline(config,token,',');
            tokens[i] = std::stoull(token);
        }
        config.close();
    }
    else
    {
        std::cout << "config Error";
        exit(1);
    }

    std::string inName;
    std::string outName;

    std::cout << "input file name\n";
    std::cin >> inName;

    std::cout << "output file name\n";
    std::cin >> outName;

    ConfigClass cfg(tokens,inName,outName);

    size_t bufSz = techOps::calcBufSz(cfg);
    cfg.setBufSz(bufSz);

    ManagerClass manager(cfg);
    manager.run();

    return 0;
}