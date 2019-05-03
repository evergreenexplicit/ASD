
#ifndef ZAD1M_GRAPHS_H
#define ZAD1M_GRAPHS_H


#include <vector>
#include <string>
#include <limits>
#include "../zad2/PriorityQueue.h"

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

};


class Graph{
private:
    int numV;
    vector<vector<Edge>> E_list;
    vector<Vertex> V_list;

public:
    explicit Graph(int numV){
        this->numV = numV;
        for(int i=0; i<numV;i++){
            Vertex v;
            v.minDistance = numeric_limits<double>::infinity();
            v.prevVertex = -1;
            v.idx = i;
            V_list.push_back(v);

        }
        E_list.resize(numV);
    }
    void add_edge(int u ,int v, double weight){
        E_list[u].push_back(*(new Edge(u,v,weight)));///////////
    }
    void dijkstra(int beginning){

        V_list[beginning].minDistance = 0;
        auto *pq = new PriorityQueue<int>();
        for(Vertex v:V_list)
            pq->insert(v.idx,v.minDistance);

        while(!(pq->isEmpty())){
            int currentV = pq->extract_min();

            for(Edge e: E_list[currentV]){
                    if(V_list[e.v].minDistance > V_list[e.u].minDistance + e.weight){
                        V_list[e.v].minDistance = V_list[e.u].minDistance + e.weight;
                        pq->priority(V_list[e.v].idx,V_list[e.v].minDistance);//WARN
                        V_list[e.v].prevVertex = currentV;
                    }
            }



        }
    }
    void pathInOrder( Vertex v){
        if(v.prevVertex != -1)
            pathInOrder(V_list[v.prevVertex]);
        cerr << v.idx+1 << " | dist: " << v.minDistance << endl;
    }
    void print(){
        for (Vertex v:V_list)
            cout << v.idx+1 << " " << v.minDistance << endl;

        for(Vertex v : V_list){
            if(v.prevVertex == -1)
                cerr << "path to " << v.idx+1 << " = " << v.minDistance << endl;
            else{
                cerr << "path to " << v.idx+1 << " = " << v.minDistance << endl;
                pathInOrder(v);
            }

        }

    }

};






#endif //ZAD1M_GRAPHS_H
