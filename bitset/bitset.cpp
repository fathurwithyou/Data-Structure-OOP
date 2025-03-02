#include "Bitset.hpp"

template <std::size_t N>
Bitset<N>::Bitset() : bits{} {}

template <std::size_t N>
Bitset<N>::~Bitset() {}

template <std::size_t N>
bool Bitset<N>::operator==(const Bitset& other) const {
  for (std::size_t i = 0; i < N; ++i) {
    if (bits[i] != other.bits[i]) {
      return false;
    }
  }
  return true;
}

template <std::size_t N>
bool Bitset<N>::operator!=(const Bitset& other) const {
  return !(*this == other);
}

template <std::size_t N>
typename Bitset<N>::reference Bitset<N>::operator[](std::size_t pos) {
  if (pos >= N) {
    throw std::out_of_range("Bitset index out of range");
  }
  return reference(bits[pos]);
}

template <std::size_t N>
bool Bitset<N>::test(std::size_t pos) const {
  if (pos >= N) {
    throw std::out_of_range("Bitset index out of range");
  }
  return bits[pos];
}

template <std::size_t N>
bool Bitset<N>::all() const {
  for (std::size_t i = 0; i < N; ++i) {
    if (!bits[i]) {
      return false;
    }
  }
  return true;
}

template <std::size_t N>
bool Bitset<N>::any() const {
  for (std::size_t i = 0; i < N; ++i) {
    if (bits[i]) {
      return true;
    }
  }
  return false;
}

template <std::size_t N>
bool Bitset<N>::none() const {
  return !any();
}

template <std::size_t N>
std::size_t Bitset<N>::count() const {
  std::size_t result = 0;
  for (std::size_t i = 0; i < N; ++i) {
    if (bits[i]) {
      ++result;
    }
  }
  return result;
}

template <std::size_t N>
std::size_t Bitset<N>::size() const {
  return N;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::operator&=(const Bitset& other) {
  for (std::size_t i = 0; i < N; ++i) {
    bits[i] &= other.bits[i];
  }
  return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::operator|=(const Bitset& other) {
  for (std::size_t i = 0; i < N; ++i) {
    bits[i] |= other.bits[i];
  }
  return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::operator^=(const Bitset& other) {
  for (std::size_t i = 0; i < N; ++i) {
    bits[i] ^= other.bits[i];
  }
  return *this;
}

template <std::size_t N>
Bitset<N> Bitset<N>::operator~() const {
  Bitset result;
  for (std::size_t i = 0; i < N; ++i) {
    result.bits[i] = !bits[i];
  }
  return result;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::operator<<=(std::size_t pos) {
  if (pos >= N) {
    std::fill(bits, bits + N, false);
  } else {
    for (std::size_t i = N - 1; i >= pos; --i) {
      bits[i] = bits[i - pos];
    }
    for (std::size_t i = 0; i < pos; ++i) {
      bits[i] = false;
    }
  }
  return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::operator>>=(std::size_t pos) {
  if (pos >= N) {
    std::fill(bits, bits + N, false);
  } else {
    for (std::size_t i = 0; i < N - pos; ++i) {
      bits[i] = bits[i + pos];
    }
    for (std::size_t i = N - pos; i < N; ++i) {
      bits[i] = false;
    }
  }
  return *this;
}

template <std::size_t N>
Bitset<N> Bitset<N>::operator<<(std::size_t pos) const {
  Bitset result(*this);
  result <<= pos;
  return result;
}

template <std::size_t N>
Bitset<N> Bitset<N>::operator>>(std::size_t pos) const {
  Bitset result(*this);
  result >>= pos;
  return result;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::set() {
  for (std::size_t i = 0; i < N; ++i) {
    bits[i] = true;
  }
  return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::set(std::size_t pos, bool value) {
  if (pos >= N) {
    throw std::out_of_range("Bitset index out of range");
  }
  bits[pos] = value;
  return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::reset() {
  for (std::size_t i = 0; i < N; ++i) {
    bits[i] = false;
  }
  return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::reset(std::size_t pos) {
  if (pos >= N) {
    throw std::out_of_range("Bitset index out of range");
  }
  bits[pos] = false;
  return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::flip() {
  for (std::size_t i = 0; i < N; ++i) {
    bits[i] = !bits[i];
  }
  return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::flip(std::size_t pos) {
  if (pos >= N) {
    throw std::out_of_range("Bitset index out of range");
  }
  bits[pos] = !bits[pos];
  return *this;
}

template <std::size_t N>
std::string Bitset<N>::to_string() const {
  std::string result;
  for (std::size_t i = N; i > 0; --i) {
    result += bits[i - 1] ? '1' : '0';
  }
  return result;
}

template <std::size_t N>
unsigned long Bitset<N>::to_ulong() const {
  if (N > sizeof(unsigned long) * 8) {
    throw std::overflow_error("Bitset to_ulong overflow");
  }
  unsigned long result = 0;
  for (std::size_t i = 0; i < N; ++i) {
    if (bits[i]) {
      result |= (1UL << i);
    }
  }
  return result;
}

template <std::size_t N>
unsigned long long Bitset<N>::to_ullong() const {
  if (N > sizeof(unsigned long long) * 8) {
    throw std::overflow_error("Bitset to_ullong overflow");
  }
  unsigned long long result = 0;
  for (std::size_t i = 0; i < N; ++i) {
    if (bits[i]) {
      result |= (1ULL << i);
    }
  }
  return result;
}

template <std::size_t N>
Bitset<N> operator&(const Bitset<N>& lhs, const Bitset<N>& rhs) {
  Bitset<N> result(lhs);
  result &= rhs;
  return result;
}

template <std::size_t N>
Bitset<N> operator|(const Bitset<N>& lhs, const Bitset<N>& rhs) {
  Bitset<N> result(lhs);
  result |= rhs;
  return result;
}

template <std::size_t N>
Bitset<N> operator^(const Bitset<N>& lhs, const Bitset<N>& rhs) {
  Bitset<N> result(lhs);
  result ^= rhs;
  return result;
}

template <std::size_t N>
std::ostream& operator<<(std::ostream& os, const Bitset<N>& b) {
  os << b.to_string();
  return os;
}

template <std::size_t N>
std::istream& operator>>(std::istream& is, Bitset<N>& b) {
  std::string str;
  is >> str;
  for (std::size_t i = 0; i < N; ++i) {
    b.set(N - 1 - i, str[i] == '1');
  }
  return is;
}
