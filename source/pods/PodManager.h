#ifndef PODMANAGER_H
#define PODMANAGER_H

#include <argos3/core/utility/logging/argos_log.h>

// #include <iostream> 
// #include <iterator> 
#include <map>

#include "Pod.h"

class PodManager
{
private:
    std::map<int, Pod> Pods;
    int podCount;

    Pod CreatePod(int);
    bool DeletePod();

public:
    PodManager();
    PodManager(int);
    ~PodManager();

    Pod GetPod(int);
    int GetCount();
};

PodManager::PodManager(int numOfPods)
{
    PodManager::podCount = 0;

    for (int i=0; i<numOfPods; i++)
    {
        argos::LOG << "Pod count: " << PodManager::GetCount() << std::endl;
        PodManager::Pods.insert(
            std::pair<int, Pod>
                (PodManager::podCount, PodManager::CreatePod(PodManager::podCount)));
        PodManager::podCount++;
    };
}

PodManager::PodManager(){}

PodManager::~PodManager(){}

Pod PodManager::CreatePod(int nextIndex)
{
    Pod newPod = Pod(nextIndex);
    return newPod;
};

Pod PodManager::GetPod(int index)
{
    return PodManager::Pods[index];
};

int PodManager::GetCount(){
    return PodManager::podCount;
}


#endif