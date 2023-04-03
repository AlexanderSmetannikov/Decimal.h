#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int status = 1, scale = 0;
  double srcd = (double)src;
  int sign = get_sign_float(srcd);
  if (dst && isfinite(srcd)) {
    status = 0;
    decimal_init(dst);
    int exp = get_exp_float(srcd);
    if (exp <= 95) {
      if (srcd != 0) {
        while (!truncf(srcd)) {
          srcd *= 10;
          scale += 1;
        }
        if (scale <= 28) {
          while (!truncf(srcd / 1000000) && scale < 28) {
            srcd *= 10;
            scale += 1;
          }
          srcd = fabs(srcd);
          srcd = round_float(srcd);
          dst->bits[LOW] = srcd;
          while (is_divisible_by_10(*dst)) {
            div10(dst);
            scale--;
          }
          dst->bits[SCALE] = scale << 16;
          if (sign)
            dst->bits[SCALE] = set_bit(dst->bits[SCALE], 31);
          else
            dst->bits[SCALE] = reset_bit(dst->bits[SCALE], 31);
        } else {
          status = 1;
        }
      }
    } else {
      status = 1;
    }
  }

  return status;
}
