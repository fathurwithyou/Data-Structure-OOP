#ifndef BITSET_HPP
#define BITSET_HPP

#include <array>
#include <cstddef>
#include <stdexcept>
#include <cstdint>
#include <string>
#include <algorithm>
#include <iostream>

template <std::size_t N>
class Bitset {
private:
    static constexpr std::size_t num_words = (N + 63) / 64;
    std::array<uint64_t, num_words> bits;

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

#include "Bitset.cpp"

#endif 
