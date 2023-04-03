#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err = 0, scale = 0;
  decimal_overflow tmp = {{0, 0, 0, 0, 0, 0}};
  decimal_overflow res = {{0, 0, 0, 0, 0, 0}};
  for (int i = 0; i < 96; i++) {
    if (is_bit_set(value_1.bits[i / 32], i % 32)) {
      overflow_init(&tmp);
      dec_overflow_assignment(&tmp, res);
      overflow_add(tmp, left_shift_overflow(value_2, i), &res);
    }
  }
  if (get_exp(value_1.bits[3]) || get_exp(value_2.bits[3]))
    scale = (get_exp(value_1.bits[3]) + get_exp(value_2.bits[3])) << 16;
  if (get_sign(value_1.bits[3]) || get_sign(value_2.bits[3])) {
    if (!(get_sign(value_1.bits[3]) && get_sign(value_2.bits[3]))) {
      scale |= MINUS;
    }
  }
  err = check_max(res, scale);
  if (result) {
    if (!err) {
      decimal_init(result);
      result->bits[3] = scale;
      reverse_normalization(res, result);
      if (is_zero(*result)) {
        if (get_exp(result->bits[3]) >= 28) err = 1;
        decimal_init(result);
      } else {
        while (is_divisible_by_10(*result) && get_exp(result->bits[3]) != 0) {
          div10(result);
          result->bits[3] -= 1 << 16;
        }
      }
    }
  }
  return err;
}
