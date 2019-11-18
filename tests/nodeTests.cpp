//
// Created by Mathias Hindsgaul on 14/11/2019.
//

#include <iostream>

//Currently using path, however a fix for relative path is on the way to ensure viability on all pcs
#include "../environment/node.h"

//include the google test dependencies
#include <gtest/gtest.h>

//declare the function are to be tested
double CostToRoot(class Node n);
int heuristic(class Node n, class Node goal);

//Every test consists of a suite(category), and a specific case as the parameters.
//Create objects and variables you want to test and use EXPECT_EQ to test if the two objects/variables are equal to
//each other
TEST(NodeSuite, xpos1){
    Node root(0, 0, Node::North);
    EXPECT_EQ(root.x, 0) << "xpos is not correct";
}

TEST(NodeSuite, xpos2){
    Node root(7, 22, Node::North);
    EXPECT_EQ(root.x, 7) << "xpos is not correct";
}

TEST(NodeSuite, xpos3){
    Node root(-943,143, Node::North);
    EXPECT_EQ(root.x, -943) << "xpos is not correct";
}

TEST(NodeSuite, ypos1){
    Node root(0, 0, Node::North);
    EXPECT_EQ(root.y, 0) << "ypos is not correct";
}

TEST(NodeSuite, ypos2){
    Node root(55, 271, Node::North);
    EXPECT_EQ(root.y, 271) << "ypos is not correct";
}

TEST(NodeSuite, ypos3){
    Node root(1, -3, Node::North);
    EXPECT_EQ(root.y, -3) << "ypos is not correct";
}

TEST(NodeSuite, direction1){
    Node root(0, 0, Node::North);
    EXPECT_EQ(root.direction, Node::North) << "Direction is not correct";
}

TEST(NodeSuite, direction2){
    Node root(0, 0, Node::West);
    EXPECT_EQ(root.direction, Node::West) << "Direction is not correct";
}

TEST(NodeSuite, direction3){
    Node root(0, 0, Node::South);
    EXPECT_EQ(root.direction, Node::South) << "Direction is not correct";
}

TEST(NodeSuite, direction4){
    Node root(0, 0, Node::East);
    EXPECT_EQ(root.direction, Node::East) << "Direction is not correct";
}

TEST(NodeSuite, parent1){
    Node root(0,0, Node::North);
    Node node1(1,0, Node::East);
    node1.parent = &root;
    EXPECT_EQ(node1.parent, &root) << "This is not the correct reference to parent";
}

TEST(NodeSuite, parent2){
    Node root(0,0, Node::North);
    Node node1(1,0, Node::East);
    node1.parent = &root;
    Node node2(2,0, Node::East);
    node2.parent = &node1;
    EXPECT_EQ(node2.parent, &node1) << "This is not the correct reference to parent";
}

TEST(CostToRootSuite, costTest1){
    Node root(0,0,Node::North);
    root.start = true;
    Node node1(0,1,Node::North);
    node1.parent = &root;
    node1.parentWeight = 1;
    Node node2(0,2,Node::North);
    node2.parent = &node1;
    node2.parentWeight = 1;
    int i = node2.CostToRoot(node2);
    EXPECT_EQ(i, 2) << "The cost to root is not correct";
}

TEST(CostToRootSuite, costTest2){
    Node root(0,0,Node::North);
    root.start = true;
    Node node1(1,0,Node::East);
    node1.parent = &root;
    node1.parentWeight = 3;
    Node node2(1,1,Node::North);
    node2.parent = &node1;
    node2.parentWeight = 3;
    int i = node2.CostToRoot(node2);
    EXPECT_EQ(i, 6) << "The cost to root is not correct";
}

TEST(CostToRootSuite, costTest3){
    Node root(0,0,Node::North);
    root.start = true;
    Node node1(1,0,Node::East);
    node1.parent = &root;
    node1.parentWeight = 7;
    Node node2(1,1,Node::North);
    node2.parent = &node1;
    node2.parentWeight = 1;
    int i = node2.CostToRoot(node2);
    EXPECT_EQ(i, 8) << "The cost to root is not correct";
}

//main function for tests, DON'T REMOVE!
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}