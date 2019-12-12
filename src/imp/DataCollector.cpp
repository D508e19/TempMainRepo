#ifndef DATA_DATACOLLECTOR_CPP
#define DATA_DATACOLLECTOR_CPP

#include <iostream>
#include <fstream>
#include <string>

#include "src/argos/controllers/basicbot/basicbot.h"

DataCollector::DataCollector(){}
DataCollector::~DataCollector(){}

void DataCollector::CollectData(std::map<int, Basicbot*> botControllers)
{
        // create output-file
    output.open ("output.txt");

    // foreach bot in bots

    for (int i=0; i<botControllers.size(); i++)
    {
        Basicbot* b = botControllers[i];
        output << "Bot: " << i << " - Ticks idle: "<< b->ticksIdle << std::endl;
        output << "Bot: " << i << " - Ticks moveforward: "<< b->ticksMoveforward << std::endl;
        output << "Bot: " << i << " - Ticks turnleft: "<< b->ticksTurnleft<< std::endl;
        output << "Bot: " << i << " - Ticks turnright: "<< b->ticksTurnright << std::endl;
        output << "Bot: " << i << " - Ticks turn180: "<< b->ticksTurn180 << std::endl;
        output << "Bot: " << i << " - Ticks pickuppod: "<< b->ticksPickuppod << std::endl;
        output << "Bot: " << i << " - Ticks putdownpod: "<< b->ticksPutdownpod << std::endl;
        output << "Bot: " << i << " - Ticks ignore: "<< b->ticksIgnore << std::endl;
        output << "Bot: " << i << " - Ticks wait: "<< b->ticksWait << std::endl;
        output << std::endl;
    }

    // close output-file
    output.close();
}

void DataCollector::WriteLineToFile(std::string x)
{

}

#endif