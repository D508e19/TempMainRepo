#ifndef PODMANAGER_CPP
#define PODMANAGER_CPP

PodManager::PodManager(){}
PodManager::~PodManager(){}

void PodManager::Tick(){};

void PodManager::SetupPodManager(Warehouse* _wh, int numOfPods)
{
    wh = _wh;
    

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