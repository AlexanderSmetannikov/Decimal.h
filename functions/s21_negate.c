#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int err = 1;
  if (result) {
    decimal_init(result);
    decimal_assignment(result, value);
    result->bits[SCALE] = reverse_bit(result->bits[SCALE], 31);
    err = 0;
  }

  return err;
}
