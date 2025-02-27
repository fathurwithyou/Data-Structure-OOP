#include "stack.h"

template <typename T>
Stack<T>::Stack() : index(0), sz(0), data(nullptr) {}

template <typename T>
Stack<T>::Stack(const Stack<T> &tmp) : index(tmp.index), sz(tmp.sz) {
  data = new T[sz];
  for (int i = 0; i < index; i++)
    data[i] = tmp.data[i];
}

template <typename T> T Stack<T>::top() {
  if (!index)
    throw std::runtime_error("Stack is empty");

  return data[index - 1];
}

template <typename T> void Stack<T>::pop() {
  if (!index)
    index--;
}

template <typename T> int Stack<T>::size() { return sz; }

template <typename T> void Stack<T>::push(const T &x) {
  if (index == sz) {
    int nsz = (!sz) ? 1 : sz * 2;
    T *ndata = new T[nsz];
    for (int i = 0; i < index; i++)
      ndata[i] = data[i];

    delete[] data; // dealloc to prevent memory leak
    data = ndata;
    sz = nsz;
  }
  data[index++] = x;
}

template <typename T> bool Stack<T>::empty() { return index == 0; }

template <typename T> Stack<T>::~Stack() { delete[] data; }