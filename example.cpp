#include <iostream>
#include "queue/queue.h"
#include "stack/stack.h"
#include "vector/vector.h"
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
    cout << v.size() << " " << v.get(0).size();
    for(int i = 0; i < v.size(); i++){
        for(int j = 0; j < v.get(0).size(); j++){
            cout << v.get(i).get(j) << " ";
        }
        cout << endl;
    }
    return 0;
}