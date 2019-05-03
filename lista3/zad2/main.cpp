#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "timer.h"
#include "graphs.h"
#include "PriorityQueue.h"
int main() {
    int numV, numE, u,v,start;
    double weight;
    cin >> numV;
    Graph *g = new Graph(numV);
    cin >> numE;

    while(numE>0){
        cin >> u;
        cin >> v;
        cin >> weight;
        g->add_edge(u-1,v-1,weight);
        numE--;
    }
    cin >> start;
    auto t = Timer::start();
    g->dijkstra(start-1);
    auto t1 = Timer::stop(t);
    g->print();

    cout << "\ntime in ms = " << t1 << endl;
}