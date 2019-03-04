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
#include "DFA.h"

using namespace std;

void readFile(string FileName,vector<char> &alphabet,int &noState,vector<int> &acceptStates, int &startState,map<pair<State,char>,State>& transitions)
{
    std::ifstream ulazni_tok(FileName);

    if(!ulazni_tok)
        throw std::domain_error("Nije uspjelo ucitavanje fajla " +FileName + "!\n");
    else
    {

        std::string red_datoteke;
        int linija = 0;
        while(std::getline(ulazni_tok, red_datoteke))
        {
            if(linija == 0)
            {
                int i = 0;
                while(red_datoteke[i] != ':')
                    i++;

                for(int j = i+1; j < red_datoteke.size(); j++)
                {
                    if(red_datoteke[j] == ' ' || red_datoteke[j] == ',')
                        continue;
                    alphabet.push_back(red_datoteke[j]);
                }
                linija++;
            }
            else if(linija == 1)
            {
                int i = 0;
                while(red_datoteke[i] != ':')
                    i++;

                for(int j = i+1; j < red_datoteke.size(); j++)
                {
                    if(red_datoteke[j] == ' ')
                        continue;
                    noState = red_datoteke[j] - '0';
                }
                linija++;
            }

            else if(linija == 2)
            {

                int i = 0;
                while(red_datoteke[i] != ':')
                    i++;

                for(int j = i+1; j < red_datoteke.size(); j++)
                {
                    if(red_datoteke[j] == ' ')
                        continue;

                    if(red_datoteke[j] == '(')
                    {
                        j++;
                        int k;
                        k = red_datoteke[j];
                        j+=2;
                        char z;
                        z = red_datoteke[j];
                        j+=2;
                        int l;
                        l =red_datoteke[j];
                        j+=2;
                        vector<int> pom1;
                        pom1.push_back(k-'0');
                        vector<int> pom2;
                        pom2.push_back(l-'0');

                        State s(pom1);
                        State p(pom2);
                        transitions[pair<State,char>(s,z)] = p;
                    }
                }
                linija++;
            }
            else if(linija == 3)
            {
                int i = 0;
                while(red_datoteke[i] != ':')
                    i++;

                for(int j = i+1; j < red_datoteke.size(); j++)
                {
                    if(red_datoteke[j] == ' ')
                        continue;
                    startState = red_datoteke[j] - '0';
                }
                linija++;
            }
            else
            {
                int i = 0;
                while(red_datoteke[i] != ':')
                    i++;

                for(int j = i+1; j < red_datoteke.size(); j++)
                {
                    if(red_datoteke[j] == ' ' || red_datoteke[j] ==',')
                        continue;
                    acceptStates.push_back(red_datoteke[j]-'0');
                }
                linija++;
            }
        }
    }
    ulazni_tok.close();
}


DFA::DFA(string file)
{
    try
    {
        readFile(file,alphabet,NofStates,acceptS,start,transitions);
    }
    catch(const std::exception& e)
    {
        std::cout << e.what();
    }
    sort(acceptS.begin(),acceptS.end());
    for(int i = 0; i < NofStates*alphabet.size(); i++)
    {
        bool flag1 = false;
        if(binary_search(acceptS.begin(),acceptS.end(),i+1))
            flag1 = true;
        bool flag2 = false;
        if(start==i+1)
        {
            flag2 = true;
        }
        vector<int> v;
        v.push_back(i+1);
        auto p = make_shared<State>(v,flag2,flag1);
        if (flag2)
            startS = *p;
        states.push_back(*p);
    }

}
void DFA::printDFA()
{
    cout << "Broj stanja je " << NofStates << ".\n" <<"Pocetno stanje je: " << start << ".\n"<<"Zavrsna stanja su: ";
    for(auto x : acceptS)
        cout << x << " ";
    cout << "\nAlfabet je: ";
    for(auto x : alphabet)
        cout << x << " ";
    cout << " \nTranzcija je data sa:\n";
    for(auto x : transitions)
    {
        auto p = x.first.first.GetState();
        auto q = x.first.second;
        auto z = x.second.GetState();
        cout <<"("<< p[0] << "," << q << "," << z[0]<<")\n";
    }
    cout << "*******************\n Stanja su:\n";
    for(auto x : states)
        x.print();



}
bool DFA::Accepts(string w)
{
    if(w.length() == 0)
        return startS.IsAccept();

    State x =  transitions[pair<State,char>(startS,w[0])];

    for(int i = 1; i < w.length(); i++)
        x = transitions[pair<State,char>(x,w[i])];


    for(int i = 0; i < NofStates; i++)
        if(states[i].GetState()[0] == x.GetState()[0])
        {
            x = states[i];
        }
    if(x.IsAccept())
        return true;
    else
        return false;

}



















