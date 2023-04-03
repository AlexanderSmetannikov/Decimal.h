#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int status = 1;
  if (dst) {
    decimal_init(dst);
    status = 0;
    if (src < 0) dst->bits[SCALE] = MINUS;
    dst->bits[LOW] = s21_abs(src);
  }
  return status;
}
