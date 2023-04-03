#include "../s21_decimal.h"
#include "../suitecases.h"

START_TEST(decimal_add_1) {
  s21_decimal x = {{4294967295, 4294967295, 0, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 1 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_2) {
  s21_decimal x = {{20, 1, 0, 2147483648}};
  s21_decimal y = {{21, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "4294967295 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_3) {
  s21_decimal x = {{20, 1, 0, 2147483648}};
  s21_decimal y = {{21, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "41 1 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_4) {
  s21_decimal x = {{20, 1, 0, 0}};
  s21_decimal y = {{21, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "4294967295 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_5) {
  s21_decimal x = {{20, 0, 0, 2147483648}};
  s21_decimal y = {{21, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_6) {
  s21_decimal x = {{25, 1, 0, 2147483648}};
  s21_decimal y = {{21, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "4 1 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_7) {
  s21_decimal x = {{100, 0, 0, 2147483648}};
  s21_decimal y = {{100, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_8) {
  s21_decimal x = {{99, 0, 0, 0}};
  s21_decimal y = {{100, 0, 0, 2147483648}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "1 0 0 2147483648";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_9) {
  s21_decimal x = {{0, 0, 300000000, 1835008}};
  s21_decimal y = {{0, 0, 300000000, 1835008}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 6 1310720";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_add_10) {
  s21_decimal x = {{0, 0, 3000000000, 0}};
  s21_decimal y = {{0, 0, 3000000000, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = s21_add(x, y, &z);
  ck_assert_int_eq(err, 1);
}
END_TEST

START_TEST(decimal_add_11) {
  s21_decimal x = {{1, 0, 0, 1835008}};
  s21_decimal y = {{1, 0, 0, 2149318656}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_add_1) {
  s21_decimal x = {{1, 1, 1, 65536}};
  s21_decimal y = {{1, 1, 1, 65536}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "2 2 2 65536";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_add_2) {
  s21_decimal x = {{1, 1, 1, 65536}};
  s21_decimal y = {{1, 1, 1, 655360}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "1000000001 1000000001 1000000001 655360";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_add_3) {
  s21_decimal x = {{24, 1, 1, -2147418112}};
  s21_decimal y = {{1, 15, 1, 655360}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "2525163519 999999990 999999999 2148139008";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_add_4) {
  s21_decimal x = {{1, 1, 1, 655360}};
  s21_decimal y = {{1, 1, 1, -2147418112}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_add(x, y, &z);
  char ourRes[1000], expect[1000] = "999999999 999999999 999999999 2148139008";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_add() {
  Suite *suite = suite_create("s21_add");
  TCase *tcase = tcase_create("s21_add");
  suite_add_tcase(suite, tcase);

  tcase_add_test(tcase, decimal_add_1);
  tcase_add_test(tcase, decimal_add_2);
  tcase_add_test(tcase, decimal_add_3);
  tcase_add_test(tcase, decimal_add_4);
  tcase_add_test(tcase, decimal_add_5);
  tcase_add_test(tcase, decimal_add_6);
  tcase_add_test(tcase, decimal_add_7);
  tcase_add_test(tcase, decimal_add_8);
  tcase_add_test(tcase, decimal_add_9);
  tcase_add_test(tcase, decimal_add_10);
  tcase_add_test(tcase, decimal_add_11);
  tcase_add_test(tcase, verter_add_1);
  tcase_add_test(tcase, verter_add_2);
  tcase_add_test(tcase, verter_add_3);
  tcase_add_test(tcase, verter_add_4);

  return suite;
}
