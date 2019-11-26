
#include "DataCollector.h"



DataCollector::DataCollector()
{
    // create output-file
    output.open ("output.txt");
    
    

    // foreach bot in bots
        // output << "Writing this to a file.\n";


    // close output-file
    output.close();
}

DataCollector::~DataCollector(){}

void DataCollector::WriteLineToFile(std::string x)
{
    
}