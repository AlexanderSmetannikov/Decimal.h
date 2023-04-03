#include "../s21_decimal.h"
#include "../suitecases.h"

START_TEST(test_from_float_to_dec_1) {
  float src = 56.986;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "56986 0 0 196608";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(test_from_float_to_dec_2) {
  float src = 1.0 / 0.0;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 1);
}
END_TEST

START_TEST(test_from_float_to_dec_3) {
  float src = -1.596;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "1596 0 0 2147680256";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(test_from_float_to_dec_4) {
  float src = 1 / 0.0;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 1);
}
END_TEST

START_TEST(test_from_float_to_dec_5) {
  double src = 0;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(test_from_float_to_dec_6) {
  long double src = 0;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(test_from_float_to_dec_7) {
  float src = 1612354.986;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "1612355 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(test_from_float_to_dec_8) {
  float src = 124.4;
  int error = 0;
  error = s21_from_float_to_decimal(src, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(test_from_float_to_dec_9) {
  float src = 0.000000986;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "986 0 0 589824";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

Suite *suite_s21_from_float_to_decimal() {
  Suite *suite = suite_create("s21_from_float_to_decimal");
  TCase *tcase = tcase_create("case_s21_from_float_to_decimal");

  tcase_add_test(tcase, test_from_float_to_dec_1);
  tcase_add_test(tcase, test_from_float_to_dec_2);
  tcase_add_test(tcase, test_from_float_to_dec_3);
  tcase_add_test(tcase, test_from_float_to_dec_4);
  tcase_add_test(tcase, test_from_float_to_dec_5);
  tcase_add_test(tcase, test_from_float_to_dec_6);
  tcase_add_test(tcase, test_from_float_to_dec_7);
  tcase_add_test(tcase, test_from_float_to_dec_8);
  tcase_add_test(tcase, test_from_float_to_dec_9);

  suite_add_tcase(suite, tcase);

  return suite;
}
