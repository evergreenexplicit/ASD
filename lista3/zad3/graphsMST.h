//
// Created by konra on 27.04.2019.
//

#ifndef ZAD1M_GRAPHSMST_H
#define ZAD1M_GRAPHSMST_H

#include <vector>
#include <string>
#include <limits>
#include "PriorityQueue.h"
#include "UnionFind.h"
#define REVERSE 2
using namespace std;

struct Vertex {
    int idx;
    double minDistance;
    int prevVertex;
};
struct Edge{
    int u;
    int v;
    double weight;
    Edge(int u, int v,double weight){
        this->u = u;
        this->v = v;
        this->weight = weight;
    }

    Edge(){

    }
};
class Graph {
private:
    Edge eTemp;
    int numV;
    vector<vector<Edge>> E_list;
    vector<Vertex> V_list;
    vector<Edge*>* used;
public:
    Graph(int numV) {
        this->numV = numV;
        for (int i = 0; i < numV; i++) {
            auto *v = new Vertex();
            v->prevVertex = -1;
            v->minDistance = numeric_limits<double>::infinity();
            v->idx = i;
            V_list.push_back(*v);

        }
        E_list.resize(numV);
    }

    void add_edge(int u, int v, double weight) {
        E_list[u].push_back(*(new Edge(u, v, weight)));
    }


    void krusgal() {
        auto *uf = new UnionFind(V_list.size());
        auto *pq = new PriorityQueue<Edge*>();
        used = new vector<Edge*>;
        for(auto &subList:E_list)
        for (auto &e: subList)
            pq->insert(&e, e.weight);


        Edge* e;
        for (auto i = 0; i < numV - 1; i++) {
            do {
                e = pq->extract_min();
            } while(uf->connected((*e).u,(*e).v));
            used->push_back(e);
            uf->merge((*e).u,(*e).v);
        }
    }
    void prim() {
        vector<bool> alreadyIn(numV, false);
        PriorityQueue<int> pq;
        used = new vector<Edge*>;
        V_list[0].minDistance = 0;
        for (Vertex v:V_list)
              pq.insert(v.idx, v.minDistance);


        while(!pq.isEmpty()){
            int currentV = pq.extract_min();
            alreadyIn[currentV] = true;

            for (auto &e : E_list[currentV]) {
                if(e.v == V_list[currentV].prevVertex)
                    used->push_back(&e);
                if (!alreadyIn[e.v] && V_list[e.v].minDistance > e.weight) {
                    V_list[e.v].minDistance = e.weight;
                    pq.priority(V_list[e.v].idx, V_list[e.v].minDistance);
                    V_list[e.v].prevVertex = currentV;
                }
            }
        }
    }
    void print(){
        double sum = 0;
        for(Edge *e : *used){
            if(e != nullptr) {
                cout << "(" << (*e).u + 1 << "," << (*e).v + 1 << ") " << (*e).weight << endl;
                sum += (*e).weight;
            }
        }
        cout << "sum:" << sum << endl;
    }

};

























#endif //ZAD1M_GRAPHSMST_H
