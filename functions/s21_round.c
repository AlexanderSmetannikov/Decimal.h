#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int err = 1;
  int sign = get_sign(value.bits[SCALE]);
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal ten = {{10, 0, 0, 0}};
  s21_decimal tmp;
  s21_decimal mod;
  decimal_init(&tmp);
  decimal_init(&mod);
  decimal_assignment(&tmp, value);
  int scaleMask = get_exp(value.bits[SCALE]);
  if (result) {
    decimal_init(result);
    while (scaleMask > 1) {
      div10(&tmp);
      scaleMask--;
    }
    if (scaleMask == 1) {
      decimal_assignment(&value, tmp);
      div10(&tmp);
      simple_mul(tmp, ten, &tmp);
      s21_sub_bin(value, tmp, &mod);
      div10(&value);
      if (mod.bits[LOW] > 4) simple_add(value, one, &value);
      scaleMask--;
      set_exp(&(value.bits[SCALE]), scaleMask);
    }
    decimal_assignment(result, value);
    if (sign)
      result->bits[SCALE] = set_bit(result->bits[SCALE], 31);
    else
      result->bits[SCALE] = reset_bit(result->bits[SCALE], 31);
    err = 0;
  }

  return err;
}
