#ifndef QUEUE_H
#define QUEUE_H
#include <stdexcept>

template <typename T> class Queue {
private:
  int index;
  int sz;
  T *data;

public:
  Queue();
  Queue(const Queue<T> &);
  void pop();
  void push(const T &);
  int size();
  T front();
  T back();
  bool empty();
  ~Queue();
};

#include "queue.cpp"

#endif