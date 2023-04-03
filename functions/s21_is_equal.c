#include "../s21_decimal.h"

int s21_is_equal(s21_decimal number1, s21_decimal number2) {
  int result = 1;
  decimal_overflow num_1 = {{number1.bits[LOW], number1.bits[MID],
                             number1.bits[HIGH], 0, 0, 0}},
                   num_2 = {{number2.bits[LOW], number2.bits[MID],
                             number2.bits[HIGH], 0, 0, 0}};
  comparison_scale(&num_1, &num_2, number1.bits[SCALE], number2.bits[SCALE]);
  if (get_sign(number1.bits[SCALE]) == get_sign(number2.bits[SCALE])) {
    for (int i = 5; i >= 0; i--) {
      unsigned int value1 = num_1.bits[i];
      unsigned int value2 = num_2.bits[i];
      if (value1 != value2) {
        result = 0;
      }
    }
  } else {
    if (!is_zero(number1) || !is_zero(number2)) {
      result = 0;
    }
  }
  return result;
}