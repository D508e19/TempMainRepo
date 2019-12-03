#ifndef PODMANAGER_CPP
#define PODMANAGER_CPP

PodManager::PodManager(){}
PodManager::~PodManager(){}

void PodManager::SetupPodManager(Warehouse* _wh, int numOfPods)
{
    wh = _wh;
    podCount = 0;

    nullPodPnt = new Pod(-1); // todo. maybe just use NULL instead??

    for (int i=0; i<numOfPods; i++)
    {
        CreatePod();
    }

    wh->em->AddParkingSpotsForPods(podCount, nullPodPnt);
}

void PodManager::Tick()
{  
    while (!ordersToBeProcessed.empty())
	{
		Order* nextOrder = ordersToBeProcessed.front();
   
        // add pod id - fakeish for now 
        nextOrder->podID = nextOrder->orderID;
    
        // send the order onwards to the Robot Manager
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