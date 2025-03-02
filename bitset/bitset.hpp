#ifndef BITSET_HPP
#define BITSET_HPP

#include <cstddef>
#include <string>
#include <stdexcept>

// Bitset class implementation based on https://en.cppreference.com/w/cpp/utility/bitset
template <std::size_t N>
class Bitset {
 public:
  class reference;

  Bitset();
  ~Bitset();

  bool operator==(const Bitset& other) const;
  bool operator!=(const Bitset& other) const;

  reference operator[](std::size_t pos);
  bool test(std::size_t pos) const;
  bool all() const;
  bool any() const;
  bool none() const;
  std::size_t count() const;

  std::size_t size() const;

  Bitset& operator&=(const Bitset& other);
  Bitset& operator|=(const Bitset& other);
  Bitset& operator^=(const Bitset& other);
  Bitset operator~() const;
  Bitset& operator<<=(std::size_t pos);
  Bitset& operator>>=(std::size_t pos);
  Bitset operator<<(std::size_t pos) const;
  Bitset operator>>(std::size_t pos) const;

  Bitset& set();
  Bitset& set(std::size_t pos, bool value = true);
  Bitset& reset();
  Bitset& reset(std::size_t pos);
  Bitset& flip();
  Bitset& flip(std::size_t pos);

  std::string to_string() const;
  unsigned long to_ulong() const;
  unsigned long long to_ullong() const;
};

template <std::size_t N>
Bitset<N> operator&(const Bitset<N>& lhs, const Bitset<N>& rhs);

template <std::size_t N>
Bitset<N> operator|(const Bitset<N>& lhs, const Bitset<N>& rhs);

template <std::size_t N>
Bitset<N> operator^(const Bitset<N>& lhs, const Bitset<N>& rhs);

template <std::size_t N>
std::ostream& operator<<(std::ostream& os, const Bitset<N>& b);

template <std::size_t N>
std::istream& operator>>(std::istream& is, Bitset<N>& b);

#endif
