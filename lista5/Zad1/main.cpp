#include <iostream>
#include <cmath>
#include <time.h>
#include <fstream>
#include "Timer.h"
#include "GraphBackup.h"
using namespace std;
void convertToBinary(unsigned int n)
{
    if (n / 2 != 0) {
        convertToBinary(n / 2);
    }
    printf("%d", n % 2);
}



int main(int argc, char* argv[]) {

  /*  cout << "Provide k:\n";
    int k;
    cin >> k;
    HypercubeGraph graph(k);
    auto t = Timer::start();
     graph.generate("zad1.mod");
    auto t1 = Timer::stop(t);
    cout << graph.edmond_karp(0,graph.numV-1) << " Time(ms):" << t1;*/
    ofstream myfile;
    myfile.open ("zad1output100 1 14 50 rep.csv");
    myfile << "k;Avg Maxflow;Aug paths;Time" << endl;

    int repNum = 50;

    for(int i = 1;i <=14;i++){
        int end = static_cast<int>(pow(2, i)-1);
        cout << i << endl;
        for(int j = 0;j<repNum;j++){
            //cout << i <<" " << j << endl;
            auto t = Timer::start();
            HypercubeGraph graph(i);
            int maxFlow = graph.edmond_karp(0,end);
            auto t1 = Timer::stop(t);
            myfile << i << ";" << maxFlow << ";" << graph.augPathsNum << ";" << t1 << endl;

        }

    }
    myfile.close();
    return 0;

}
// init of reverse edge flow?