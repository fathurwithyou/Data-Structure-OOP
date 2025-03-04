template <std::size_t N>
class Bitset<N>::reference {
 private:
  uint64_t& word;
  std::size_t bit_index;

 public:
  reference(uint64_t& w, std::size_t index) : word(w), bit_index(index) {}

  operator bool() const { return (word & (1ULL << bit_index)) != 0; }

  reference& operator=(bool value) {
    if (value)
      word |= (1ULL << bit_index);
    else
      word &= ~(1ULL << bit_index);
    return *this;
  }

  reference& operator=(const reference& other) {
    *this = static_cast<bool>(other);
    return *this;
  }

  reference& flip() {
    word ^= (1ULL << bit_index);
    return *this;
  }
};

template <std::size_t N>
Bitset<N>::Bitset() : bits{} {}

template <std::size_t N>
Bitset<N>::~Bitset() {}

template <std::size_t N>
bool Bitset<N>::operator==(const Bitset& other) const {
  for (std::size_t i = 0; i < num_words; ++i) {
    if (bits[i] != other.bits[i]) return false;
  }
  return true;
}

template <std::size_t N>
bool Bitset<N>::operator!=(const Bitset& other) const {
  return !(*this == other);
}

template <std::size_t N>
typename Bitset<N>::reference Bitset<N>::operator[](std::size_t pos) {
  if (pos >= N) throw std::out_of_range("Bitset index out of range");
  std::size_t word_index = pos / 64;
  std::size_t bit_index = pos % 64;
  return reference(bits[word_index], bit_index);
}

template <std::size_t N>
bool Bitset<N>::test(std::size_t pos) const {
  if (pos >= N) throw std::out_of_range("Bitset index out of range");
  std::size_t word_index = pos / 64;
  std::size_t bit_index = pos % 64;
  return (bits[word_index] & (1ULL << bit_index)) != 0;
}

template <std::size_t N>
bool Bitset<N>::all() const {
  for (std::size_t i = 0; i < num_words; ++i) {
    uint64_t mask = ~0ULL;
    if (i == num_words - 1 && (N % 64) != 0) {
      mask = (1ULL << (N % 64)) - 1;
    }
    if ((bits[i] & mask) != mask) {
      return false;
    }
  }
  return true;
}

template <std::size_t N>
bool Bitset<N>::any() const {
  for (std::size_t i = 0; i < num_words; ++i) {
    if (bits[i] != 0) return true;
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
  for (std::size_t i = 0; i < num_words; ++i) {
    uint64_t x = bits[i];
    while (x) {
      result += x & 1ULL;
      x >>= 1;
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
  for (std::size_t i = 0; i < num_words; ++i) bits[i] &= other.bits[i];
  return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::operator|=(const Bitset& other) {
  for (std::size_t i = 0; i < num_words; ++i) bits[i] |= other.bits[i];
  return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::operator^=(const Bitset& other) {
  for (std::size_t i = 0; i < num_words; ++i) bits[i] ^= other.bits[i];
  return *this;
}

template <std::size_t N>
Bitset<N> Bitset<N>::operator~() const {
  Bitset result;
  for (std::size_t i = 0; i < num_words; ++i) result.bits[i] = ~bits[i];
  if (N % 64 != 0) {
    uint64_t mask = (1ULL << (N % 64)) - 1;
    result.bits[num_words - 1] &= mask;
  }
  return result;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::operator<<=(std::size_t pos) {
  if (pos >= N) {
    std::fill(bits.begin(), bits.end(), 0);
    return *this;
  }
  Bitset tmp;
  std::size_t word_shift = pos / 64;
  std::size_t bit_shift = pos % 64;
  for (std::size_t i = num_words; i > 0; --i) {
    std::size_t src_index =
        (i - 1 >= word_shift) ? (i - 1 - word_shift) : num_words;
    uint64_t val = 0;
    if (src_index < num_words) {
      val = bits[src_index] << bit_shift;
      if (bit_shift > 0 && src_index > 0)
        val |= bits[src_index - 1] >> (64 - bit_shift);
    }
    tmp.bits[i - 1] = val;
  }
  *this = tmp;
  return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::operator>>=(std::size_t pos) {
  if (pos >= N) {
    std::fill(bits.begin(), bits.end(), 0);
    return *this;
  }
  Bitset tmp;
  std::size_t word_shift = pos / 64;
  std::size_t bit_shift = pos % 64;
  for (std::size_t i = 0; i < num_words; ++i) {
    std::size_t src_index = i + word_shift;
    uint64_t val = 0;
    if (src_index < num_words) {
      val = bits[src_index] >> bit_shift;
      if (bit_shift > 0 && src_index + 1 < num_words)
        val |= bits[src_index + 1] << (64 - bit_shift);
    }
    tmp.bits[i] = val;
  }
  *this = tmp;
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
  for (std::size_t i = 0; i < num_words; ++i) bits[i] = ~0ULL;
  if (N % 64 != 0) {
    uint64_t mask = (1ULL << (N % 64)) - 1;
    bits[num_words - 1] = mask;
  }
  return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::set(std::size_t pos, bool value) {
  if (pos >= N) throw std::out_of_range("Bitset index out of range");
  std::size_t word_index = pos / 64;
  std::size_t bit_index = pos % 64;
  if (value)
    bits[word_index] |= (1ULL << bit_index);
  else
    bits[word_index] &= ~(1ULL << bit_index);
  return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::reset() {
  std::fill(bits.begin(), bits.end(), 0);
  return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::reset(std::size_t pos) {
  return set(pos, false);
}

template <std::size_t N>
Bitset<N>& Bitset<N>::flip() {
  for (std::size_t i = 0; i < num_words; ++i) bits[i] = ~bits[i];
  if (N % 64 != 0) {
    uint64_t mask = (1ULL << (N % 64)) - 1;
    bits[num_words - 1] &= mask;
  }
  return *this;
}

template <std::size_t N>
Bitset<N>& Bitset<N>::flip(std::size_t pos) {
  if (pos >= N) throw std::out_of_range("Bitset index out of range");
  std::size_t word_index = pos / 64;
  std::size_t bit_index = pos % 64;
  bits[word_index] ^= (1ULL << bit_index);
  return *this;
}

template <std::size_t N>
std::string Bitset<N>::to_string() const {
  std::string result;
  result.reserve(N);
  for (std::size_t i = N; i > 0; --i) {
    std::size_t pos = i - 1;
    std::size_t word_index = pos / 64;
    std::size_t bit_index = pos % 64;
    result.push_back((bits[word_index] & (1ULL << bit_index)) ? '1' : '0');
  }
  return result;
}

template <std::size_t N>
unsigned long Bitset<N>::to_ulong() const {
  if (N > sizeof(unsigned long) * 8)
    throw std::overflow_error("Bitset to_ulong overflow");
  unsigned long result = 0;
  for (std::size_t pos = 0; pos < N; ++pos) {
    if (test(pos)) result |= (1UL << pos);
  }
  return result;
}

template <std::size_t N>
unsigned long long Bitset<N>::to_ullong() const {
  if (N > sizeof(unsigned long long) * 8)
    throw std::overflow_error("Bitset to_ullong overflow");
  unsigned long long result = 0;
  for (std::size_t pos = 0; pos < N; ++pos) {
    if (test(pos)) result |= (1ULL << pos);
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
  if (str.size() != N)
    throw std::invalid_argument(
        "Input string length does not match Bitset size");
  for (std::size_t i = 0; i < N; ++i) b.set(N - 1 - i, str[i] == '1');
  return is;
}