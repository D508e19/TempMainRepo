#ifndef CUSTOM_ASTAR_H
#define CUSTOM_ASTAR_H

#include <map>
//#include "../node.h"
//#include "../../src/datatypes/Coordinate.h"
//#include "../../src/datatypes/Path.h"
//#include <queue>
//#include <src/datatypes/direction>

class Astar {
public:
    Astar();
    Path PathFinder(Coordinate, direction, Coordinate);

    Node* current;
    Path pathList;
private:

    Path pathConstructer(Node node, Path path);
    std::list<std::pair<Coordinate, Coordinate>> constructPath(Node, std::list<std::pair<Coordinate, Coordinate>>);
};



#endif 