#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int status = 1;
  if (dst) {
    status = 0;
    int exp = get_exp(src.bits[SCALE]);
    int sign = get_sign(src.bits[SCALE]);
    long double res = 0;

    for (int i = 0; i < 95; i++) {
      if (is_bit_set(src.bits[i / 31], i % 31)) res += pow(2, i);
    }

    while (exp > 0) {
      res /= 10;
      exp--;
    }
    if (sign) res *= -1;
    *dst = res;
  }
  return status;
}
