#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0;
  if (is_zero(value_2)) err = 3;

  int sign =
      is_bit_set(value_1.bits[SCALE], 31) ^ is_bit_set(value_2.bits[SCALE], 31);
  decimal_overflow res = {0};
  int scale = dividing(value_1, value_2, &res);

  if (is_overflowed(&res) && err != 3) {
    if (sign)
      err = 2;
    else
      err = 1;
  }
  if (result && err == 0) {
    result->bits[0] = res.bits[0];
    result->bits[1] = res.bits[1];
    result->bits[2] = res.bits[2];
    result->bits[3] = scale << 16;
    if (sign) result->bits[3] = set_bit(result->bits[3], 31);
  }

  return err;
}
