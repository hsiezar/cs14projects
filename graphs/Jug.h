#ifndef __JUG_H__
#define __JUG_H__
#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<list>
#include<climits>
using namespace std;
struct Vertex {
  list<pair<int, int> > neighbors;
  int jugA;
  int jugB;
  int distance;
  string decision;
  Vertex* prev;

  Vertex():jugA(0),jugB(0), distance(INT_MAX), decision(""),prev(0){}
  ~Vertex(){}
};

class Jug {
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    private:
        int Ca;
        int Cb;
        int N;
        int cfA;
        int cfB;
        int ceA;
        int ceB;
        int cpAB;
        int cpBA;
        void makeGraph(Vertex *);
        bool valid();
        void reset(vector<Vertex*> vertices);
        vector<Vertex*> vertices;
        vector<string> paths;
      };
#endif
