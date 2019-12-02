#ifndef DATA_DATACOLLECTOR_H
#define DATA_DATACOLLECTOR_H

#include <iostream>
#include <fstream>
#include <string>

#include "src/argos/controllers/basicbot/basicbot.h"

class DataCollector
{
private:
    std::ofstream output;

public:
    DataCollector();
    ~DataCollector();

    void CollectData(std::map<int, Basicbot*> botControllers);
    void WriteLineToFile(std::string x);
};


#endif