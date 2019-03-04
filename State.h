#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <vector>
using namespace std;
class State
{
    vector<int> v;
    bool start = false;
    bool accept = false;


public:
    State(vector<int> p);
    State(vector<int> p,bool s, bool a);
    State();
    vector<int> GetState() const;
    bool IsAccept();
    bool operator <(const State& rhs) const;
    void print();
};

#endif // STATE_H_INCLUDED
