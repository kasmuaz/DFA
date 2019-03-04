#ifndef DFA_H_INCLUDED
#define DFA_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <exception>
#include <algorithm>
#include <map>
#include <utility>
#include <memory>
#include "State.h"

using namespace std;

class DFA
{
    vector<State> states;
    vector<int> acceptS;
    State startS;
    int start;
    int NofStates;
    vector<char> alphabet;
    map<pair<State,char>,State> transitions;
public:

    DFA(string file);
    void printDFA();
    bool Accepts(string w);
    friend void readFile(string FileName,vector<char> &alphabet,int &noState,vector<int> &acceptStates, int &startState,map<pair<State,char>,State>& transitions);

};


#endif // DFA_H_INCLUDED
