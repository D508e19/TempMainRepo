#ifndef PODMANAGER_H
#define PODMANAGER_H

#include <map>

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
    ~PodManager();

    void SetupPodManager(int numOfPods);
    void Tick();

    Pod GetPod(int podId);
    int GetPodCount();
};

PodManager::PodManager(){}
PodManager::~PodManager(){}

void PodManager::Tick(){};

void PodManager::SetupPodManager(int numOfPods)
{
    m_podCount = 0;

    for (int i=0; i<numOfPods; i++)
    {
        m_Pods.insert(
            std::pair<int, Pod>
                (m_podCount, CreatePod(m_podCount)));
        m_podCount++;
    };
}

Pod PodManager::CreatePod(int nextIndex)
{
    Pod newPod = Pod(nextIndex);
    return newPod;
};

Pod PodManager::GetPod(int podId)
{
    return m_Pods[podId];
};

int PodManager::GetPodCount()
{
    return m_podCount;
};

#endif