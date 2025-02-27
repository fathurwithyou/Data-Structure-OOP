#include <iostream>
#include "queue/queue.h"
#include "stack/stack.h"
#include "vector/vector.h"
using namespace std;

int main(){
    Queue<int> q;
    q.push(10);
    cout << q.front() << endl;

    Stack<int> s;
    s.push(99);
    cout << s.top() << endl;

    Vector<int> v(10);
    for(int i = 0; i < v.size(); i++){
        cout << v.get(i) << " ";
    }
}