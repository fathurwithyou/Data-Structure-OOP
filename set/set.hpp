#ifndef SET_HPP
#define SET_HPP

#include <stdexcept>

// Reference: https://en.cppreference.com/w/cpp/container/set
template <typename T>
class Set {
 public:
  // Ctor & Dtor
  Set();
  ~Set();
  Set(const Set& other);
  Set& operator=(const Set& other);

  // Custom Iterator
  class Iterator {
   public:
    Iterator();
    ~Iterator();
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    const T& operator*() const;
    bool operator==(const Iterator&) const;
    bool operator!=(const Iterator&) const;
  };

  Iterator begin() const;
  Iterator end() const;

  // Capacity
  bool empty() const;
  size_t size() const;
  size_t max_size() const;

  // Modifiers
  void insert(const T& value);
  void erase(const T& value);
  void swap(Set& other);
  void clear();
  template <typename... Args>
  void emplace(Args&&... args);
  template <typename... Args>
  void emplace_hint(Args&&... args);

  // Observers
  std::function<bool(const T&, const T&)> key_comp() const;
  std::function<bool(const T&, const T&)> value_comp() const;

  // Operations
  bool contains(const T& value) const;
  size_t count(const T& value) const;
  bool find(const T& value) const;
  bool lower_bound(const T& value) const;
  bool upper_bound(const T& value) const;
  std::pair<bool, bool> equal_range(const T& value) const;
};

#endif
