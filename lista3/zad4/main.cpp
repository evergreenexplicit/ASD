#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "graphsSCC.h"
#include "timer.h"
int main(int argc, char* argv[]) {
    int numV, numE, u,v;
    double weight;
    cin >> numV;
    Graph *g = new Graph(numV);
    cin >> numE;

    while(numE>0){
        cin >> u;
        cin >> v;
        g->add_edge(u-1,v-1);
        numE--;
    }

    auto t = Timer::start();
    g->tarjan();
    auto t1 = Timer::stop(t);
    g->print();
    cout << "\ntime in ms = " << t1 << endl;
    //}
}