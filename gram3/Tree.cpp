#include "Tree.h"
#include<iostream>
#include<string>
using namespace std;
#include "Node.h"

Tree::Tree(){
  Root = 0;
}

Tree::~Tree(){
  desHelp(Root);
  Root = 0;
}

void Tree::desHelp(Node * curr){
  if(curr == 0){
    return;
  }

  if(isLeaf(curr)){
    delete curr;
    curr = 0;
  }
  else if(twoCheck(curr)){               //for two nodes
    desHelp(curr->left);
    desHelp(curr->right);
  }
  else{
    desHelp(curr->left);             //for three node
    desHelp(curr->middle);
    desHelp(curr->right);
  }
} //recursive function for destructer

void Tree::inOrder()const{
  inOrder(Root);
  cout << endl;
}

void Tree::inOrder(Node *curr)const{
  if(curr == 0){
    return;
  }
  else if(twoCheck(curr)){
    inOrder(curr->left);
    cout << curr->small << ", ";
    inOrder(curr->right);
  }
  else if (threeCheck(curr)){
    inOrder(curr->left);
    cout << curr->small << ", ";
    inOrder(curr->middle);
    cout << curr->large << ", ";
    inOrder(curr->right);
  }
}

void Tree::preOrder( ) const{
  preOrder(Root);
  cout << endl;
}

void Tree::preOrder(Node * curr)const{
  if(curr == 0){
    return;
  }
  else if(twoCheck(curr)){
    cout << curr->small << ", ";
    preOrder(curr->left);
    preOrder(curr->right);
  }
  else if (threeCheck(curr)){
    cout << curr->small << ", ";
    preOrder(curr->left);
    cout << curr->large << ", ";
    preOrder(curr->middle);
    preOrder(curr->right);
  }
}

void Tree::postOrder( ) const{
  postOrder(Root);
  cout << endl;
}

void Tree::postOrder(Node * curr)const{
  if(curr == 0){
    return;
  }
  else if(twoCheck(curr)){
    postOrder(curr->left);
    postOrder(curr->right);
    cout << curr->small << ", ";
  }
  else if(threeCheck(curr)){
    postOrder(curr->left);
    postOrder(curr->middle);
    cout << curr->small << ", ";
    postOrder(curr->right);
    cout << curr->large << ", ";
  }
}

bool Tree::search (const string &data) const{
    if(Root == 0){
        return false;
    }
    return search(Root, data);
}

bool Tree::search(Node * curr, const string& data) const{ // recursive helper function to navigate thru tree
  if (!curr){
    return false;
  }
  else if (curr->small == data || curr->large == data){
    return true;
  }
  else{
    if (data < curr->small){
      return search(curr->left, data);          //search down left subtree
    }
    else if (data < curr->large){
      return search(curr->middle, data);        //search down middle subtree
    }
    else{
      return search(curr->right, data);         //search down right subtree
    }
  }
}

bool Tree::threeCheck(Node *curr)const{ // checks to see if its three node by checking both strings
  if (!curr->small.empty() && !curr->large.empty()){
    return true;
  }
    return false;
}

bool Tree::twoCheck(Node *curr)const{ // checks if node is a 2 node by checking large string
  if (!curr->small.empty() && curr->large.empty()){
    return true;
  }
  return false;
}

void Tree::insert(const string &data){
  if(Root == 0){
    Root = new Node(data);
    return;
  }
  Node * leaf = findLeaf(data, Root); // find node it belongs in
  if(isLeaf(leaf)){  // adds data according if it is a two node
    if(twoCheck(leaf)){
      if(leaf->small < data){
        leaf->large = data;
        return;
      }
      else{
        string swapval = leaf->small;
        leaf->large = swapval;
        leaf->small = data;
      }
      return;
    }
    else if (threeCheck(leaf)){  // if three node it hits the recursive call
      split(data, leaf, 0, 0, 0, 0);
    }
  }
    return;
}

Node * Tree::findLeaf(string data, Node *curr){ // finds the leaf for the insert function
  if(curr == 0){
    return 0;
  }
  if(isLeaf(curr)){
    return curr;
  }
  else if(twoCheck(curr)){
    if(data  == curr->small || data == curr->large){
      return curr;
    }
    else if(data < curr->small){
      return findLeaf(data, curr->left);
    }
    else{
      return findLeaf(data, curr->right);
    }
  }
  else{
    if(data == curr->small || data == curr->large){
      return curr;
    }
    else if(data < curr->small){
      return findLeaf(data, curr->left);
    }
    else if(data > curr->large){
      return findLeaf(data, curr->right);
    }
    else{
      return findLeaf(data, curr->middle);
    }
  }
}

string Tree::findMed(string& data, Node* curr){ // finds the medium value for the insert if its 3node
  if(curr->large < data){
    return curr->large;
  }
  else if (curr->small > data){
    return curr->small;
  }
  else{
  return data;
  }
}

