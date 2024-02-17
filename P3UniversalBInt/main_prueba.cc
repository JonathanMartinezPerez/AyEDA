#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "bigint.h"
#include "calculator.h"

/*
Base = 10
N1 = 442142117615672
N2 = 46651367647546
E1 = N1 N2 +
E2 = E1 N1 N2 - +
 */
// Leer fichero con esta entrada
// Meterlo en un vector de strings excepto el primer elemento
// Meter el primer elemento en un size_t

int main(int argc, char* argv[]) {
  constexpr size_t diez = 10;
  BigInt<diez> num5(5);
  BigInt<diez> num3(3);
  BigInt<diez> num_neg3(-3);
  BigInt<diez> num_neg5(-5);
  BigInt<diez> num8(8);
  BigInt<diez> num_neg2(-2);
  BigInt<diez> num_neg8(-8);
  BigInt<diez> num2(2);
  BigInt<diez> num15(15);
  BigInt<diez> num_neg15(-15);
  BigInt<diez> num_4(4);
  BigInt<diez> num_neg4(-4);
  BigInt<diez> num_0;
  BigInt<diez> num_1(1);
  BigInt<diez> num_05("05");
  BigInt<diez> num_0_neg("-0");
  BigInt<diez> num125("125");
  BigInt<diez> num_neg125("-125");
  BigInt<diez> num25("25");
  BigInt<diez> num_10("10");
  BigInt<diez> num_600("600");
  BigInt<diez> num_200("200");
  BigInt<diez> num_025("025");

  //Prueba division
  std::cout << (num_025 >= num25) << std::endl;
  std::cout << (num125 / num25) << std::endl;
  std::cout << (num_600 / num_200) << std::endl;

  // Suma


  std::cout << std::boolalpha << ((num5 + num3) == num8) << std::endl;
  std::cout << ((-num5 + num3) == num_neg2) << std::endl;
  // Solo quiero probar las combinaciones con num5 y num3 y con signo  diferente
  // y que salga true
  std::cout << ((num5 + num3) == num8) << std::endl;
  std::cout << (((-num5) + num3) == num_neg2) << std::endl;
  std::cout << ((num5 + (-num3)) == num2) << std::endl;
  std::cout << (((-num5) + (-num3)) == num_neg8) << std::endl;
  // Cambiando el orden de los operandos
  std::cout << ((num3 + num5) == num8) << std::endl;
  std::cout << (((-num3) + num5) == num2) << std::endl;
  std::cout << ((num3 + (-num5)) == num_neg2) << std::endl;
  std::cout << (((-num3) + (-num5)) == num_neg8) << std::endl;
  // Resta

  // Ahora con la resta con num5 y num3 y con signo  diferente y que salga true
  std::cout << ((num5 - num3) == num2) << std::endl;
  std::cout << (((-num5) - num3) == num_neg8) << std::endl;
  std::cout << ((num5 - (-num3)) == num8) << std::endl;
  std::cout << (((-num5) - (-num3)) == num_neg2) << std::endl;
  // Cambiando el orden de los operandos
  std::cout << ((num3 - num5) == num_neg2) << std::endl;
  std::cout << (((-num3) - num5) == num_neg8) << std::endl;
  std::cout << ((num3 - (-num5)) == num8) << std::endl;
  std::cout << (((-num3) - (-num5)) == num2) << std::endl;

  // Multiplicacion

  // Ahora con la multiplicacion con num5 y num3 y con signo  diferente y que
  // salga true
  std::cout << ((num5 * num3) == num15) << std::endl;
  std::cout << (((-num5) * num3) == num_neg15) << std::endl;
  std::cout << ((num5 * (-num3)) == num_neg15) << std::endl;
  std::cout << (((-num5) * (-num3)) == num15) << std::endl;
  // Cambiando el orden de los operandos
  std::cout << ((num3 * num5) == num15) << std::endl;
  std::cout << (((-num3) * num5) == num_neg15) << std::endl;
  std::cout << ((num3 * (-num5)) == num_neg15) << std::endl;
  std::cout << (((-num3) * (-num5)) == num15) << std::endl;

  // Division Entera

  // Ahora con la division con num5 y num3 y con signo  diferente y que salga
  // true
  std::cout << ((num8 / num2) == num_4) << std::endl;
  std::cout << (((-num8) / num2) == num_neg4) << std::endl;
  std::cout << ((num8 / (-num2)) == num_neg4) << std::endl;
  std::cout << (((-num8) / (-num2)) == num_4) << std::endl;
  // Cambiando el orden de los operandos
  std::cout << ((num2 / num8) == num_0) << std::endl;
  std::cout << (((-num2) / num8) == num_0) << std::endl;
  std::cout << ((num2 / (-num8)) == num_0) << std::endl;
  std::cout << (((-num2) / (-num8)) == num_0) << std::endl;

  // Modulo

  // Ahora con el modulo con num5 y num3 y con signo  diferente y que salga true
  std::cout << ((num8 % num2) == num_0) << std::endl;
  std::cout << (((-num8) % num2) == num_0) << std::endl;
  std::cout << ((num8 % (-num2)) == num_0) << std::endl;
  std::cout << (((-num8) % (-num2)) == num_0) << std::endl;
  // Cambiando el orden de los operandos
  std::cout << ((num2 % num8) == num2) << std::endl;
  std::cout << (((-num2) % num8) == num_neg2) << std::endl;
  std::cout << ((num2 % (-num8)) == num2) << std::endl;
  std::cout << (((-num2) % (-num8)) == num_neg2) << std::endl;

  // Probar las comparaciones y que salga true
  std::cout << ((num5 == num_05)) << std::endl;
  std::cout << ((num_0 == num_0_neg)) << std::endl;
  std::cout << ((num3 != num_1)) << std::endl;
  std::cout << ((num5 > num3)) << std::endl;
  std::cout << ((num3 < num5)) << std::endl;
  std::cout << ((num5 >= num_05)) << std::endl;
  std::cout << ((num5 <= num_05)) << std::endl;
  // Ahora con numeros negativos y que salga true
  std::cout << ((num_neg5 < num_neg3)) << std::endl;
  std::cout << ((num_neg5 < num_05)) << std::endl;
  std::cout << ((num_neg5 < num_0)) << std::endl;
  std::cout << ((num_neg5 < num3)) << std::endl;

  // Ahora probamos las potencias y que salga true
  // por lo que tenemos que declara los resultados de las potencias
  // 5^3 = 125
  std::cout << ((num5 ^ num3) == num125) << std::endl;
  //El exponente no puede ser negativo
  //Si el exponente es 0 el resultado es 1
  std::cout << ((num5 ^ num_0) == num_1) << std::endl;
  //Si el exponente es 1 el resultado es el mismo numero
  std::cout << ((num5 ^ num_1) == num5) << std::endl;
  // Si exponente es 2 o par el resultado es positivo
  std::cout << ((num5 ^ num2) == num25) << std::endl;
  std::cout << (((-num5) ^ num2)) << std::endl;
  // Si la base es negativa y el exponente es impar el resultado es negativo
  std::cout << (((-num5) ^ num3) == num_neg125) << std::endl;

  std::cout << ((num5 ^ num_10)) << std::endl;

  std::cout << num5 << std::endl;
  std::cout << num5.fill_zeros(5) << std::endl;
  BigInt<diez> num6 = num5.fill_zeros(5);
  std::cout << num6 << std::endl;



  return 0;
}