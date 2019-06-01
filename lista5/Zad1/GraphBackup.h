//
// Created by konra on 22.05.2019.
//

#ifndef ZAD1_GRAPHS_H
#define ZAD1_GRAPHS_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <initializer_list>
#include <cstring>
#include <queue>
#include <fstream>
using namespace std;



struct Edge {
    int u;
    int v;
    int flow;
    int cap;
    Edge* rev;
    Edge(int u, int v, int cap) {
        this->u = u;
        this->v = v;
        this->cap = cap;
        this->flow = 0;
        this->rev = nullptr;
    }


};

unsigned int countBits(unsigned int n) {
    unsigned int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

class HypercubeGraph {
private:

    unsigned int k;
    vector<vector<Edge*>> edges;

public:
    unsigned int numV;
    unsigned int numE;
    unsigned int augPathsNum = 0;
    explicit HypercubeGraph(unsigned int k) {
        numE = 0;
        this->k = k;
        this->numV = static_cast<unsigned int>(pow(2, k));



        edges.resize(numV); // WARN: the last one is empty in this case

        for (unsigned int i = 0; i < numV; i++) {
            unsigned int twoPow = 1;
            while (twoPow < numV) {
                if ((twoPow ^ i) > i) {
                    add_edge(i, twoPow ^ i);
                }

                twoPow *= 2;
            }
        }
    }

    ~HypercubeGraph(){
        vector<vector<Edge*>>().swap(edges);
    }
    void add_edge(unsigned int u, unsigned int v) {

        unsigned int max = std::max({countBits(u), k - countBits(u), countBits(v), k - countBits(v)});
        auto cap = static_cast<unsigned int>(pow(2, std::rand() % (max + 1)));
        Edge* edge = new Edge(u, v, cap);
        Edge* revEdge = new Edge(v,u,0);
        edge->rev = revEdge;
        revEdge->rev = edge;
        edges[u].push_back(edge);
        edges[v].push_back(revEdge);
        // cout << u << " " << v << " " << cap << endl;
        numE++;
    }

    int edmond_karp(int s, int t) {



        int flow = 0;
        vector<Edge*> predList;
        do {
            predList.clear();//TODO
            predList.resize(numV);//warn: with nullptr?
            queue<int> q;
            q.push(s);
            while (!q.empty()) {
                int curNode = q.front();
                q.pop();
                for (Edge* e:edges[curNode]) {
                    if (predList[e->v]==nullptr && e->v != s && e->cap > e->flow) {
                        predList[e->v] = e;
                        q.push(e->v);
                    }
                }
            }

            if (predList[t]) {
                augPathsNum++;
                int flowDiff = 1 << 29; // INF
                for (Edge *e = predList[t]; e; e = predList[e->u])
                    flowDiff = min(flowDiff, (e->cap - e->flow));

                for (Edge *e = predList[t]; e; e = predList[e->u]) {
                    e->flow += flowDiff;
                    e->rev->flow -=flowDiff;
                }
                flow += flowDiff;
            }
        } while(predList[t]);

        return flow;
    }



    void generate(const string &fileName){
        ofstream myfile;
        myfile.open (fileName);

        myfile <<"param n, integer, >= 2;" << endl;
        myfile <<"/* number of nodes */" << endl;

        myfile <<"set V, default {0..(n-1)};" << endl;
        myfile << "/* set of nodes */" << endl;

        myfile << "set E, within V cross V;" << endl;
        myfile << "/* set of arcs */" << endl;

        myfile << "param a{(i,j) in E}, > 0;" << endl;
        myfile << "/* a[i,j] is capacity of arc (i,j) */" << endl;

        myfile << "param s, symbolic, in V, default 0;" << endl;
        myfile << "/* source node */" << endl;

        myfile << "param t, symbolic, in V, != s, default (n-1);" << endl;
        myfile << "/* sink node */" << endl;

        myfile << "var x{(i,j) in E}, >= 0, <= a[i,j];" << endl;
        myfile << "/* x[i,j] is elementary flow through arc (i,j) to be found */" << endl;

        myfile << "var flow, >= 0;" << endl;
        myfile << "/* total flow from s to t */" << endl;

        myfile << "s.t. node{i in V}:" << endl;
        myfile << "/* node[i] is conservation constraint for node i */" << endl;

        myfile << "    sum{(j,i) in E} x[j,i] + (if i = s then flow)" << endl;
        myfile << "    /* summary flow into node i through all ingoing arcs */" << endl;

        myfile << "    = /* must be equal to */" << endl;

        myfile << "    sum{(i,j) in E} x[i,j] + (if i = t then flow);" << endl;
        myfile << "    /* summary flow from node i through all outgoing arcs */" << endl;

        myfile << "maximize obj: flow;" << endl;
        myfile << "/* objective is to maximize the total flow through the network */" << endl;

        myfile << "solve;" << endl;


        myfile << "printf " << "\"Maximum flow from node %s to node %s is %g\\n\\n\"" << ", s, t, flow;" << endl;


        myfile << "data;" << endl;




//TODO change first idx to 0
        myfile << "param n := "<< numV << ";" << endl;

        myfile << "param : E :   a :=" << endl;
        for(vector<Edge*> list : edges){
            for(Edge* e  : list){
                if(e->u < e->v)
                    myfile << "          " << e->u << " " << e->v  << "   " << e->cap << endl;
            }

        }
        myfile << ";"<<endl;

        myfile << "end;" << endl;

    }
};


#endif //ZAD1_GRAPHS_H
