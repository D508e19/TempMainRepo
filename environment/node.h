//
// Created by Christopher krejler on 12/11/2019.
//

#ifndef KBOT_NODE_H
#define KBOT_NODE_H

class Node;

class Node {

public:
    Node *parent;
    int parentWeight;
    int x;
    int y;
    bool start;
    enum direction{North, South, East, West};

};


#endif //KBOT_NODE_H
