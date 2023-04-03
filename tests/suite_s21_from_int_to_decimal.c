#include "../s21_decimal.h"
#include "../suitecases.h"

START_TEST(test_from_int_to_dec_1) {
  s21_decimal decimal;
  decimal_init(&decimal);
  int i = -3000, res = 0;
  s21_from_int_to_decimal(i, &decimal);
  s21_from_decimal_to_int(decimal, &res);
  ck_assert_int_eq(i, res);
}
END_TEST

START_TEST(test_from_int_to_dec_2) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{15, 0, 0, 0}};
  int z = 15;
  s21_from_int_to_decimal(z, &x);
  char res1[1000], res2[1000];
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", x.bits[0], x.bits[1],
           x.bits[2], x.bits[3]);
  snprintf(res2, sizeof(char) * 1000, "%u %u %u %u", y.bits[0], y.bits[1],
           y.bits[2], y.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_from_int_to_dec_3) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{15, 0, 0, 2147483648}};
  int z = -15;
  s21_from_int_to_decimal(z, &x);
  char res1[1000], res2[1000];
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", x.bits[0], x.bits[1],
           x.bits[2], x.bits[3]);
  snprintf(res2, sizeof(char) * 1000, "%u %u %u %u", y.bits[0], y.bits[1],
           y.bits[2], y.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_from_int_to_dec_4) {
  s21_decimal x = {{0, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  int z = 0;
  s21_from_int_to_decimal(z, &x);
  char res1[1000], res2[1000];
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", x.bits[0], x.bits[1],
           x.bits[2], x.bits[3]);
  snprintf(res2, sizeof(char) * 1000, "%u %u %u %u", y.bits[0], y.bits[1],
           y.bits[2], y.bits[3]);
  ck_assert_str_eq(res1, res2);
}
END_TEST

START_TEST(test_from_int_to_dec_5) {
  int src = 124;
  int error = 0;
  error = s21_from_int_to_decimal(src, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

Suite *suite_s21_from_int_to_decimal() {
  Suite *suite = suite_create("s21_from_int_to_decimal");
  TCase *tcase = tcase_create("case_s21_from_int_to_decimal");

  tcase_add_test(tcase, test_from_int_to_dec_1);
  tcase_add_test(tcase, test_from_int_to_dec_2);
  tcase_add_test(tcase, test_from_int_to_dec_3);
  tcase_add_test(tcase, test_from_int_to_dec_4);
  tcase_add_test(tcase, test_from_int_to_dec_5);
  suite_add_tcase(suite, tcase);

  return suite;
}
