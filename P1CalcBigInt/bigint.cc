#include "bigint.h"

template <size_t Base>
BigInt<Base>::BigInt(long n) {
  if (n == 0) {
    sign_ = 0;
    digits_.push_back(0);
    return;
  }
  if (n < 0) {
    sign_ = -1;
    n = -n;
  } else {
    sign_ = 1;
  }
  while (n > 0) {
    digits_.push_back(n % Base);
    n /= Base;
  }
}

template <size_t Base>
BigInt<Base>::BigInt(std::string &number_str) {
  // Si es vacio
  if (number_str.empty()) {
    sign_ = 1;
    digits_.push_back(0);
    return;
  }
  std::string number_big = number_str;
  digits_.clear();
  if (number_big[0] == '-') {
    sign_ = -1;
    number_big.erase(0, 1);
  } else {
    sign_ = 1;
  }
  for (int i = number_big.size() - 1; i >= 0; i--) {
    if (isdigit(number_big[i])) {
      digits_.push_back(number_big[i] - '0');
    } else if (number_big[i] >= 'A' && number_big[i] <= 'F') {
      digits_.push_back(number_big[i] - 'A' + 10);
    } else {
      throw std::invalid_argument("Constructor(string): Invalid character");
    }
  }
}

template <size_t Base>
BigInt<Base>::BigInt(const char *number_ptr) {
  size_t size_number = std::char_traits<char>::length(number_ptr);
  // Si es vacio
  if (size_number == 0) {
    sign_ = 1;
    digits_.push_back(0);
    return;
  }
  digits_.clear();
  if (number_ptr[0] == '-') {
    sign_ = -1;
    number_ptr++;
    size_number--;
  } else {
    sign_ = 1;
  }
  for (int i = size_number - 1; i >= 0; --i) {
    if (isdigit(number_ptr[i])) {
      digits_.push_back(number_ptr[i] - '0');
    } else if (number_ptr[i] >= 'A' && number_ptr[i] <= 'F') {
      digits_.push_back(number_ptr[i] - 'A' + 10);
    } else {
      std::cout << (int)number_ptr[i] << std::endl;
      throw std::invalid_argument("Constructor(char): Invalid character");
    }
  }
}

template <size_t Base>
BigInt<Base>::BigInt(const std::vector<char> &digits_aux, const int &sign_aux) {
  char max_digit = static_cast<char>(Base);
  for (size_t i = 0; i < digits_aux.size(); i++) {
    if (digits_aux[i] >= max_digit) {
      throw std::invalid_argument("Constructor(vector): Invalid digit");
    }
  }
  digits_ = digits_aux;
  sign_ = sign_aux;
}

template <size_t Base>
BigInt<Base>::BigInt(const BigInt<Base> &number_big) {
  sign_ = number_big.sign_;
  digits_ = number_big.digits_;
}

