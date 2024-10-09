#include <gmpxx.h>
#include <iostream>

int main() {
  // Initialize two GMP integers
  mpz_class a = 123456789;
  mpz_class b = 987654321;

  // Perform basic arithmetic operations
  mpz_class sum = a + b;
  mpz_class product = a * b;
  mpz_class difference = a - b;
  mpz_class quotient = b / a;

  // Output the results
  std::cout << "a = " << a << std::endl;
  std::cout << "b = " << b << std::endl;
  std::cout << "sum = " << sum << std::endl;
  std::cout << "product = " << product << std::endl;
  std::cout << "difference = " << difference << std::endl;
  std::cout << "quotient = " << quotient << std::endl;

  // Perform modular exponentiation (b^a % a)
  mpz_class mod_exp_result;
  mpz_powm(mod_exp_result.get_mpz_t(), b.get_mpz_t(), a.get_mpz_t(),
           a.get_mpz_t());
  std::cout << "b^a % a = " << mod_exp_result << std::endl;

  return 0;
}