#ifndef PODMANAGER_H
#define PODMANAGER_H

#include <queue>

class PodManager
{
private:
    std::queue<Order*> failedOrders;

    void GeneratePodLayout(int warehouse_widthInTiles, int warehouse_heightInTiles);
    void GeneratePodLayoutWithDebugPrint(int warehouse_widthInTiles, int warehouse_heightInTiles);

public:
    PodManager();
    ~PodManager();

    const int layout_startzone_width = 4;
    const int layout_hallway_size = 1;
    const int layout_edge_size = 1;
    const int layout_podcluster_height = 2;
    const int layout_podcluster_width = 2;

    Warehouse *wh;

    void SetupPodManager(Warehouse * _wh);
    void Tick();

    std::map<int, Pod*> pods;
    std::queue<Order*> ordersToBeProcessed;

    int podCount;

    void AddInformationToOrder(Order* order);
    void CreatePod();
    Pod* GetPodPtr(int podID);
};

#endif
