#include "../s21_decimal.h"

int s21_is_less(s21_decimal number1, s21_decimal number2) {
  return s21_is_greater(number2, number1);
}
