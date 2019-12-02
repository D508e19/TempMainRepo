#ifndef CUSTOM_NODE_CPP
#define CUSTOM_NODE_CPP

Node::Node() {
}
Node::Node(Coordinate c, direction d) {
    coordinate = c;
    lowestCost = 100000000;
    Dir = d;
    parentWeight = 0;
    fScore = 100000000;
    gScore = 0;
    start = true;
}
Node::Node(Coordinate c, direction d, Node* p, int weight) {
    fScore = 1000000000;
    gScore = 1000000000;
    start = false;
    Dir = d;
    coordinate= c;
    parent = p;
    parentWeight = weight;
}


int Node::CostToRoot(Node n){
    if (n.start){
        return 0;
    }
    else{
        return CostToRoot(*n.parent)+n.parentWeight;
    }
}


std::list<Node> Node::ReturnPath(Node n, std::list<Node> path){
    if (n.start){
        argos::LOG << "Hello11 ";
        path.push_back(n);
        return path;
    }
    else{
        path.push_back(n);
        return ReturnPath(*n.parent, path);
    }
}

int Node::heuristic(Coordinate goal){
    int gx = goal.x;
    int gy = goal.y;
    int nx = coordinate.x;
    int ny = coordinate.y;
    int h = 0;

    int deltaX = abs(nx-gx);;
    int deltaY = abs(ny-gy);


    if(gx == nx && gy == ny){
        return h;
    }

    if(Dir == north){
        if(gx != nx){
            h+= 3;
            if(gy<ny){
                h+=3;
            }
        }else if(gy < ny){
            h+=6;
        }
    }

    else if(Dir == south){
        if(gx != nx){
            h+= 3;
            if(gy>ny){
                h+=3;
            }
        }else if(gy > ny){
            h+=6;
        }
    }

    else if(Dir == east){
        if(gy != ny){
            h+= 3;
            if(gx<nx){
                h+=3;
            }
        }else if(gx < nx){
            h+=6;
        }
    }
    else if(Dir == west){
        if(gy != ny){
            h+= 3;
            if(gx>nx){
                h+=3;
            }
        }else if(gx > nx){
            h+=6;
        }
    }

    h+= deltaX;
    h+= deltaY;

    argos::LOG << h << std::endl;
    argos::LOG << "( " << nx << " , " << ny << " )" << std::endl;

    return h;
}


void Node::calculateNeighbour() {
    switch (Dir)
    {
        case north :
            children.emplace_back(Node((*(new Coordinate(coordinate.x, coordinate.y + 1))), north, this, 1));
            children.emplace_back(Node((*this).coordinate, south, this, 3));
            children.emplace_back(Node((*this).coordinate, east, this, 3));
            children.emplace_back(Node((*this).coordinate, west, this, 3));
            //(*this).children.push_back(new Node((*this).coordinate, north, this, 1));
            break;
        case south :
            (*this).children.emplace_back(Node((*this).coordinate, north, this, 3));
            (*this).children.emplace_back(Node((*(new Coordinate(coordinate.x, coordinate.y - 1))), south, this, 1));
            (*this).children.emplace_back(Node((*this).coordinate, east, this, 3));
            (*this).children.emplace_back(Node((*this).coordinate, west, this, 3));
            //(*this).children.push_back(new Node((*this).coordinate, south, this, 1));

            break;
        case east :
            (*this).children.emplace_back(Node((*this).coordinate, north, this, 3));
            (*this).children.emplace_back(Node((*this).coordinate, south, this, 3));
            (*this).children.emplace_back(Node((*(new Coordinate(coordinate.x + 1, coordinate.y))), east, this, 1));
            (*this).children.emplace_back(Node((*this).coordinate, west, this, 3));
            //(*this).children.push_back(new Node((*this).coordinate, east, this, 1));

            break;
        case west :
            (*this).children.emplace_back(Node((*this).coordinate, north, this, 3));
            (*this).children.emplace_back(Node((*this).coordinate, south, this, 3));
            (*this).children.emplace_back(Node((*this).coordinate, east, this, 3));
            (*this).children.emplace_back(Node((*(new Coordinate(coordinate.x - 1, coordinate.y))), west, this, 1));
            //(*this).children.push_back(new Node((*this).coordinate, west, this, 1));
            break;
        default:
            break;
    }
}

Node* Node::leastCost() {

    if(children.empty()){
        return this;
    }
    else{
        Node* lowboi = (&children.front());

        for(Node& n : children) {
            if ((*lowboi).lowestCost > n.lowestCost) {
                lowboi= (&n);
            }
        }
        return (*lowboi).leastCost();
    }
}

#endif