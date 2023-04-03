#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  short err = 0, sign_1 = get_sign(value_1.bits[3]),
        sign_2 = get_sign(value_2.bits[3]);
  unsigned int scale = 0;
  decimal_overflow val_1 = {{value_1.bits[LOW], value_1.bits[MID],
                             value_1.bits[HIGH], 0, 0, 0}},
                   val_2 = {{value_2.bits[LOW], value_2.bits[MID],
                             value_2.bits[HIGH], 0, 0, 0}},
                   res = {0};
  scale = comparison_scale(&val_1, &val_2, value_1.bits[3], value_2.bits[3]);
  value_1.bits[3] = reset_bit(value_1.bits[3], 31);
  value_2.bits[3] = reset_bit(value_2.bits[3], 31);
  scale = reset_bit(scale, 31);
  if (!sign_1 && !sign_2) {
    if (s21_is_less(value_1, value_2)) {
      s21_sub_bin_overflow(val_2, val_1, &res);
      scale |= MINUS;
    } else if (!s21_is_equal(value_1, value_2)) {
      s21_sub_bin_overflow(val_1, val_2, &res);
    }
  } else if (sign_1 && !sign_2) {
    overflow_add(val_1, val_2, &res);
    scale |= MINUS;
  } else if (!sign_1 && sign_2) {
    overflow_add(val_1, val_2, &res);
  } else {
    if (s21_is_greater(value_1, value_2)) {
      s21_sub_bin_overflow(val_1, val_2, &res);
      scale |= MINUS;
    } else if (!s21_is_equal(value_1, value_2)) {
      s21_sub_bin_overflow(val_2, val_1, &res);
    }
  }
  err = check_max(res, scale);
  if (result) {
    if (!err) {
      decimal_init(result);
      result->bits[3] = scale;
      reverse_normalization(res, result);
      while (is_divisible_by_10(*result) && get_exp(result->bits[3]) != 0) {
        div10(result);
        result->bits[3] -= 1 << 16;
      }
    }
  }
  return err;
}
