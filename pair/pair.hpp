#ifndef PAIR_H
#define PAIR_H

template <typename T, typename U>
class Pair {
 private:
  T fi;
  U se;

 public:
  Pair();
  Pair(const T&, const U&);
  T first() const;
  U second() const;
  ~Pair();
};

#include "pair.cpp"

#endif