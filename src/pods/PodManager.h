#ifndef PODMANAGER_H
#define PODMANAGER_H

#include <map>

#include <argos3/core/utility/logging/argos_log.h>

#include "Pod.h"

class PodManager
{
private:
    std::map<int, Pod> m_Pods; // TODO: laves om til vector?
    int m_podCount;

    Pod CreatePod(int);
    bool DeletePod();

public:
    PodManager();
    PodManager(int numOfPods);
    ~PodManager();

    Pod GetPod(int podId);
    int GetCount();
};

PodManager::PodManager(){}

PodManager::PodManager(int numOfPods)
{
    m_podCount = 0;

    for (int i=0; i<numOfPods; i++)
    {
        argos::LOG << "Pod count: " << GetCount() << std::endl; //For testing TODO: del
        m_Pods.insert(
            std::pair<int, Pod>
                (m_podCount, CreatePod(m_podCount)));
        m_podCount++;
    };
}

PodManager::~PodManager(){}

Pod PodManager::CreatePod(int nextIndex)
{
    Pod newPod = Pod(nextIndex);
    return newPod;
};

Pod PodManager::GetPod(int podId)
{
    return m_Pods[podId];
};

int PodManager::GetCount(){
    return m_podCount;
}


#endif
