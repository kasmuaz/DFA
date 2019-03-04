#include <iostream>
#include "State.h"
#include "DFA.h"
using namespace std;

int main()
{
    DFA dfa("ulazDFA.txt");
    dfa.printDFA();

    string w;
    cout << "Unosi stringove (kraj za kraj): ";

    while(1)
    {
        cin >> w;
        if(w == "kraj")
            break;
         if(dfa.Accepts(w))
        cout << "PRIHVATA\n";
    else
        cout << "NE PRIHVATA\n";

    }

    return 0;
}
