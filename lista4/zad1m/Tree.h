//
// Created by konra on 03.05.2019.
//
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#ifndef ZAD1_TREE_H
#define ZAD1_TREE_H

#include <iostream>
#include <math.h>
#include "timer.h"
using namespace std;
class Tree {
public:
    unsigned long long int cmp = 0,mod = 0,insCmp = 0,insNum = 0, srNum = 0,delNum = 0,
                            insMod = 0,srCmp = 0,delCmp = 0,delMod = 0;
    double insTime = 0, srTime = 0,delTime = 0;
    virtual void insertWrapper(string input ) = 0;
    virtual void deleteWrapper(string input) = 0;
    virtual void searchWrapper(string input) = 0;
    virtual void inorderWrapper() = 0;
    void iter(string fileName, void (Tree::*operation)(string)){
            ifstream file(fileName);
            string word;
            long int n = 0;
            while(file >> word) {

                for (auto c : word) {
                    if (!ispunct(c) || c == '`') {
                        (*this.*operation)(word);

                    }
                }
               n++;
                if(n%1000==0)
                    cout<< n << " ";

            }

    }
    void iter2(string fileName, void (Tree::*operation)(string), void (Tree::*operationB)(string)){
        ifstream file(fileName);
        string word;
        long int n = 0;
        while(file >> word) {

            for (auto c : word) {
                if (!ispunct(c) || c == '`') {
                    (*this.*operation)(word);
                    (*this.*operationB)(word);

                }
            }
            n++;
            if(n%1000==0)
                cout<< n << " ";

        }

    }
    void load(string fileName){
        auto t = Timer::start();
        iter(fileName,(&Tree::insertWrapper));
        insTime = Timer::stop(t);
    }
    void test(string fileName){
        auto t = Timer::start();
        iter(fileName,(&Tree::insertWrapper));
        insTime = Timer::stop(t);

        t = Timer::start();
        iter(fileName,(&Tree::searchWrapper));
        srTime = Timer::stop(t);

        //this->inorderWrapper();

        t = Timer::start();
        iter(fileName,(&Tree::deleteWrapper));
        delTime = Timer::stop(t);
    }
    void balancedTest(string fileName){


        auto t = Timer::start();
        optimalIter(fileName,(&Tree::insertWrapper),50000,1);
        insTime = Timer::stop(t);

        t = Timer::start();
        optimalIter(fileName,(&Tree::searchWrapper),50000,1);
        srTime = Timer::stop(t);

        //this->inorderWrapper();

        t = Timer::start();
        optimalIter(fileName,(&Tree::deleteWrapper),50000,1);
        delTime = Timer::stop(t);
    }





    void optimalIter(const string& fileName, void (Tree::*operation)(string),int number, int step){
        const int lines = 100000;
        string word = nLine(fileName,number);
        //cout << word << " ";
        (*this.*operation)(word);
       if(step < 13) {
           step++;
           optimalIter(fileName, (operation), number - (lines /(int) pow(2, step)), step);
           optimalIter(fileName, (operation), number + (lines /(int) pow(2, step)), step);
       }

    }
    string nLine(const std::string& filename, int N)
    {
        std::ifstream in(filename.c_str());

        std::string s;
        //for performance
        s.reserve(50);

        //skip N lines
        for(int i = 0; i < N; ++i)
            std::getline(in, s);

        std::getline(in,s);
        return s;
    }
};


#endif //ZAD1_TREE_H
