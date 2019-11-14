//
// Created by Christopher krejler on 12/11/2019.
//

#ifndef KBOT_NODE_H
#define KBOT_NODE_H

class Node;

class Node {

public:
    Node *parent{};
    int parentWeight{};
    int x{};
    int y{};
    bool start{};
    enum Direction{North, South, East, West};
    Direction direction;

    Node(int, int, Node::Direction);
    static int heuristic(class Node, class Node);
    static int CostToRoot(Node n);
};


#endif //KBOT_NODE_H