template <size_t Base>
BigInt<Base> &BigInt<Base>::operator=(const BigInt<Base> &number_big) {
  sign_ = number_big.sign_;
  digits_ = number_big.digits_;
  return *this;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::SetSign(int sign_aux) {
  sign_ = sign_aux;
  return *this;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::SetDigits(std::vector<char> digits_aux) {
  digits_ = digits_aux;
  return *this;
}

template <size_t Base>
std::vector<char> BigInt<Base>::GetDigits() const {
  return digits_;
}

template <size_t Base>
int BigInt<Base>::GetSign() const {
  return sign_;
}


template <size_t Base>
int BigInt<Base>::sign() const {
  return sign_;
}

template <size_t Base>
size_t BigInt<Base>::size() const {
  return digits_.size();
}

template <size_t Base>
char BigInt<Base>::operator[](size_t position) const {
  if (position < 0 || position >= digits_.size()) {
    std::cout << "position: " << position << " Size " << digits_.size()
              << std::endl;
    throw std::out_of_range("operator[]: Invalid position");
  }
  return digits_[position];
}

template <size_t Base_t>
bool operator==(const BigInt<Base_t> &number_x,
                const BigInt<Base_t> &number_y) {
  BigInt<Base_t> number_x_aux = number_x;
  BigInt<Base_t> number_y_aux = number_y;
  if (number_x_aux.IsZero() && number_y_aux.IsZero()) {
    return true;
  }
  if (number_x.GetSign() != number_y.GetSign()) {
    return false;
  }
  if (number_x.GetDigits().size() != number_y.GetDigits().size()) {
    // fill with zeros
    size_t size_difference =
        std::abs(static_cast<int>(number_x.GetDigits().size()) -
                 static_cast<int>(number_y.GetDigits().size()));
    if (number_x.GetDigits().size() > number_y.GetDigits().size()) {
      number_y_aux = number_y_aux.fill_zeros(size_difference);
    } else if (number_x.GetDigits().size() < number_y.GetDigits().size()) {
      number_x_aux = number_x_aux.fill_zeros(size_difference);
    }
  }

  for (size_t i = 0; i < number_x_aux.size(); i++) {
    if (number_x_aux[i] != number_y_aux[i]) {
      return false;
    }
  }
  return true;
}

template <size_t Base>
bool BigInt<Base>::operator!=(const BigInt<Base> &number_y) const {
  return !(*this == number_y);
}

template <size_t Base_t>
bool operator>(const BigInt<Base_t> &number_x, const BigInt<Base_t> &number_y) {
  if (number_x.GetSign() > number_y.GetSign()) {
    return true;
  } else if (number_x.GetSign() < number_y.GetSign()) {
    return false;
  }
  size_t number_digit_different =
      abs(number_x.GetDigits().size() - number_y.GetDigits().size());
  BigInt<Base_t> number_y_aux;
  BigInt<Base_t> number_x_aux;
  if (number_x.GetDigits().size() > number_y.GetDigits().size()) {
    number_y_aux = number_y.fill_zeros(number_digit_different);
    number_x_aux = number_x;
  } else if (number_x.GetDigits().size() < number_y.GetDigits().size()) {
    number_x_aux = number_x.fill_zeros(number_digit_different);
    number_y_aux = number_y;
  } else {
    number_x_aux = number_x;
    number_y_aux = number_y;
  }

  for (int i = number_x_aux.GetDigits().size() - 1; i >= 0; i--) {
    if (number_x_aux.GetDigits()[i] > number_y_aux.GetDigits()[i]) {
      return number_x_aux.GetSign() == 1 ? true : false;
    } else if (number_x_aux.GetDigits()[i] < number_y_aux.GetDigits()[i]) {
      return number_x_aux.GetSign() == 1 ? false : true;
    }
  }
  return false;
}

template <size_t Base>
bool BigInt<Base>::operator>=(const BigInt<Base> &number_y) const {
  return (*this > number_y || *this == number_y);
}

template <size_t Base_t>
bool operator<(const BigInt<Base_t> &number_x, const BigInt<Base_t> &number_y) {
  return !(number_x >= number_y);
}

template <size_t Base>
bool BigInt<Base>::operator<=(const BigInt<Base> &number_y) const {
  return !(*this > number_y);
}

template <size_t Base>
bool BigInt<Base>::IsZero() const {
  // Check if the number is zero or not
  for (size_t i = 0; i < digits_.size(); i++) {
    if (digits_[i] != 0) {
      return false;
    }
  }
  return true;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::fill_zeros(unsigned number_zero) const {
  std::string number_str = this->to_string();
  number_str.insert(number_str.begin(), number_zero, '0');
  return BigInt<Base>(number_str);
}

template <size_t Base>
BigInt<Base> BigInt<Base>::Abs() const {
  BigInt<Base> number_aux = *this;
  number_aux.SetSign(1);
  return number_aux;
}

template <size_t Base>
std::string BigInt<Base>::to_string() const {
  std::string number_str;
  if (sign_ == -1) {
    number_str += '-';
  }
  for (int i = digits_.size() - 1; i >= 0; i--) {
    if (digits_[i] < 10) {
      number_str += digits_[i] + '0';
    } else {
      number_str += digits_[i] - 10 + 'A';
    }
  }
  return number_str;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator-() const {
  BigInt<Base> number_aux = *this;
  number_aux.SetSign(-number_aux.GetSign());
  return number_aux;
}

template <size_t Base_t>
BigInt<Base_t> operator+(const BigInt<Base_t> &number_x,
                         const BigInt<Base_t> &number_y) {
  int carry = 0;
  size_t number_digit_different =
      abs(number_x.GetDigits().size() - number_y.GetDigits().size());
  BigInt<Base_t> number_y_aux;
  BigInt<Base_t> number_x_aux;
  if (number_x.GetDigits().size() > number_y.GetDigits().size()) {
    number_y_aux = number_y.fill_zeros(number_digit_different);
    number_x_aux = number_x;
  } else if (number_x.GetDigits().size() < number_y.GetDigits().size()) {
    number_x_aux = number_x.fill_zeros(number_digit_different);
    number_y_aux = number_y;
  } else {
    number_x_aux = number_x;
    number_y_aux = number_y;
  }
  // We need control the sign of the result of the operands because the sign is
  // defined by the sign of the major operand
  if (number_x_aux.GetSign() != number_y_aux.GetSign()) {
    if (number_x_aux.GetSign() == -1) {
      return number_y_aux - (-number_x_aux);
    } else {
      return number_x_aux - (-number_y_aux);
    }
  }

  std::vector<char> digits_sum;
  for (size_t i = 0; i < number_x_aux.GetDigits().size(); i++) {
    int sum = number_x_aux[i] + number_y_aux[i] + carry;
    digits_sum.push_back(sum % Base_t);
    carry = sum / Base_t;
  }
  if (carry != 0) {
    digits_sum.push_back(carry);
  }
  return BigInt<Base_t>(digits_sum, number_x_aux.GetSign());
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator-(const BigInt<Base> &number_y) const {
  size_t number_digit_different =
      abs(this->GetDigits().size() - number_y.GetDigits().size());
  BigInt<Base> number_y_aux;
  BigInt<Base> number_x_aux;
  if (this->GetDigits().size() > number_y.GetDigits().size()) {
    number_y_aux = number_y.fill_zeros(number_digit_different);
    number_x_aux = *this;
  } else if (this->GetDigits().size() < number_y.GetDigits().size()) {
    number_x_aux = this->fill_zeros(number_digit_different);
    number_y_aux = number_y;
  } else {
    number_x_aux = *this;
    number_y_aux = number_y;
  }
  // Only for positive numbers and number_x_aux > number_y_aux we can control
  // this situation always

  if (number_x_aux < number_y_aux) {
    return BigInt<Base>(number_y_aux - number_x_aux).SetSign(-1);
  }
  if (number_x_aux.GetSign() == 1 && number_y_aux.GetSign() == -1) {
    return BigInt<Base>(number_x_aux + (-number_y_aux));
  } else if (number_x_aux.GetSign() == -1 && number_y_aux.GetSign() == 1) {
    return BigInt<Base>((-number_x_aux) + number_y_aux);
  } else if (number_x_aux.GetSign() == -1 && number_y_aux.GetSign() == -1) {
    return BigInt<Base>(number_x_aux + (-number_y_aux));
  }

  std::vector<char> digits_sub;
  int carry = 0;
  for (size_t i = 0; i < number_x_aux.size(); i++) {
    int sub = number_x_aux[i] - number_y_aux[i] - carry;
    if (sub < 0) {
      sub += Base;
      carry = 1;
    } else {
      carry = 0;
    }
    digits_sub.push_back(sub);
  }

  return BigInt<Base>(digits_sub, number_x_aux.GetSign());
}

template <size_t Base>
BigInt<Base> BigInt<Base>::PushBack(char number_aux) {
  digits_.push_back(static_cast<char>(number_aux));
  return *this;
}

template <size_t Base>
BigInt<Base> &BigInt<Base>::operator++() {
  BigInt<Base> One(1);
  *this = *this + One;
  return *this;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator++(int) {
  BigInt<Base> One(1);
  BigInt<Base> number_aux = *this;
  *this = *this + One;
  return number_aux;
}

template <size_t Base>
BigInt<Base> &BigInt<Base>::operator--() {
  BigInt<Base> One(1);
  *this = *this - One;
  return *this;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator--(int) {
  BigInt<Base> number_aux = *this;
  BigInt<Base> One(1);

  *this = *this - One;
  return number_aux;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator*(const BigInt<Base> &number_y) const {
  BigInt<Base> number_x_aux = this->Abs();
  BigInt<Base> number_y_aux = number_y.Abs();
  BigInt<Base> result("0");
  BigInt<Base> i("0");
  for (; i < number_y_aux; ++i) {
    result = result + number_x_aux;
  }
  if (this->GetSign() != number_y.GetSign()) {
    result = -result;
  }
  return result;
}

template <size_t Base>
BigInt<Base> operator/(const BigInt<Base> &number_x,
                       const BigInt<Base> &number_y) {
  BigInt<Base> number_x_aux = number_x.Abs();
  BigInt<Base> number_y_aux = number_y.Abs();
  BigInt<Base> result("0");
  BigInt<Base> i("0");
  // if number_y_aux is 0 we can't divide
  if (number_y_aux == result) {
    throw std::invalid_argument("Can't divide by 0");
  }
  for (; number_x_aux >= number_y_aux; ++i) {
    number_x_aux = number_x_aux - number_y_aux;
  }
  if (number_x.GetSign() != number_y.GetSign()) {
    return -i;
  }

  return i;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator%(const BigInt<Base> &number_y) const {
  BigInt<Base> number_x_aux = this->Abs();
  BigInt<Base> number_y_aux = number_y.Abs();
  BigInt<Base> result("0");
  // if number_y_aux is 0 we can't divide
  if (number_y_aux == result) {
    throw std::invalid_argument("Can't divide by 0");
  }
  for (; number_x_aux >= number_y_aux; ++result) {
    number_x_aux = number_x_aux - number_y_aux;
  }
  if (this->GetSign() == -1) {
    return -number_x_aux;
  }

  return number_x_aux;
}
template <size_t Base>
BigInt<Base> pow(const BigInt<Base> &number_x, const BigInt<Base> &number_y) {
  BigInt<Base> number_x_aux = number_x.Abs();
  BigInt<Base> number_y_aux = number_y.Abs();
  BigInt<Base> result("1");
  BigInt<Base> i("0");
  BigInt<Base> zero("0");
  BigInt<Base> two("2");
  // if number_y_aux is 0 the result is 1
  if (number_y_aux == i) {
    return result;
  }
  // if number_y is negative we can't calculate the power
  if (number_y.GetSign() == -1) {
    throw std::invalid_argument(
        "Can't calculate the power of a negative number");
  }
  for (; i < number_y_aux; ++i) {
    result = result * number_x_aux;
  }
  // number_x_aux is negative and number_y_aux is odd
  if (number_x.GetSign() == -1) {
    if (number_y_aux % two == zero) {
      return result;
    }
    return -result;
  }
  return result;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator^(const BigInt<Base> &number_y) const {
  return pow(*this, number_y);
}

template <size_t Base_aux>
std::ostream &operator<<(std::ostream &os, const BigInt<Base_aux> &number_aux) {
  std::string number_str = number_aux.to_string();
  os << number_str;
  return os;
}

template <size_t Base_t>
std::istream &operator>>(std::istream &, BigInt<Base_t> &number_x){
  std::string number_str;
  std::cin >> number_str;
  number_x = BigInt<Base_t>(number_str);
  return std::cin;
}

template <size_t Base>
BigInt<Base> BigInt<Base>::operator!() const{
  BigInt<Base> number_aux = this->Abs();
  BigInt<Base> result("1");
  BigInt<Base> i("1");
  BigInt<Base> zero("0");
  if(number_aux == zero){
    return result;
  }
  for(; i <= number_aux; ++i){
    result = result * i;
  }
  return result;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//BASE 2
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



BigInt<2>::BigInt(long n) {
  if (n == 0) {
    digits_.push_back(0);
    return;
  }
  while (n > 0) {
    digits_.push_back(n % 2);
    n /= 2;
  }
}

BigInt<2>::BigInt(std::string &number_str) {
  // Si es vacio
  if (number_str.empty()) {
    digits_.push_back(0);
    return;
  }
  std::string number_big = number_str;
  digits_.clear();

  for (int i = number_big.size() - 1; i >= 0; i--) {
    if (isdigit(number_big[i])) {
      digits_.push_back(number_big[i] - '0');
    } else {
      throw std::invalid_argument("Constructor(string): Invalid character");
    }
  }
}

BigInt<2>::BigInt(const char *number_ptr) {
  size_t size_number = std::char_traits<char>::length(number_ptr);
  // Si es vacio
  if (size_number == 0) {
    digits_.push_back(0);
    return;
  }
  digits_.clear();
  
  for (int i = size_number - 1; i >= 0; --i) {
    if (isdigit(number_ptr[i])) {
      digits_.push_back(number_ptr[i] - '0');
    } else {
      std::cout << (int)number_ptr[i] << std::endl;
      throw std::invalid_argument("Constructor(char): Invalid character");
    }
  }
}

BigInt<2>::BigInt(const std::vector<char> &digits_aux, const int &sign_aux) {
  char max_digit = static_cast<char>(2);
  for (size_t i = 0; i < digits_aux.size(); i++) {
    if (digits_aux[i] >= max_digit) {
      throw std::invalid_argument("Constructor(vector): Invalid digit");
    }
  }
  digits_ = digits_aux;
}

BigInt<2>::BigInt(const BigInt<2> &number_big) {
  digits_ = number_big.digits_;
}

BigInt<2> &BigInt<2>::operator=(const BigInt<2> &number_big) {
  digits_ = number_big.digits_;
  return *this;
}

BigInt<2> BigInt<2>::SetDigits(std::vector<char> digits_aux) {
  digits_ = digits_aux;
  return *this;
}

std::vector<char> BigInt<2>::GetDigits() const {
  return digits_;
}

int BigInt<2>::GetSign() const {
  return sign_;
}

size_t BigInt<2>::size() const {
  return digits_.size();
}

char BigInt<2>::operator[](size_t position) const {
  if (position < 0 || position >= digits_.size()) {
    std::cout << "position: " << position << " Size " << digits_.size()
              << std::endl;
    throw std::out_of_range("operator[]: Invalid position");
  }
  return digits_[position];
}


bool operator==(const BigInt<2> &number_x,
                const BigInt<2> &number_y) {
  BigInt<2> number_x_aux = number_x;
  BigInt<2> number_y_aux = number_y;
  if (number_x_aux.IsZero() && number_y_aux.IsZero()) {
    return true;
  }
  if (number_x.GetDigits().size() != number_y.GetDigits().size()) {
    // fill with zeros
    size_t size_difference = std::abs(static_cast<int>(number_x.GetDigits().size()) - static_cast<int>(number_y.GetDigits().size()));
    if (number_x.GetDigits().size() > number_y.GetDigits().size()) {
      number_y_aux = number_y_aux.fill_zeros(size_difference);
    } else if (number_x.GetDigits().size() < number_y.GetDigits().size()) {
      number_x_aux = number_x_aux.fill_zeros(size_difference);
    }
  }

  for (size_t i = 0; i < number_x_aux.size(); i++) {
    if (number_x_aux[i] != number_y_aux[i]) {
      return false;
    }
  }
  return true;
}

bool BigInt<2>::operator!=(const BigInt<2> &number_y) const {
  return !(*this == number_y);
}

bool operator>(const BigInt<2> &number_x, const BigInt<2> &number_y) {

  size_t number_digit_different =
      abs(number_x.GetDigits().size() - number_y.GetDigits().size());
  BigInt<2> number_y_aux;
  BigInt<2> number_x_aux;
  if (number_x.GetDigits().size() > number_y.GetDigits().size()) {
    number_y_aux = number_y.fill_zeros(number_digit_different);
    number_x_aux = number_x;
  } else if (number_x.GetDigits().size() < number_y.GetDigits().size()) {
    number_x_aux = number_x.fill_zeros(number_digit_different);
    number_y_aux = number_y;
  } else {
    number_x_aux = number_x;
    number_y_aux = number_y;
  }

  for (int i = number_x_aux.GetDigits().size() - 1; i >= 0; i--) {
    if (number_x_aux.GetDigits()[i] > number_y_aux.GetDigits()[i]) {
      return number_x_aux.GetSign() == 1 ? true : false;
    } else if (number_x_aux.GetDigits()[i] < number_y_aux.GetDigits()[i]) {
      return number_x_aux.GetSign() == 1 ? false : true;
    }
  }
  return false;
}

bool BigInt<2>::operator>=(const BigInt<2> &number_y) const {

}

bool operator<(const BigInt<2> &number_x, const BigInt<2> &number_y) {

}

bool BigInt<2>::operator<=(const BigInt<2> &number_y) const {

}

bool BigInt<2>::IsZero() const {

}

BigInt<2> BigInt<2>::fill_zeros(unsigned number_zero) const {

}

BigInt<2> BigInt<2>::Abs() const {

}


std::string BigInt<2>::to_string() const {

}

BigInt<2> BigInt<2>::operator-() const {

}

BigInt<2> operator+(const BigInt<2> &number_x, const BigInt<2> &number_y) {

}

BigInt<2> BigInt<2>::operator-(const BigInt<2> &number_y) const {

}

BigInt<2> BigInt<2>::PushBack(char number_aux) {

}

BigInt<2> &BigInt<2>::operator++() {

}

BigInt<2> BigInt<2>::operator++(int) {

}

BigInt<2> &BigInt<2>::operator--() {

}

BigInt<2> BigInt<2>::operator--(int) {

}

BigInt<2> BigInt<2>::operator*(const BigInt<2> &number_y) const {

}

BigInt<2> operator/(const BigInt<2> &number_x, const BigInt<2> &number_y) {

}

BigInt<2> BigInt<2>::operator%(const BigInt<2> &number_y) const {

}

BigInt<2> pow(const BigInt<2> &number_x, const BigInt<2> &number_y) {

}

BigInt<2> BigInt<2>::operator^(const BigInt<2> &number_y) const {

}

std::ostream &operator<<(std::ostream &os, const BigInt<2> &number_aux) {

}

std::istream &operator>>(std::istream &, BigInt<2> &number_x){

}

BigInt<2> BigInt<2>::operator!() const{

}
