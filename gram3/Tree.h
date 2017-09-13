#ifndef __TREE_H__
#define __TREE_H__

#include<iostream>
#include<string>
#include "Node.h"
using namespace std;

class Tree {
  private:
    Node * Root;
    void desHelp(Node *);
    void preOrder(Node *)const;
    void inOrder(Node *)const;
    void postOrder(Node *)const;
    bool search(Node *, const string&) const;
    Node * findLeaf(string, Node *);
    bool isLeaf(Node*)const;
    bool twoCheck(Node *)const;
    bool threeCheck(Node *) const;
    //void split(string, Node *, Node *, Node *, Node *, Node *);
    void split(string, Node*, Node*, Node*, Node*, Node*);
    string findMed(string&, Node *);
    string findMin(string& data, Node * curr);
    string findMax(string& data, Node * curr);
    Node * removeFind(const string& data, Node * curr)const;
    Node * orderSucc(const string& data, Node * curr)const;
    void fix(Node * curr);

  public:
    Tree();
    ~Tree();
    void preOrder( )const;
    void inOrder( )const;
    void postOrder( )const;
    void insert(const string &);
    void remove(const string &);
    bool search(const string &) const;
  };
#endif
