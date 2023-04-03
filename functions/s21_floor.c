#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int err = 1;

  if (result) {
    int sign = get_sign(value.bits[SCALE]);
    decimal_init(result);
    s21_decimal one = {{1, 0, 0, 0}};
    err = s21_truncate(value, result);
    if (sign && s21_is_not_equal(value, *result)) {
      simple_add(*result, one, result);
    }
    if (sign)
      result->bits[SCALE] = set_bit(result->bits[SCALE], 31);
    else
      result->bits[SCALE] = reset_bit(result->bits[SCALE], 31);
  }

  return err;
}
