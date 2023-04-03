#ifndef SUITECASES_H
#define SUITECASES_H

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Suite *suite_s21_truncate();
Suite *suite_s21_round();
Suite *suite_s21_floor();
Suite *suite_s21_negate();
Suite *suite_s21_from_decimal_to_float();
Suite *suite_s21_from_float_to_decimal();
Suite *suite_s21_from_decimal_to_int();
Suite *suite_s21_from_int_to_decimal();
Suite *suite_s21_add();
Suite *suite_s21_sub();
Suite *suite_s21_div();
Suite *suite_s21_mod();
Suite *suite_s21_mul();
Suite *suite_s21_is_less_or_equal();
Suite *suite_s21_is_less();
Suite *suite_s21_is_greater();
Suite *suite_s21_is_greater_or_equal();
Suite *suite_s21_is_equal();
Suite *suite_s21_is_not_equal();

#endif