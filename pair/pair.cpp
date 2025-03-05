template <typename T, typename U>
Pair<T, U>::Pair() : fi(), se() {}
template <typename T, typename U>
Pair<T, U>::Pair(const T& x, const U& y) {
  fi = x;
  se = y;
}

template <typename T, typename U>
T Pair<T, U>::first() const {
  return fi;
}

template <typename T, typename U>
U Pair<T, U>::second() const {
  return se;
}

template <typename T, typename U>
Pair<T, U>::~Pair() {}