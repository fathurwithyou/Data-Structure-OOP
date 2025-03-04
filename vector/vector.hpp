#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>

template <typename T>
class Vector {
 private:
  int index;
  int sz;
  T *data;
  void resize_();

 public:
  class Iterator {
   private:
    T *ptr;

   public:
    Iterator(T *p) : ptr(p) {}
    // i++
    Iterator &operator++(int) {
      Iterator tmp(*this);
      ptr++;
      return tmp;
    }
    // ++i
    Iterator operator++() { return Iterator(++ptr); }
    Iterator operator--() { return Iterator(--ptr); }
    T operator*() { return *ptr; }
    T *operator->() { return ptr; }
    bool operator==(const Iterator &it) { return ptr == it.ptr; }
    bool operator!=(const Iterator &it) { return ptr != it.ptr; }
  };

  Vector();
  Vector(const Vector<T> &);
  Vector(int);
  Vector(int, const T &);

  T &operator[](const int &);
  Vector<T> &operator=(const Vector<T> &);

  int size() const;
  void push_back(const T &);
  void pop_back();  // delete back element (not literal)
  void resize(const int &);
  void assign(const int &, const T &);  // change the size and value
  Iterator begin();
  Iterator end();
  void reverse();
  ~Vector();
};

#include "vector.cpp"

#endif
