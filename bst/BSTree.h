#ifndef __BSTree_H__
#define __BSTree_H__

#include<iostream>
#include<fstream>
#include<string>
#include "Node.h"
using namespace std;


class BSTree {
private:
  Node *Root;
  void preOrder(Node *curr)const;
  void inOrder(Node *curr)const;
  void postOrder(Node *curr)const;
  bool search(Node *curr, string userData)const;
  int heighthelp(Node* curr)const;
  void removehelp(Node *prev, Node* curr, string userData);
  Node * min(Node *curr)const;
  Node * max(Node *curr)const;
public:
  BSTree();
  void insert(const string &);
  Node * searchHeight(const string &, Node * )const;
  bool search(const string &) const;
  string largest() const;
  string smallest() const;
  int height(const string &) const;
  void remove(const string &);
  void preOrder( )const;
  void inOrder( )const;
  void postOrder( )const;

};
BSTree::BSTree(){
  Root = 0;
}
void BSTree::inOrder( )const{
  Node *curr = Root;
  inOrder(curr);
  cout << endl;
}

void BSTree::inOrder(Node *curr)const{
  if(curr == 0){
    return;
  }
  inOrder(curr->left);
  cout << curr->data << "(" << curr->count << ")"<< ", ";
  inOrder(curr->right);
}

void BSTree::preOrder( )const{
  Node *curr = Root;
  preOrder(curr);
  cout << endl;
}

void BSTree::preOrder(Node *curr)const{
  if(curr == 0){
    return;
  }
  cout << curr->data << "(" << curr->count << ")" <<  ", ";
  preOrder(curr->left);
  preOrder(curr->right);
}

void BSTree::postOrder( )const{
  postOrder(Root);
  cout << endl;
}

void BSTree::postOrder(Node *curr)const{
  if(curr == 0){
    return;
  }
  postOrder(curr->left);
  postOrder(curr->right);
  cout << curr->data << "(" << curr->count << ")" << ", ";
}

void BSTree::insert(const string & userData){
  if (Root == 0){
    Node *created = new Node(userData);
    Root = created;
    return;
  }
  Node *curr = Root;
  while(curr != 0){
    if(curr->data == userData){
      curr->count = curr->count + 1;
      return;
    }
    else if(userData > curr->data){
      if(curr->right == 0){
        Node *created = new Node(userData);
        curr->right = created;
        return;
      }
      else if(curr->right != 0){
        curr = curr->right;
      }
    }
    else if(userData < curr->data){
      if(curr->left == 0){
        Node *created = new Node(userData);
        curr->left = created;
        return;
      }
      else if(curr->left != 0){
        curr = curr->left;
      }
    }
  }
}

bool BSTree::search(const string& userData) const{
  bool result;
  if (Root == 0){
    return false;
  }

   result = search(Root, userData);
   return result;
}

bool BSTree::search(Node *curr, string userData) const{
  if(curr == 0){
    return false;
  }
  else if (curr->data == userData){
    return true;
  }
  else if (userData < curr->data){
    curr = curr->left;
    return search(curr,userData);
  }
  else if (userData > curr->data){
    curr = curr->right;
    return search(curr,userData);
  }
  return false;


}

string BSTree::largest() const{
  string small = "";
  if (Root == 0){
    return small;
  }
  Node *curr = Root;
  while(curr != 0){
    small = curr->data;
    curr = curr->right;
  }
  return small;
}

string BSTree::smallest() const{
  string big = "";
  if (Root == 0){
    return big;
  }
  Node *curr = Root;
  while(curr != 0){
    big = curr->data;
    curr = curr->left;
  }
  return big;
}

int BSTree::height(const string & userData) const{
  Node* temp = searchHeight(userData, Root);
  return heighthelp(temp);
}


int BSTree::heighthelp(Node* curr) const{
    if(curr == 0){
      return -1;
    }
    int l = heighthelp(curr->left);
    int r = heighthelp(curr->right);
    if(l >= r){
      return 1 + l;
    }
    else if( l <= r){
      return 1 + r;
    }
    return 0;
}


Node * BSTree::searchHeight(const string & userData, Node *curr)const{
  if(curr == 0){
    return 0;
  }
  else if (curr->data == userData){
    return curr;
  }
  else if (userData < curr->data){
    curr = curr->left;
    return searchHeight(userData, curr);
  }
  else if (userData > curr->data){
    curr = curr->right;
    return searchHeight(userData, curr);
  }
  return 0;

}

void BSTree::remove(const string & userData){
  if(Root == 0){
    return;
  }
  else if((!Root->right && !Root->left) && Root->data == userData){
    delete Root;
    Root = 0;
    return;
  }
  removehelp(Root, Root, userData);
}

void BSTree::removehelp(Node *prev, Node* curr, string userData){
  if (curr == 0){
    return;
  }

  else if(curr->data == userData){
    if(curr->count > 1 && curr->data != prev->data){
      curr->count = curr->count - 1;
      return;
    }
    if(curr == Root && curr->count > 1){
      curr->count = curr->count - 1;
      return;
    }
    else if(!curr->right && !curr->left){

      if(curr->data > prev->data){
        //cout << "here " << endl;
        prev->right = 0;
        delete curr;
        return;
      }
      else if(curr->data < prev->data){
        prev->left = 0;
        delete curr;
        return;
      }
      else if(curr->data == prev->data){
        if(prev->right == 0){
        prev->left = 0;
        delete curr;
        }
        else if(prev->left ==0){
          prev->right = 0;
          delete curr;
        }
        else if(prev->right && prev->left){
          if(curr->data == prev->left->data){
            prev->left = 0;
            delete curr;
          }
          else if(curr->data == prev->right->data){
            prev->right = 0;
            delete curr;
          }
        }
      }
    }
    else if((curr->left != 0 && curr->right != 0) || (curr->left != 0 && curr->right == 0)){
      Node* temp = max(curr->left);
      curr->data = temp->data;
      curr->count = temp->count;
      removehelp(curr, curr->left, curr->data);
    }
    else if(!curr->left && curr->right){
      Node *temp = min(curr->right);
      curr->data = temp->data;
      curr->count = temp->count;
      removehelp(curr, curr-> right, curr->data);
    }
  }
  else if(curr->data < userData){
    removehelp(curr, curr->right, userData);
  }
  else if (curr->data > userData){
    removehelp(curr,curr->left, userData);
  }
}


Node * BSTree::min(Node *curr)const{
  Node *temp = curr;
  while(curr != 0){
    temp = curr;
    curr = curr->left;
  }
  return temp;
}

Node * BSTree::max(Node *curr)const{
  Node *temp = curr;
  while(curr != 0){
    temp = curr;
    curr = curr->right;
  }
  return temp;
}



#endif
