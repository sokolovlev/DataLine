#include <iostream>
#include "ManagerClass.h"
#include "cstdint"
#include <istream>
#include "ParametersClass.h"

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

    ParametersClass parameters(tokens[0],tokens[1],tokens[2],tokens[3],tokens[4]);

    std::string inputDir = "input";
    std::string outputDir = "output";

    std::string inputName;
    std::string outputName;

    std::string techDir = "tech";
    std::cout << "inpute file name";
    std::cin >> inputName;

    std::cout << "outpute file name";
    std::cin >> outputName;

    ManagerClass manager(inputDir,outputDir, techDir, &parameters,inputName,outputName);
    manager.run();

    return 0;
}