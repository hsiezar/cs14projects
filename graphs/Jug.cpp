#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<fstream>
#include<queue>
#include<stack>
#include "Jug.h"
using namespace std;

Jug::Jug(int capa, int capb, int goal, int fca, int fcb, int ea, int eb, int ap, int bp):
Ca(capa), Cb(capb), N(goal), cfA(fca), cfB(fcb), ceA(ea), ceB(eb), cpAB(ap), cpBA (bp){
  if(valid() == false){
    return;
  }
  paths.push_back("fill A");
  paths.push_back("fill B");
  paths.push_back("empty A");
  paths.push_back("empty B");
  paths.push_back("pour A B");
  paths.push_back("pout B A");
  Vertex* origin = new Vertex();
  vertices.push_back(origin);
  makeGraph(origin);
  //for(unsigned i = 0; i < vertices.size(); ++i){
  //  cout << vertices.at(i)->jugA << " " << vertices.at(i)->jugB << endl;
//  }
}

void Jug::makeGraph(Vertex * vert){
  for(unsigned i = 0; i < paths.size(); ++i){
    Vertex * newVert = 0;
    int cost;
    if(i == 0 && vert->jugA < Ca){ //creates fill a jug is possible
      newVert = new Vertex();
      newVert->jugA = Ca;
      newVert->jugB = vert->jugB;
      newVert->decision = paths.at(i);
      cost = cfA;
    }
    else if (i == 1 && vert->jugB < Cb){ // creates fill b jug if possible
      newVert = new Vertex();
      newVert->jugA = vert->jugA;
      newVert->jugB = Cb;
      newVert->decision = paths.at(i);
      cost = cfB;
    }
    else if(i == 2 && vert->jugA > 0){ // creates empty a if possible
      newVert = new Vertex();
      newVert->jugA = 0;
      newVert->jugB = vert->jugB;
      newVert->decision = paths.at(i);
      cost = ceA;
    }
    else if(i == 3 && vert->jugB > 0){ // created empty a if possible
      newVert = new Vertex();
      newVert->jugB = 0;
      newVert->jugA = vert->jugA;
      newVert->decision = paths.at(i);
      cost = ceB;
    }
    else if(i == 4 && vert->jugB < Cb && vert->jugA > 0){ // pour a to b
      newVert = new Vertex();
      newVert->jugA = vert->jugA;
      newVert->jugB = vert->jugB;
      while(newVert->jugB < Cb && newVert->jugA > 0){
        newVert->jugB += 1;
        newVert->jugA -= 1;
      }
      newVert->decision = paths.at(i);
      cost = cpAB;
    }
    else if(i == 5 && vert->jugA < Ca && vert->jugB > 0){ // pour b to a
      newVert = new Vertex();
      newVert->jugB = vert->jugB;
      newVert->jugA = vert->jugA;
      while(newVert->jugA < Ca && newVert->jugB > 0){
        newVert->jugB -= 1;
        newVert->jugA += 1;
      }
      newVert->decision = paths.at(i);
      cost = cpBA;
    }

    if(newVert != 0){   // if a vertices was created push onto vector and neighbors
      bool duplicate = false;
      for(unsigned j = 0; j < vertices.size(); j++){ // checks diplicates
        if(vertices.at(j)->jugA == newVert->jugA && vertices.at(j)->jugB == newVert->jugB){
          duplicate = true;
        }
      }

      if(duplicate != true){ // finds index of new vertices
        vertices.push_back(newVert);
        unsigned index = 0;
        for(unsigned j = 0; j < vertices.size(); j++){
          if(vertices.at(j) == newVert){
            index = j;
          }
        }
        vert->neighbors.push_back(make_pair(index, cost));
      }
      else{
        delete newVert;
        newVert = 0;
      }
    }
  }

  std::list< pair<int, int> >::iterator it; // addes newvert to list of vert
  for (it = vert->neighbors.begin(); it != vert->neighbors.end(); ++it) {
    makeGraph(vertices.at(it-> first));
  }
}

Jug::~Jug(){ // goes thru vertices and deletes vertices
  for(unsigned i = 0; i < vertices.size(); ++i){
    delete vertices.at(i);
    vertices.at(i) = 0;
  }
}

bool Jug::valid(){ // checks to see if the costs are valid
  if(!((Ca > 0) && (Ca <= Cb)) || !((N < Cb) && (Cb <= 1000))){
    return false;
  }
  else if(0 > cfA || 0 > cfB || 0 > ceA || 0 > ceB || 0 > cpAB || 0 > cpBA){
    return false;
  }
  return true;
}

int Jug::solve(string &solution){ // dykstras
  bool exist = false;

  if(valid() == false){ // checks all cost and capacity
    solution = "";
    return -1;
  }
  for(unsigned i = 0; i < vertices.size(); ++i){ // this loop checks to see if the solution exist
    if(vertices.at(i)->jugA == 0 && vertices.at(i)->jugB == N){
      exist = true;
      break;
    }
  }
  if(exist == false){
    solution = "";
    return 0;
  }
  reset(vertices); // initializes all vertices distance and prev
  queue<Vertex*> q;
  vector<Vertex*> cloud;
  for(unsigned i = 0; i < vertices.size(); i++){
    q.push(vertices.at(i));
  }
  while(!q.empty()){ //dykstras algorithm
    Vertex* curr = q.front();
    cloud.push_back(curr); // seen vertices
    q.pop();
    std::list< pair<int, int> >::iterator it;
    for (it = curr->neighbors.begin(); it != curr->neighbors.end(); ++it){ // this loop relaxes
      if(vertices.at(it->first)->distance > curr->distance + it->second){
        vertices.at(it->first)->distance = curr->distance + it->second;
        vertices.at(it->first)->prev = curr;
      }
    }
  }
  Vertex* goal = 0;
  for(unsigned i = 0; i < cloud.size(); i++){ // finds the vertices = N
    if (cloud.at(i)->jugA == 0 && cloud.at(i)->jugB == N){
      goal = cloud.at(i);
    }
  }
  Vertex* curr = goal;
  Vertex* before = 0;
  stack <string> s;
  int total = 0;

  while(curr){  // collects  all the actions taken
    string arguement  = "";
    before = curr->prev;
    if(before){
     arguement  = curr->decision + "\n";
    }
    s.push(arguement );
    if(before){
     std::list< pair<int, int> >::iterator it;
     for (it = before->neighbors.begin(); it != before->neighbors.end(); ++it){ // collects all the costs of the path
      if(vertices.at(it->first)->jugA == curr->jugA && vertices.at(it->first)->jugB == curr->jugB){
        total = total + it->second;
      }
     }
    }
    curr = before;
  }

  while(!s.empty()){ // reverses the order so the paths are in the right direction
    solution = solution + s.top();
    s.pop();
  }
  solution = solution + "success " + to_string(total);


  return 1;
}

void Jug::reset(vector<Vertex*> vertices){ // resets all vertices distance and prev
  for(unsigned i = 0; i < vertices.size(); ++i){
    vertices.at(i)->distance = INT_MAX;
    vertices.at(i)->prev = 0;
  }
  vertices.at(0)->distance = 0;
  return;
}
