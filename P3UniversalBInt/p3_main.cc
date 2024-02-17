#include <iostream>

#include "number.h"


int main() {
//Probar la clase abstracta Number
  Number* n1 = Number::create(16, "010");
  Number* n2 = Number::create(10, "011");
  //Check OUTPUT
  std::cout << *n1 << std::endl;
  std::cout << *n2 << std::endl;
  std::cout << *n1->add(n2) << std::endl;
  return 0;
}