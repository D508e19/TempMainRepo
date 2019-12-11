#ifndef PODMANAGER_H
#define PODMANAGER_H


class PodManager
{
private:

    std::pair<int, int> pickingStationLocation;

    void GeneratePodLayout(int warehouse_widthInTiles, int warehouse_heightInTiles);

public:
    PodManager();
    ~PodManager();

    const int layout_startzone_width = 4; //4
    const int layout_hallway_size = 1; //1
    const int layout_edge_size = 1; //1
    const int layout_podcluster_height = 2; //2
    const int layout_podcluster_width = 2; //4

    Warehouse *wh;

    void SetupPodManager(Warehouse * _wh);
    void Tick();

    std::map<int, Pod*> pods; // TODO: laves om til vector?
    std::queue<Order*> ordersToBeProcessed;
    Pod* nullPodPnt;

    int podCount;

    void CreatePod();
    Pod* GetPodPtr(int podID);
};


#endif
