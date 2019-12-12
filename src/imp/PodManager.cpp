#ifndef PODMANAGER_CPP
#define PODMANAGER_CPP

PodManager::PodManager(){}
PodManager::~PodManager(){}

void PodManager::SetupPodManager(Warehouse* _wh)
{
    wh = _wh;
    podCount = 0;

    nullPodPnt = new Pod(-1); // todo. maybe just use NULL instead??

    GeneratePodLayout(wh->em->warehouseLength, wh->em->warehouseHeight);
}

void PodManager::Tick()
{
    std::queue<Order*> failedOrders;

    while (!ordersToBeProcessed.empty())
	{
		Order* nextOrder = ordersToBeProcessed.front();
   
        // add pod id - fakeish for now 
        int podID = (nextOrder->orderID) % podCount;
        nextOrder->podPtr = GetPodPtr(podID);
        //Find location of pod
        std::pair<int, int> podLocation = wh->em->FindPodLocation(pods[nextOrder->podPtr->getId()]);

        //Add picking station location
        nextOrder->pickStation = wh->psm->GetPickStationForOrder();

        //Did it find a pod location?
        if(podLocation.first != -1 && podLocation.second != -1) //Yes
        {
            //argos::LOG << "FOUND THE REQUESTED POD!!" << " Pod id: " << nextOrder->podID << std::endl;
            nextOrder->podPtr->location = podLocation;

            // send the order onwards to the Robot Manager
    	    wh->rm.ordersToBeProcessed.push(nextOrder);
            //nextOrder->pickStation->tasks.push(nextOrder);
            nextOrder->pickStation->tasks.push_back(nextOrder);
        }
        else //No
        {
            argos::LOGERR << "FAILED FINDING THE REQUESTED POD!!" << " Pod id: " << nextOrder->podPtr->getId() << std::endl;

            // Add order to the failed queue
            failedOrders.push(nextOrder);
        }
        
		ordersToBeProcessed.pop();
	}

    // Add the failed orders back into the main queue
    while(!failedOrders.empty())
    {
        ordersToBeProcessed.push(failedOrders.front());
        failedOrders.pop();
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

    argos::LOG << "Final X: " << final_possible_pod_x << std::endl;
    argos::LOG << "Final Y: " << final_possible_pod_y << std::endl;

    //while(currentX < warehouse_widthInTiles && currentY < warehouse_widthInTiles)
    //This while loop will ship the outside of the pod placement zone
    while(currentX <= final_possible_pod_x && currentY <= final_possible_pod_y)
    {
        bool pod_horizontal_check = ((currentX - layout_startzone_width) % (layout_podcluster_width + layout_hallway_size)) < layout_podcluster_width;
        bool pod_vertical_check = ((currentY - layout_edge_size) % (layout_podcluster_height + layout_hallway_size)) < layout_podcluster_height;

        if(pod_horizontal_check && pod_vertical_check)
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