#include "number.h"
#include "bigint.h"

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

//Convert and return new number 
