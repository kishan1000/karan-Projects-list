#include "../include/my_impl.hpp"
#include <cmath>
#include <mpfr.h>

void __gmp_exp(mpf_class &result, const mpf_class base, const mpf_class exp) {
  mpfr_t mpfr_result, mpfr_base, mpfr_exp;
  mpfr_init2(
      mpfr_result,
      base.get_prec()); // initalized result and set result in type of mpfr
  mpfr_init_set_f(mpfr_base, base.get_mpf_t(),
                  MPFR_RNDN); // initialized and set base in type of mpfr
  mpfr_init_set_f(mpfr_exp, exp.get_mpf_t(),
                  MPFR_RNDN); // initialized and set exp in type of mpfr

  mpfr_pow(mpfr_result, mpfr_base, mpfr_exp,
           MPFR_RNDN); // the real exponanitaion

  mpfr_get_f(result.get_mpf_t(), mpfr_result,
             MPFR_RNDN); // storing result from mpfr typr to mpf type

  mpfr_clear(mpfr_result); // clearing mpfr related variable
  mpfr_clear(mpfr_base);   // clearing mpfr related variable
  mpfr_clear(mpfr_exp);    // clearing mpfr related variable
  return;
}

mpf_class __calculate_pi(const long n) {
  mpf_set_default_prec(n);
  long x = 0, y;

  mpf_class num, dnum, ans, final_sum = mpf_class(0.0);
  mpz_class six_n_fact, num_first_const = mpz_class(13591409),
                        num_second_const = mpz_class(545140134),
                        minus_one = mpz_class(-1), six = mpz_class(6), six_x,
                        minus_one_x; // numerator related variables

  mpz_class dnum_const = mpz_class(640320), n_fact, n_fact_cube, three_n_fact,
            dnum_const_three_n;
  mpf_class final_dnum_const;
  __gmp_exp(final_dnum_const, mpf_class(dnum_const), mpf_class(1.5));

  for (x = 0; x <= n; x++) {
    mpz_class mpz_x(x);

    // six_x = six * mpz_x;
    mpz_fac_ui(six_n_fact.get_mpz_t(), (6 * x));
    num = std::pow(-1, x) * six_n_fact *
          (num_first_const + (num_second_const * x));

    // dnum operations
    mpz_fac_ui(n_fact.get_mpz_t(), x);
    mpz_pow_ui(n_fact_cube.get_mpz_t(), n_fact.get_mpz_t(), 3);
    mpz_fac_ui(three_n_fact.get_mpz_t(), 3 * x);
    mpz_pow_ui(dnum_const_three_n.get_mpz_t(), dnum_const.get_mpz_t(), 3 * x);
    dnum = n_fact_cube * three_n_fact * dnum_const_three_n;

    final_sum += num / dnum;
  }

  ans = final_dnum_const / (mpf_class(12) * final_sum);
  return ans;
}

std::string calculate_pi(long n, bool full) {
  long _p;
  std::string result = __calculate_pi(n).get_str(_p);

  long tries = 2;
  while (result.length() <= n) {
    result = __calculate_pi(tries * n).get_str(_p);
    tries++;
  }

  if (!full)
    result = result.substr(0, n + 1);

  return result.insert(1, 1, '.');
}