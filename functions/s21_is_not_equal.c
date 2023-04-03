#include "../s21_decimal.h"

int s21_is_not_equal(s21_decimal number1, s21_decimal number2) {
  return !s21_is_equal(number1, number2);
}