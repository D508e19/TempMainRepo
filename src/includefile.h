#ifndef includefile
#define includefile

// forward declarations
class Pod;
class Coordinate;
class Node;
class Order;
class Path;
class Astar;
class DataCollector;
class Pathfinder;
class RobotWrapper;
class OrderManager;
class PodManager;
class RobotManager;
class EnvironmentManager;
class Warehouse;

// datatypes
#include "datatypes/instruction.h"
#include "datatypes/direction.h"

// headers
#include "headers/Pod.h"
#include "headers/Coordinate.h"
#include "headers/Node.h"
#include "headers/Order.h"
#include "headers/Path.h"
#include "headers/Astar.h"
#include "headers/DataCollector.h"
#include "headers/Pathfinder.h"
#include "headers/RobotWrapper.h"
#include "headers/OrderManager.h"
#include "headers/PodManager.h"
#include "headers/RobotManager.h"
#include "headers/EnvironmentManager.h"
#include "headers/Warehouse.h"

// implementation
#include "imp/Pod.cpp"
#include "imp/Coordinate.cpp"
#include "imp/Node.cpp"
#include "imp/Order.cpp"
#include "imp/Path.cpp"
#include "imp/Astar.cpp"
#include "imp/DataCollector.cpp"
#include "imp/Pathfinder.cpp"
#include "imp/RobotWrapper.cpp"
#include "imp/OrderManager.cpp"
#include "imp/PodManager.cpp"
#include "imp/RobotManager.cpp"
#include "imp/EnvironmentManager.cpp"
#include "imp/Warehouse.cpp"

#endif