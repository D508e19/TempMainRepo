#ifndef PODMANAGER_H
#define PODMANAGER_H


class PodManager
{
private:
    std::map<int, Pod> m_Pods; // TODO: laves om til vector?
    int m_podCount;

    Warehouse *wh;

    Pod CreatePod(int);
    bool DeletePod();

public:
    PodManager();
    ~PodManager();

    void SetupPodManager(Warehouse * _wh, int numOfPods);
    void Tick();

    Pod GetPod(int podId);
    int GetPodCount();
};


#endif
