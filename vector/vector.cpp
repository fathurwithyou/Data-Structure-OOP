#include "vector.h"

template <typename T>
Vector<T>::Vector() : sz(0), index(0), data(nullptr) {}

template <typename T>
Vector<T>::Vector(const Vector<T> &tmp) : sz(tmp.sz), index(tmp.index) {
  data = new T[sz];
  for (int i = 0; i < index; i++) data[i] = tmp.data[i];
}

template <typename T>
Vector<T>::Vector(int n) : sz(n), index(n), data(new T[n]) {
  for (int i = 0; i < n; i++) data[i] = 0;
}

template <typename T>
Vector<T>::Vector(int cap, const T &x) : sz(cap), index(cap), data(new T[cap]) {
  for (int i = 0; i < cap; ++i) {
    data[i] = x;
  }
}

template <typename T>
void Vector<T>::push_back(const T &x) {
  if (index == sz) {
    int nsz = (!sz) ? 1 : sz * 2;
    T *ndata = new T[nsz];
    for (int i = 0; i < index; i++) ndata[i] = data[i];

    delete[] data;
    data = ndata;
    sz = nsz;
  }
  data[index++] = x;
}

template <typename T>
int Vector<T>::size() const {
  return index;
}

template <typename T>
T Vector<T>::get(const int &i) {
  if (i >= index || i < 0) {
    throw std::runtime_error("Index out of bound.");
  }
  return data[i];
}

template <typename T>
void Vector<T>::set(const int &i, const T &val) {
  if (i >= 0 && i < index) {
    data[i] = val;
  } else {
    throw std::runtime_error("Index out of bound.");
  }
}

template <typename T>
void Vector<T>::pop_back() {
  if (!index) index--;
}

template <typename T>
void swap(T *x, T *y) {
  T tmp = *x;
  *x = *y;
  *y = tmp;
}

template <typename T>
void Vector<T>::resize(const int &nsz) {
  // just update the size if nsz < sz
  if (nsz <= sz) {
    index = nsz;
    return;
  }
  T *ndata = new T[nsz];
  for (int i = 0; i < index; i++) {
    ndata[i] = data[i];
  }
  for (int i = index; i < nsz; i++) {
    ndata[i] = T();
  }
  delete[] data;
  data = ndata;
  sz = nsz;
  index = nsz;
}

template <typename T>
void Vector<T>::reverse() {
  for (int i = 0; i < index / 2; i++) swap(&data[i], &data[index - i - 1]);
}

template <typename T>
void Vector<T>::assign(const int &nsz, const T &x) {
  if (nsz > sz) {
    T *ndata = new T[nsz];
    for (int i = 0; i < nsz; i++) ndata[i] = x;
    delete[] data;
    data = ndata;
  } else {
    for (int i = 0; i < sz; i++) data[i] = x;
  }
  index = nsz;
  sz = nsz;
}

template <typename T>
Vector<T>::~Vector() {
  delete[] data;
}