#include "../s21_decimal.h"

int s21_is_greater(s21_decimal number1, s21_decimal number2) {
  int result = 0, flag = 0;
  int signNumber1 = get_sign(number1.bits[SCALE]);
  int signNumber2 = get_sign(number2.bits[SCALE]);
  decimal_overflow num_1 = {{number1.bits[LOW], number1.bits[MID],
                             number1.bits[HIGH], 0, 0, 0}},
                   num_2 = {{number2.bits[LOW], number2.bits[MID],
                             number2.bits[HIGH], 0, 0, 0}};
  comparison_scale(&num_1, &num_2, number1.bits[SCALE], number2.bits[SCALE]);
  if (signNumber1 == signNumber2) {
    for (int j = 5; j >= 0 && !result; j--) {
      unsigned int value1 = num_1.bits[j];
      unsigned int value2 = num_2.bits[j];
      if (!flag) {
        if (value1 > value2 && !signNumber1)
          result = 1;
        else if (value1 < value2)
          // break;
          flag++;
        if (value1 < value2 && signNumber1)
          result = 1;
        else if (value1 > value2)
          // break;
          flag++;
      }
    }
  } else if ((signNumber1 < signNumber2) &&
             !(is_zero(number1) && is_zero(number2))) {
    result = 1;
  }
  return result;
}
