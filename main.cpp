#include <iostream>
#include "ManagerClass.h"
#include "cstdint"
#include <istream>
#include "ConfigClass.h"
#include "techOps.h"
#include "techOps.h"

int main()
{
    constexpr int len = 6;
    std::ifstream config(techOps::kConfigPath);

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
        std::cout << techOps::kConfigError;
        exit(1);
    }

    std::string inName;
    std::string outName;

    std::cout << techOps::inputMsg;
    std::cin >> inName;

    std::cout << techOps::outputMsg;
    std::cin >> outName;

    ConfigClass cfg(tokens,inName,outName);

    ManagerClass manager(cfg);
    manager.run();

    return 0;
}