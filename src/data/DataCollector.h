#ifndef DATA_DATACOLLECTOR_H
#define DATA_DATACOLLECTOR_H

#include <iostream>
#include <fstream>
#include <string>

class DataCollector
{
private:
    std::ofstream output;

    
public:
    DataCollector();
    ~DataCollector();

    void WriteLineToFile(std::string x);
};


#endif