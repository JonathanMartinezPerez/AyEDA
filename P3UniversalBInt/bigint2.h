// This file will be used to implement the class BigInt2
// that will be used to store binary numbers in a vector of bool
// The class BigInt2 will be a template class specialized for the base 2

#ifndef BIGINT2_H
#define BIGINT2_H
// we need to include the class BigInt to use it as a base class

#include <algorithm>
#include <cmath>
#include <vector>

#include "bigint.h"

template <>
class BigInt<2> : public Number {
 public:
  BigInt(long number_x = 0);
  BigInt(const BigInt<2> &other);
  BigInt(std::vector<bool> digits);
  BigInt(const std::vector<char> &, const int &);
  BigInt(std::string number_x);
  BigInt operator=(const BigInt<2> &other);

  // Conversion
  
  template <size_t base>
  BigInt<base> ConvertBaseT();

  operator BigInt<2>() const override;
  operator BigInt<8>() const override;
  operator BigInt<10>() const override;
  operator BigInt<16>() const override;

  ///Number& operator=(const Number&) override;

  // Getters and Setters
  std::vector<bool> GetDigits() const;
  BigInt<2> SetDigits(std::vector<bool> digits);

  bool operator[](size_t) const;
  size_t size() const;
  void push_back(bool digit);

  // Modifications or checks
  bool IsZero() const;
  BigInt<2> Abs() const;

  // factorial
  BigInt<2> factorial() const;
  BigInt<2> operator!() const;

  friend bool operator==(const BigInt<2> &, const BigInt<2> &);
  // Comparison operators
  bool operator!=(const BigInt<2> &other) const;
  friend bool operator>(const BigInt<2> &, const BigInt<2> &);
  bool operator>=(const BigInt<2> &other) const;
  friend bool operator<(const BigInt<2> &, const BigInt<2> &);
  bool operator<=(const BigInt<2> &other) const;

  // Increment/Decrement
  BigInt<2> &operator++();    // pre-increment
  BigInt<2> operator++(int);  // post-increment
  BigInt<2> &operator--();    // pre-decrement
  BigInt<2> operator--(int);  // post-decrement

  // arithmetic operators
  friend BigInt<2> operator+(const BigInt<2> &first, const BigInt<2> &other);
  BigInt<2> sum_overflow(const BigInt<2> &first, const BigInt<2> &other) const;
  BigInt<2> operator-() const;
  BigInt<2> operator-(const BigInt<2> &other) const;
  BigInt<2> operator*(const BigInt<2> &other) const;
  friend BigInt<2> operator/(const BigInt<2> &first, const BigInt<2> &other);
  BigInt<2> operator%(const BigInt<2> &other) const;

  friend BigInt<2> pow(const BigInt<2> &first, const BigInt<2> &other);
  BigInt<2> operator^(const BigInt<2> &other) const;

  // Displacement operators
  void operator<<(size_t n);
  void operator>>(size_t n);

  // Controlled operators
  BigInt<2> FillSign(size_t n) const;
  BigInt<2> ConvertToTwosComplement() const;

  // Input/Output
  friend std::ostream &operator<<(std::ostream &os, const BigInt<2> &number_x);

  std::string to_string() const;

  // Methods overriden from the number class
  Number *add(const Number *) const override;
  Number *subtract(const Number *) const override;
  Number *multiply(const Number *) const override;
  Number *divide(const Number *) const override;
  Number *module(const Number *) const override;
  Number *pow(const Number *) const override;

  std::ostream &write(std::ostream &) const override;
  std::istream &read(std::istream &)  override;

 private:
  void operator<<(BigInt<2> &other);
  void operator>>(BigInt<2> &other);

  std::vector<bool> digits;
};
#include "bigint2.cc"

#endif  // BIGINT2_H