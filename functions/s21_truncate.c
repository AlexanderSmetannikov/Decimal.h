#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int err = 1;
  if (result) {
    int sign = get_sign(value.bits[SCALE]);
    int exp = get_exp(value.bits[SCALE]);
    decimal_init(result);
    for (; exp > 0; exp--) {
      div10(&value);
    }
    set_exp(&value.bits[SCALE], exp);
    decimal_assignment(result, value);
    if (sign)
      result->bits[SCALE] = set_bit(result->bits[SCALE], 31);
    else
      result->bits[SCALE] = reset_bit(result->bits[SCALE], 31);
    err = 0;
  }

  return err;
}
