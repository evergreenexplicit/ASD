//
// Created by konra on 24.05.2019.
//

#ifndef ZAD2_BGRAPH_H
#define ZAD2_BGRAPH_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <queue>
#include <fstream>

#define NIL 0
#define INF (1<<28)
using namespace std;

class BGraph {
private:
    vector<vector<int> > edges;
    vector<int> dist;
    vector<int> match;
    int numV, k, edgesPerOne;
public:
    BGraph(int k, int edgesPerOne) {
        numV = static_cast<int>(pow(2, k));
        this->k = k;
        this->edgesPerOne = edgesPerOne;
        edges.resize(numV + 1);
        match.resize(2 * numV + 1);
        dist.resize(numV + 1);
        int randomVal;
        for (int i = 1; i <= numV; i++)
            for (int j = 0; j < edgesPerOne; j++) {
                while (find(
                        edges[i].begin(),
                        edges[i].end(),
                        (randomVal = numV + 1 + ((rand()) % (numV)))
                ) != edges[i].end()
                        ) {} // avoiding repetitions with finding in while loop
                //  cout << randomVal << endl;
                add_edge(i, randomVal);

            }


    }

    void add_edge(int u, int v) {
        edges[u].push_back(v);
        //cout << u << " " << v << endl;
    }

    bool bfs() {

        queue<int> q;
        for (int i = 1; i <= numV; i++) {
            if (match[i] == NIL) {
                dist[i] = 0;
                q.push(i);
            } else dist[i] = INF;
        }
        dist[NIL] = INF;
        int u;
        while (!q.empty()) {
            u = q.front();
            q.pop();
            if (u != NIL) {
                for (int &v : edges[u]) {
                    if (dist[match[v]] == INF) {
                        dist[match[v]] = dist[u] + 1;
                        q.push(match[v]);
                    }
                }
            }
        }
        return (dist[NIL] != INF);
    }

    bool dfs(int u) {
        if (u != NIL) {
            for (int &v: edges[u]) {
                if (dist[match[v]] == dist[u] + 1) {
                    if (dfs(match[v])) {
                        match[v] = u;
                        match[u] = v;
                        return true;
                    }
                }
            }
            dist[u] = INF;
            return false;
        }
        return true;
    }

    int hopcroft_karp() {
        int matching = 0, i;
        // match[] is assumed NIL for all vertex in edges
        while (bfs())
            for (i = 1; i <= numV; i++)
                if (match[i] == NIL && dfs(i))
                    matching++;
        return matching;
    }

    void generate(const string &fileName) {
        ofstream myfile;
        myfile.open(fileName);

        myfile << "param n, integer, >= 2;" << endl;
        myfile << "/* number of nodes */" << endl;

        myfile << "set V, default {0..(n-1)};" << endl;
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
        myfile << "/* Maxflow problem is equivalent to max matching problem when we connect V1 to source and V2 to sink */" << endl;
        myfile << "solve;" << endl;


        myfile << "printf " << "\"Maximum flow from node %s to node %s is %g\\n\\n\"" << ", s, t, flow;" << endl;


        myfile << "data;" << endl;




//TODO change first idx to 0
        myfile << "param n := " << 2 * numV + 2 << ";" << endl;

        myfile << "param : E :   a :=" << endl;
        for (int i = 0; i < edges.size(); i++)
            myfile << "0" << " " << i << " 1" << endl;


        for (int i = 0; i < edges.size(); i++)
            for (int j = 0; j < edges[i].size(); j++)
                myfile << i << " " << edges[i][j] << " 1" << endl;

        for (int i = 0; i < edges.size()-1; i++)
            myfile << numV + 1 + i << " " << 2 * numV+1 << " 1" << endl;

        myfile << ";" << endl;

        myfile << "end;" << endl;

    }
};



#endif //ZAD2_BGRAPH_H
