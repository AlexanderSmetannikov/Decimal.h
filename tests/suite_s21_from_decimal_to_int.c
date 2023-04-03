#include "../s21_decimal.h"
#include "../suitecases.h"

START_TEST(test_from_dec_to_int_1) {
  s21_decimal x = {{150, 13658, 0, 0}};
  set_exp(&(x.bits[3]), 10);
  x.bits[3] = set_bit(x.bits[3], 31);
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, -5866);
}
END_TEST

START_TEST(test_from_dec_to_int_2) {
  s21_decimal x = {{150, 13658, 0, 0}};
  set_exp(&(x.bits[3]), 10);
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 5866);
}
END_TEST

START_TEST(test_from_dec_to_int_3) {
  s21_decimal x = {{150, 13658, 155, 0}};
  set_exp(&(x.bits[3]), 10);
  int y = 0;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 0);
}
END_TEST

START_TEST(test_from_dec_to_int_4) {
  s21_decimal x = {{2100000000, 0, 0, 0}};
  set_exp(&(x.bits[3]), 0);
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 2100000000);
}
END_TEST

START_TEST(test_from_dec_to_int_5) {
  s21_decimal x = {{2100000000, 0, 0, 0}};
  set_exp(&(x.bits[3]), 0);
  x.bits[3] = set_bit(x.bits[3], 31);
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, -2100000000);
}
END_TEST

START_TEST(test_from_dec_to_int_6) {
  s21_decimal x = {{3100000000, 0, 0, 0}};
  set_exp(&(x.bits[3]), 0);
  x.bits[3] = set_bit(x.bits[3], 31);
  int y = 0;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 0);
}

START_TEST(test_from_dec_to_int_7) {
  s21_decimal x = {{3100000000, 0, 0, 0}};
  set_exp(&(x.bits[3]), 0);
  int y;
  int n1 = s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(n1, 1);
}
END_TEST

START_TEST(test_from_dec_to_int_8) {
  s21_decimal x = {{9, 0, 0, 0}};
  set_exp(&(x.bits[3]), 1);
  int y;
  s21_from_decimal_to_int(x, &y);
  ck_assert_int_eq(y, 0);
}
END_TEST

START_TEST(test_from_dec_to_int_9) {
  s21_decimal x = {{9, 0, 0, 0}};
  set_exp(&(x.bits[3]), 1);
  int y = s21_from_decimal_to_int(x, NULL);
  ck_assert_int_eq(y, 1);
}
END_TEST

Suite *suite_s21_from_decimal_to_int() {
  Suite *suite = suite_create("s21_from_decimal_to_int");
  TCase *tcase = tcase_create("case_s21_from_decimal_to_int");

  tcase_add_test(tcase, test_from_dec_to_int_1);
  tcase_add_test(tcase, test_from_dec_to_int_2);
  tcase_add_test(tcase, test_from_dec_to_int_3);
  tcase_add_test(tcase, test_from_dec_to_int_4);
  tcase_add_test(tcase, test_from_dec_to_int_5);
  tcase_add_test(tcase, test_from_dec_to_int_6);
  tcase_add_test(tcase, test_from_dec_to_int_7);
  tcase_add_test(tcase, test_from_dec_to_int_8);
  tcase_add_test(tcase, test_from_dec_to_int_9);
  suite_add_tcase(suite, tcase);

  return suite;
}
