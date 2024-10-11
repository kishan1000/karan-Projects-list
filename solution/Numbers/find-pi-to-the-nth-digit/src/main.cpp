#include <gmpxx.h>
#include <iostream>
#include <optional>

#include "../include/my_impl.hpp"
#include "../include/wiki_impl.hpp"

mpf_class _calculate_pi(const long);

// Function to convert string to bool
bool stringToBool(const std::string &str) {
  if (str == "true" || str == "1") {
    return true;
  }
  if (str == "false" || str == "0") {
    return false;
  }
  throw std::invalid_argument(
      "Invalid value for boolean. Use 'true' or 'false'.");
}

int main(int argc, char *argv[]) {
  if (argc < 2 || argc > 3) {
    std::cerr << "Usage: " << argv[0]
              << " <double_value> [optional_bool(true or false)]" << std::endl;
    return 1;
  }

  // Parse the first argument as a double
  double value = std::atof(argv[1]);

  // Parse the second argument as an optional boolean (if provided)
  std::optional<bool> flag =
      std::nullopt; // Use std::optional to handle optional boolean

  if (argc == 3) {
    try {
      flag = stringToBool(argv[2]); // Convert string to bool
    } catch (const std::invalid_argument &e) {
      std::cerr << e.what() << std::endl;
      return 1;
    }
  } else {
    // If no second argument provided, set a default value (e.g., false)
    flag = false;
  }

  long n = value;
  auto ans = calculate_pi(n, flag.value());

  // if (flag) {
  //   std::cout << "PI is:" << std::endl << ans << std::endl;
  // } else {
  //   std::cout << "PI to " << n << " decimal places is: " << ans << std::endl;
  // }

  std::cout << "Chudnovsky solution:" << std::endl
            << chudnovsky(mpz_class(n), n * 4) << std::endl;
  return 0;
}