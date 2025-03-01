#ifndef STACK_H
#define STACK_H

template <typename T> class Stack {
private:
  int index = 0;
  int sz = 0;
  T *data;

public:
  Stack();              // shallow/bitwise copy
  Stack(const Stack &); // deep copy

  // Stack<T>& operator=(const Stack<T>&);

  T top();              // get top of stack
  void pop();           // pop top of stack
  int size();           // get the size of stack
  void push(const T &); // push to the stack
  bool empty();
  ~Stack();
};

#include "stack.cpp"

#endif