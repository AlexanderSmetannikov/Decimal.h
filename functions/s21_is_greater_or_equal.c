#include "../s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal number1, s21_decimal number2) {
  return !s21_is_less(number1, number2);
}
