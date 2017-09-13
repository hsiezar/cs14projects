#ifndef __NODE_H__
#define __NODE_H__
#include<iostream>
#include<string>
using namespace std;

struct Node {
    string data;
    int count;
    Node *left;
    Node *right;
    //Node *par;
  Node(string info);
};

Node::Node(string info): data(info), count(1),left(0), right(0){
}
#endif
