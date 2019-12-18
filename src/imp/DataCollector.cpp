  
#ifndef DATA_DATACOLLECTOR_CPP
#define DATA_DATACOLLECTOR_CPP

#include <iostream>
#include <fstream>
#include <string>

#include "controllers/basicbot/basicbot.h"

DataCollector::DataCollector(){}
DataCollector::~DataCollector(){}

void DataCollector::CollectData(Warehouse* wh)
{
    // Define sepeartor for data
    char seperator{44};

    // create output file for general data
    output.open ("data-general.txt");
    // Collect all general data
    output << wh->em->warehouseLength << seperator;
    output << wh->em->warehouseHeight << seperator;
    int circumference = 2 * (wh->em->warehouseLength + wh->em->warehouseHeight); // Omkreds
    output << circumference << seperator;
    output << wh->bots.size() << seperator;
    output << wh->pm.pods.size() << seperator;
    output << wh->om.orders.size() << seperator;
    
    // Iterate through all orders and count all completed and not completed orders
    int completed = 0, notCompleted = 0;
    for (int i=0;i<wh->om.orders.size(); i++)
    {
        if (wh->om.orders[i]->timestamp_completed != -1)
        {
            completed++;
        } else {
            notCompleted++;
        }
    }
    output << completed << seperator;
    output << notCompleted;
    output << std::endl;

    // close output-file
    output.close();

    // create output file for robots data
    output.open ("data-robots.txt");
    // Collect and write all data for each bot
    for (int i=0; i<wh->bots.size(); i++)
    {
        Basicbot* b = wh->bots[i];
        output << i << seperator;
        output << b->ticksIdle << seperator;
        output << b->ticksMoveforward << seperator;
        output << b->ticksTurnleft << seperator;
        output << b->ticksTurnright << seperator;
        output << b->ticksTurn180 << seperator;
        output << b->ticksPickuppod << seperator;
        output << b->ticksPutdownpod << seperator;
        output << b->ticksIgnore<< seperator;
        output << b->ticksWait;
        output << std::endl;
    }

    // close output-file
    output.close();
}

/*
void DataCollector::WriteLineToFile(std::string x)
{
    
}*/


#endif