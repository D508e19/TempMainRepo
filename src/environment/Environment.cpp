#include "Position.h" 
#include <list>  
#include <iterator>
#include <iostream>  

class Environment {
    private: 
    std::list <Position> pods;
    std::list <Position> pickupStations;
    std::list <Position> refillStations;
    std::list <Position> blocked;
    std::list <Position> podSpaces;
    std::list <Position> reservations;

    public:
    // Constructor?
    Environment() {

    }

    // Custom methods (Temporary)
    void printList (std::list <Position> theList){
        std::list <Position> :: iterator it;
        for(it = theList.begin(); it != theList.end(); ++it) 
        std::cout << "(" << it->getX() << "," << it->getY() << ")" << '\n'; 
    }

    // Adders
    void addPod (Position position){
        pods.push_back(position);
    }

    // Setters
    void setPods(std::list <Position> newList){pods = newList;}
    void setPickup_stations(std::list <Position> newList){pickupStations = newList;};
    void setRefill_stations(std::list <Position> newList){refillStations = newList;};
    void setBlocked(std::list <Position> newList){blocked = newList;};
    void setPod_spaces(std::list <Position> newList){podSpaces = newList;};
    void setReservations(std::list <Position> newList){reservations = newList;};

    // Getters
    std::list <Position> getPods() {return pods;}
    std::list <Position> getPickup_stations(){return pickupStations;};
    std::list <Position> getRefill_stations(){return refillStations;};
    std::list <Position> getBlocked(){return blocked;};
    std::list <Position> getPod_spaces(){return podSpaces;};
    std::list <Position> getReservations(){return reservations;};

};