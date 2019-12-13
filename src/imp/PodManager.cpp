#ifndef PODMANAGER_CPP
#define PODMANAGER_CPP

PodManager::PodManager(){}
PodManager::~PodManager(){}

void PodManager::SetupPodManager(Warehouse* _wh)
{
    wh = _wh;
    podCount = 0;

    GeneratePodLayout(wh->em->warehouseLength, wh->em->warehouseHeight);
}

void PodManager::Tick()
{
    //Add information to all orders
    while (!ordersToBeProcessed.empty())
	{
		Order* nextOrder = ordersToBeProcessed.front();
        AddInformationToOrder(nextOrder);
		ordersToBeProcessed.pop();
	}

    // Add the failed orders back into the main queue
    while(!failedOrders.empty())
    {
        ordersToBeProcessed.push(failedOrders.front());
        failedOrders.pop();
    }
}

void PodManager::AddInformationToOrder(Order* order)
{
    // Add pod id - Temporary solution 
    // Should be replaced by logic when pods contains items
    int podID = (order->orderID) % podCount;
    order->podPtr = GetPodPtr(podID);
    //Find location of pod
    std::pair<int, int> podLocation = wh->em->FindPodLocation(pods[order->podPtr->getId()]);

    //Add picking station location
    order->pickStation = wh->psm->GetPickStationForOrder();

    //Did it find a pod location?
    if(podLocation.first != -1 && podLocation.second != -1) //Yes
    {
        order->podPtr->location = podLocation;

        // send the order onwards to the Robot Manager
        wh->rm.ordersToBeProcessed.push(order);
        order->pickStation->activeOrders.push_back(order);
    }
    else //No
    {
        argos::LOGERR << "FAILED TO FIND THE REQUESTED POD!!" << " Pod id: " << order->podPtr->getId() << std::endl;

        // Add order to the failed queue
        failedOrders.push(order);
    }
}

void PodManager::CreatePod()
{
    Pod* newPod = new Pod(podCount);
	pods.insert(std::pair<int, Pod*> (podCount, newPod));
	podCount++;
}

void PodManager::GeneratePodLayout(int warehouse_widthInTiles, int warehouse_heightInTiles)
{
    int currentX = layout_startzone_width;
    int currentY = layout_edge_size;

    int final_possible_pod_x = warehouse_widthInTiles - 1 - layout_edge_size;
    int final_possible_pod_y = warehouse_heightInTiles - 1 - layout_edge_size;

    //This while loop will skip the outside of the pod placement zone
    while(currentX <= final_possible_pod_x && currentY <= final_possible_pod_y)
    {
        bool pod_horizontal_check = ((currentX - layout_startzone_width) % (layout_podcluster_width + layout_hallway_size)) < layout_podcluster_width;
        bool pod_vertical_check = ((currentY - layout_edge_size) % (layout_podcluster_height + layout_hallway_size)) < layout_podcluster_height;

        if(pod_horizontal_check && pod_vertical_check) //Create and place pod. If false it is a hallway.
        {
            CreatePod();
            wh->em->PlacePod( pods[podCount-1], Coordinate(currentX, currentY));
            pods[podCount-1]->location = std::pair<int,int>(currentX, currentY);
        }

        //Incrementation
        currentX++;

        if(currentX > final_possible_pod_x)
        {
            currentX = layout_startzone_width;
            currentY++;
        }
    }
}

void PodManager::GeneratePodLayoutWithDebugPrint(int warehouse_widthInTiles, int warehouse_heightInTiles)
{
    //TODO DEBUG: initialize array
    char tiles[warehouse_widthInTiles][warehouse_heightInTiles];
    for(int y = 0; y < warehouse_heightInTiles; y++)
    {
        for(int x = 0; x < warehouse_widthInTiles; x++)
        {
            tiles[x][y] = 'E';
        }
    }

    int currentX = layout_startzone_width;
    int currentY = layout_edge_size;

    int final_possible_pod_x = warehouse_widthInTiles - 1 - layout_edge_size;
    int final_possible_pod_y = warehouse_heightInTiles - 1 - layout_edge_size;

    //This while loop will ship the outside of the pod placement zone
    while(currentX <= final_possible_pod_x && currentY <= final_possible_pod_y)
    {
        bool pod_horizontal_check = ((currentX - layout_startzone_width) % (layout_podcluster_width + layout_hallway_size)) < layout_podcluster_width;
        bool pod_vertical_check = ((currentY - layout_edge_size) % (layout_podcluster_height + layout_hallway_size)) < layout_podcluster_height;

        if(pod_horizontal_check && pod_vertical_check) //Create and place pod. If false it is a hallway.
        {
            tiles[currentX][currentY] = 'P';

            CreatePod();
            wh->em->PlacePod( pods[podCount-1], Coordinate(currentX, currentY));
            pods[podCount-1]->location = std::pair<int,int>(currentX, currentY);
        }
        else
        {
            tiles[currentX][currentY] = 'H';
        }

        //Incrementation
        currentX++;

        if(currentX > final_possible_pod_x)
        {
            currentX = layout_startzone_width;
            currentY++;
        }
    }

    //TODO DEBUG: print visual warehouse
    for(int y = 0; y < warehouse_heightInTiles; y++)
    {
        for(int x = 0; x < warehouse_widthInTiles; x++)
        {
            argos::LOG << tiles[x][y];
        }

        argos::LOG << std::endl;
    }
}

Pod* PodManager::GetPodPtr(int podID)
{
    return pods[podID];
}


#endif