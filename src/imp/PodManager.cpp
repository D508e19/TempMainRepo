#ifndef PODMANAGER_CPP
#define PODMANAGER_CPP

PodManager::PodManager(){}
PodManager::~PodManager(){}

void PodManager::SetupPodManager(Warehouse* _wh, int numOfPods)
{
    wh = _wh;
    podCount = 0;

    for (int i=0; i<numOfPods; i++)
    {
        CreatePod();
    }
}

void PodManager::Tick()
{  
    int temp = rand()%99;
    argos::LOG << "PodCount" << podCount << std::endl; 
    argos::LOG << "Pod id: " << pods[temp]->getId() << "is = " << temp << std::endl;

    while (!ordersToBeProcessed.empty())
	{
		Order* nextOrder = ordersToBeProcessed.front();
        //argos::LOG << "pm. read order id: " << ordersToBeProcessed.front()->orderID << std::endl;
        nextOrder->orderID += 100;
        // add pod id
		wh->rm.ordersToBeProcessed.push(nextOrder);
		ordersToBeProcessed.pop();
	}
}

void PodManager::CreatePod()
{
    Pod* newPod = new Pod(podCount);
	pods.insert(std::pair<int, Pod*> (podCount, newPod));
	podCount++;
}


#endif