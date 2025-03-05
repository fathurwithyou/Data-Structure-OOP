#include <iostream>
#include "queue/queue.hpp"
#include "stack/stack.hpp"
#include "vector/vector.hpp"
#include "pair/pair.hpp"
#include "bitset/bitset.hpp"
using namespace std;

int main(){
    Queue<int> q;
    q.push(10);
    Queue<int> cp = q;
    cout << cp.front() << endl;

    Stack<int> s;
    s.push(99);
    cout << s.top() << endl;

    Vector<Vector<int>> v(10, Vector<int>(10));
    v[0][0] = INT_MAX;

    for(auto it = v.begin(); it != v.end(); it++){
        for(auto it2 = it->begin(); it2 != it->end(); it2++){
            cout << *it2 << " ";
        }
        cout << endl;
    }

    Pair<Pair<int, int>, int> p(Pair(99,1), 0);
    cout << p.first().first() << p.first().second() << p.second() << endl; 

    Bitset<10> b;
    Bitset<10> b2;
    // fill the bitset with 1s
    b.set();
    // fill the bitset with 0s
    b2.set(0, false);
    cout << b.to_string() << endl;
    cout << b2.to_string() << endl;
    Bitset b3 = b & b2;
    cout << b3.to_string() << endl;
    
    return 0;
}