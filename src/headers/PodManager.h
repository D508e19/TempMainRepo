#ifndef PODMANAGER_H
#define PODMANAGER_H


class PodManager
{
private:

public:
    PodManager();
    ~PodManager();

    Warehouse *wh;

    void SetupPodManager(Warehouse * _wh, int numOfPods);
    void Tick();

    std::map<int, Pod*> pods; // TODO: laves om til vector?
    std::queue<Order*> ordersToBeProcessed;
    Pod* nullPodPnt;

    int podCount;

    void CreatePod();

};


#endif
