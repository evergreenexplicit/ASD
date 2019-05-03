

#ifndef ZAD4_GRAPHSSCC_H
#define ZAD4_GRAPHSSCC_H

#include <vector>
#include <string>
#include <limits>
#include "PriorityQueue.h"
using namespace std;

struct Vertex {
    int idx;
    int sccIdx;
    int lowLink;
    bool isOnStack;
};
struct Edge{
    int u;
    int v;
    Edge(int u, int v){
        this->u = u;
        this->v = v;
    }

    Edge(){

    }
};
class Graph {
private:
    int numV;
    vector<vector<Edge>> E_list;
    vector<Vertex> V_list;
    vector<Vertex*> dfsStack;
    vector<vector<Vertex*>> SCC_list;
    int sccIdx{};

public:
    Graph(int numV) {
        this->numV = numV;
        for (int i = 0; i < numV; i++) {
            auto *v = new Vertex();
            v->idx = i;
            v->sccIdx = -1;
            V_list.push_back(*v);

        }
        E_list.resize(numV);
    }

    void add_edge(int u, int v) {
        E_list[u].push_back(*(new Edge(u, v)));
    }



    void tarjan(){
        sccIdx = -1;
        for(Vertex &u:V_list)
            if(u.sccIdx == -1)
                scc(&u);
    }

    void scc(Vertex *u){
        u->sccIdx = sccIdx;
        u->lowLink = sccIdx;
        sccIdx++;
        dfsStack.push_back(u);
        u->isOnStack = true;

        for(Edge &e: E_list[u->idx]){
            if (V_list[e.v].sccIdx == -1) {
                scc(&(V_list[e.v]));
                u->lowLink = min(u->lowLink, V_list[e.v].lowLink);
            } else if (V_list[e.v].isOnStack)
                u->lowLink = min(u->lowLink, V_list[e.v].sccIdx);

        }



        if(u->lowLink == u->sccIdx){
            Vertex* v;
            auto *tempList = new vector<Vertex*>();
            do{
                v =  dfsStack.back();
                v->isOnStack = false;
                dfsStack.pop_back();
                tempList->push_back(v);

            }while(v != u);
            SCC_list.push_back(*tempList);
        }


    }
    void print(){
        for(vector<Vertex*> vec : SCC_list){
            cout << "Component nr " << vec[0]->sccIdx << endl;
            for(Vertex* v : vec){
                cout << v->idx << " ";
            }
            cout << endl;
        }


    }



};
#endif //ZAD4_GRAPHSSCC_H
