// Clase absctra que representa un numero que pretende servi para
// una clase bigint que ya esta creada y que se pueda trabajar en tiempo
// de ejecucion con numeros de cualquie base

#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include <string>

//Forward declaration
template <size_t Base> class BigInt;
template<> class BigInt<2>;

class Number {
  // Destructor
 public:
  // Metodos virtuales puras aritmeticas
  virtual Number* add(const Number*) const = 0;
  virtual Number* subtract(const Number*) const = 0;
  virtual Number* multiply(const Number*) const = 0;
  virtual Number* divide(const Number*) const = 0;
  virtual Number* module(const Number*) const = 0;
  virtual Number* pow(const Number*) const = 0;

  


  //Falta esto
 // virtual Number& operator=(const Number&) = 0;

  // Operationg of change of base
  virtual operator BigInt<2>() const = 0;
  virtual operator BigInt<8>() const = 0;
  virtual operator BigInt<10>() const = 0;
  virtual operator BigInt<16>() const = 0;
  /*
*/

  // output and input
  virtual std::ostream& write(std::ostream&) const = 0;
  virtual std::istream& read(std::istream&) = 0;
  friend std::ostream& operator<<(std::ostream&, const Number&);
  friend std::istream& operator>>(std::istream&, Number&);
  static Number* create(size_t base, const std::string& );

 private:
  // Create
};


/*
std::ostream& operator<<(std::ostream& os, const Number& number) {
  return number.write(os);
}

std::istream& operator>>(std::istream& is, Number& number) {
  return number.read(is);
}

 Number* Number::create(size_t base, const std::string& s) {
    std::string s1 = s;
     switch (base) {
    case 2:
      return new BigInt<2>(s1);
    case 8:
      return new BigInt<8>(s1);
    case 10:
      return new BigInt<10>(s1);
    case 16:
      return new BigInt<16>(s1);
    default:
      return nullptr;
  }
}
*/

#endif  // NUMBER_H