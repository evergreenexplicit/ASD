#include <iostream>
#include <time.h>
#include <fstream>
#include "BGraph.h"
#include "Timer.h"
//testy dla 5 10 15
// zad2 testy dla 5 10 15 i zrobienie tego
int main(int argc, char* argv[]) {
    std::srand(time(0));
    cout << "Provide k and number of edges per V1 vertex:\n";
    int k,edgesNum;
    cin >> k,edgesNum;
    auto t = Timer::start();
    BGraph graph(8,5);
    auto t1 = Timer::stop(t);
    graph.generate("zad2model.mod");
    cout <<graph.hopcroft_karp() << " Time:" << t1 << endl;
    /*ofstream myfile;
    myfile.open ("zad2output.csv");*/
   /* myfile << "k;i;Max match;Time" << endl;
    int repsNum = 500;
    for(int i = 3;i<=10;i++){
        cout << i << endl;
        for(int j = 1;j<=i;j++){
            for(int rep = 0; rep<repsNum;rep++){
                auto t = Timer::start();
                BGraph graph(i,j);
                int match = graph.hopcroft_karp();
                auto t1 = Timer::stop(t);
                myfile << i << ";" <<j << ";" << match << ";" << t1 << endl;
            }

        }
    }*/

}