#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>

template <typename T> class Vector {
private:
  int index;
  int sz;
  T *data;

public:
  Vector();
  Vector(const Vector<T> &);
  Vector(int);
  Vector(int, const T &);

  Vector<T>& operator=(const Vector<T>&);

  int size() const; 
  void push_back(const T &);
  void pop_back(); // delete back element (not literal)
  void resize(const int &);
  void assign(const int &, const T &); // change the size and value
  void reverse(); 
  T get(const int &);
  void set(const int &, const T &);
  ~Vector();
};

#include "vector.cpp"

#endif
