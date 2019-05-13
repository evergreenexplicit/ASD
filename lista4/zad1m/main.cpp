#include <iostream>
#include <cstring>
#include "BSTree.h"
#include "RBTree.h"
#include "splayTree.h"
#include "timer.h"
//TODO RB DO POPRAWY NULLPTR == COLOR.BLACK + czy root zrobi sie czarny sam?
int main(int argc, char* argv[]) {
    Tree* tree;
    string input;
    if(strcmp(argv[1],"--type") == 0){
        cout << "Typ:" << endl;
        input = argv[2];
        if(input == "rbt"){
            cout << "rbt" << endl;
            tree = new RBTree();
        }

        else if(input == "bst"){
            cout << "bst" << endl;
            tree = new BSTree();
        }
        else if(input == "splay"){
            cout << "splay" << endl;
            tree = new splayTree();
        }

    }
    int cmdNum;
    cout << "Podaj liczbe komend\n";
    cin >> cmdNum;
    double totalTime = 0;
    string cmd;
    while( cmdNum-->0){
        cin >> cmd;
        if(cmd == "insert"){
            cin >> cmd;
            auto t = Timer::start();
            tree->insertWrapper(cmd);
            totalTime+= Timer::stop(t);
        }
        else if(cmd == "delete") {
            cin >> cmd;
            auto t = Timer::start();
            tree->deleteWrapper(cmd);
            totalTime+= Timer::stop(t);
        }
        else if(cmd == "search") {
            cin >> cmd;
            auto t = Timer::start();
            tree->deleteWrapper(cmd);
            totalTime+= Timer::stop(t);
        }
        else if(cmd == "load") {
            cin >> cmd;
            auto t = Timer::start();
            tree->load(cmd);
            totalTime+= Timer::stop(t);
        }
        else if(cmd == "test") {
            cin >> cmd;
            auto t = Timer::start();
            tree->test(cmd);
            totalTime+= Timer::stop(t);
        }
        else if(cmd == "balancedtest"){
            cin >> cmd;
            auto t = Timer::start();
            tree->balancedTest(cmd);
            totalTime+= Timer::stop(t);
        }
        else if(cmd == "inorder") {
            auto t = Timer::start();
            tree->inorderWrapper();
            totalTime+= Timer::stop(t);
        }
    }
    long long int totalCmp = tree->insCmp + tree->delCmp + tree->srCmp;
    long long int totalMod = tree->insMod + tree->delMod;

    ofstream resultFile;
    resultFile.open("wyniki.txt", std::ios_base::app);

    resultFile << "\n\nTyp:" << input <<  endl;
    resultFile << "Total time in s = " << totalTime/1000 << endl;
    resultFile << "Insert: number " << tree->insNum
         << "\n\t cmp:" << tree->insCmp << ", " << (double)tree->insCmp/totalCmp << "%, avg " << (double) tree->insCmp/tree->insNum
         << "ms,\n\t Mod:"<< tree->insMod << ", " << (double)tree->insMod/totalMod << "%, avg" << (tree->insMod/(double)tree->insNum)
         << "\n\t Time:" << tree->insTime/1000 << ", " <<  tree->insTime/totalTime << "%, avg:" << (tree->insTime/(double)tree->insNum)<< endl;

    resultFile << "Delete: number " << tree->delNum
         << " \n\tcmp:" << tree->delCmp << ", " << (double)tree->delCmp/totalCmp << "%, avg " << (double) tree->delCmp/tree->delNum
         << "ms  \n\tMod:"<< tree->delMod << ", " << (double)tree->delMod/totalMod << "%, avg" << (tree->delMod/(double)tree->delNum)
         << " \n\tTime:" << tree->delTime/1000 << ", " <<  tree->delTime/totalTime << "%, avg:" << (tree->delTime/(double)tree->delNum) << endl;
    resultFile << "Search: number " << tree->srNum
         << " \n\tcmp:" << tree->srCmp << ", " << (double)tree->srCmp/totalCmp << "%, avg " << (double) tree->srCmp/tree->srNum
         << "\n\tTime:" << tree->srTime/1000 << ", " <<  tree->srTime/totalTime << "%, avg:" << (tree->srTime/(double)tree->srNum) << endl;

}
/* modified i compare dla insert, search i delete
 * licznik tmp a na końcu operacji dodanie do insert-/swap-/deleteNum
 * cmp w if
 * cmp w petlach
 * przypisywanie
 * operation+=cmp/mod
 *
 *
 * mod
 *
 * DONE
 * usuwanie interp jak jest przy tym tym
 * */