string Tree::findMin(string& data, Node* curr){ // finds the minium value for the insert if its 3node
  if(curr->small > data){
    return data;
  }
  else{
    return curr->small;
  }
}

string Tree::findMax(string&data, Node* curr){  // finds the max value for the insert if its 3node
  if(curr->large > data){
    return curr->large;
  }
  else{
    return data;
  }
}

bool Tree::isLeaf(Node* curr)const{ // checks to see if the node is leaf by no children present
  if(!curr->right && !curr->middle && !curr->left){
    return true;
  }
  return false;
}

void Tree::split(string data, Node * curr, Node* child1, Node* child2, Node* child3, Node* child4){
  Node* p = 0;
  string medVal = findMed(data, curr);
  //bool changer = true;
  if(Root == curr){
    p = new Node(findMed(data, curr)); // allocates memory when node is root
  }
  else {
    p = curr->parent; // the parent is set to previous
  }
  Node* split1 = new  Node(findMin(data, curr)); // splits node by size
  Node* split2 = new Node(findMax(data, curr));
  split1->parent = p;
  split2->parent = p;
  if(!isLeaf(curr)){ // reassigning children
    split1->left = child1;
    split1->right = child2;
    child1->parent = split1;
    child2->parent = split1;
    split2->left = child3;
    split2->right = child4;
    child3->parent = split2;
    child4->parent = split2;
  }
  Node* newchild1 = 0;
  Node* newchild2 = 0;
  Node* newchild3 = 0;
  Node* newchild4 = 0;
  if(threeCheck(curr) && threeCheck(p)){ // different  cases of recursive call and children assigning
    //changer = false;
    //cout << " IN THREE BRANCH" << endl;
    if(curr == p->left){
      newchild1 = split1;
      newchild2 = split2;
      newchild3 = p->middle;
      newchild4 = p->right;
    }
    else if(curr == p->middle){
      newchild1 = p->left;
      newchild2 = split1;
      newchild3 = split2;
      newchild4 = p->right;
    }
    if(curr == p->right){
      newchild1= p->left;
      newchild2 = p->middle;
      newchild3 = split1;
      newchild4 = split2;
    }
    split(medVal, p, newchild1, newchild2, newchild3, newchild4); // recursive call
  }
  if(twoCheck(p)){ // if node = 2node than the small and large are filled accordingly
    if(curr == Root){
      p->left = split1;
      p->right = split2;
      Root = p;
    }
    else if(curr == p->left){
      p->left = split1;
      p->middle = split2;
      p->large = p->small;
      p->small = medVal;
    }
    else{
      p->middle = split1;
      p->right = split2;
      p->large = medVal;
    }
  }
  return;
}

Node * Tree::removeFind(const string& data, Node* curr)const{
  if(curr == 0){
    return 0;
  }
  else if(curr->small == data || curr->large == data){
    return curr;
  }
  else if(twoCheck(curr)){
    if(curr->small < data){
      return removeFind(data, curr->right);
    }
    else{
      return removeFind(data, curr->left);
    }
  }
  else{
    if(curr->small > data){
      return removeFind(data, curr->left);
    }
    else if(curr->small <= data || curr->large > data){
      return removeFind(data, curr->middle);
    }
    else{
      return removeFind(data, curr->right);
    }
  }
}

Node* Tree::orderSucc(const string& data, Node *curr)const{
  if(isLeaf(curr)){
    return curr;
  }
  else if(twoCheck(curr)){
    if(curr->small > data){
      return orderSucc(data, curr->left);
    }
    else{
      return orderSucc(data, curr->right);
    }
  }
  else{
    if(curr->small > data){
      return orderSucc(data, curr->left);
    }
    else if(curr->small < data && curr->large > data){
      return orderSucc(data, curr->middle);
    }
    else{
      return orderSucc(data, curr->right);
    }
  }
}

void Tree::remove(const string &data){
  if(Root == 0){
    return;
  }
  else if(data == Root->small && Root->large.empty()){
    delete Root;
    Root = 0;
    return;
  }
  else{
    if(data == Root->small){
      Root->small = Root->large;
      Root->large = "";
      return;
    }
    else{
      Root->large = "";
      return;
    }
  }
}

void Tree::fix(Node * curr){
  /*Node * p = 0;
  string pval;
  if(curr == Root){
    delete curr;
  }
  else{
    p = curr->parent;
  }
  Node * child1 = 0;
  Node * child2 = 0;
  Node * child3 = 0;
  Node * child4 = 0;
  if(has3child(p)){
    if(twoCheck(p->right)){
      pval = p->small;
      p->small = p->right->small;
      curr->small = pval;
      if(!isLeaf(p->right)){
        if(curr->right){
          child1 = curr->right;
        }
        else{
          child1 = curr->left;
        }
        child2 = p->right->left;
        child3 = p->right->middle;
        child4 = p->right->right;
        curr->left = child1;
        curr->right = child2;
        p->right->left = child3;
        p->right->right = child4;
      }
    }
  } */
}
