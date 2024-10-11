#include <gmpxx.h>

std::tuple<mpf_class, mpf_class, mpf_class>
__binary_split(mpz_class a, mpz_class b, const long prec) {
  mpf_set_default_prec(prec);
  mpf_class Pab, Qab, Rab, big_1("10939058860032000"), big_2("545140134"),
      big_3("13591409");
  if (b == a + 1) {
    Pab = -1 * (6 * a - 5) * (2 * a - 1) * (6 * a - 1);
    mpz_class a_pow_3;
    mpz_pow_ui(a_pow_3.get_mpz_t(), a.get_mpz_t(), 3);
    Qab = big_1 * a_pow_3;
    Rab = Pab * (big_2 * a + big_3);
  } else {
    mpz_class m = (a + b) / 2;
    auto [Pam, Qam, Ram] = __binary_split(a, m, prec);
    auto [Pmb, Qmb, Rmb] = __binary_split(m, b, prec);

    Pab = Pam * Pmb;
    Qab = Qam * Qmb;
    Rab = Qmb * Ram + Pam * Rmb;
  }
  return {Pab, Qab, Rab};
}

std::string chudnovsky(const mpz_class n, const long prec) {
  mpf_set_default_prec(prec);
  auto [P1n, Q1n, R1n] = __binary_split(1, n, prec);
  long _x;
  mpz_class num1 = mpz_class("426880"), num2 = mpz_class("10005"),
            num3 = mpz_class("13591409");

  mpf_class result, num2_sqrt;
  mpf_sqrt(num2_sqrt.get_mpf_t(), mpf_class(num2).get_mpf_t());
  result = (num1 * num2_sqrt * Q1n) / (num3 * Q1n + R1n);

  return result.get_str(_x).insert(1, 1, '.');
}