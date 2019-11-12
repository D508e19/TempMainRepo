//
// Created by Christopher krejler on 12/11/2019.
//

#include "node.h"

int CostToRoot(Node n){
    if (n.start){
        return 0;
    }
    else{
        return CostToRoot(*n.parent)+n.parentWeight;
    }
}

int heuristic(Node n, Node goal){

}