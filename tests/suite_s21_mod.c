#include "../s21_decimal.h"
#include "../suitecases.h"

START_TEST(decimal_mod_1) {
  s21_decimal x = {{150000008, 0, 0, 0}};
  s21_decimal y = {{15, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exp(&x.bits[SCALE], 3);
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "8 0 0 196608";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_mod_2) {
  s21_decimal x = {{150000008, 0, 500000000, 0}};
  s21_decimal y = {{1, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exp(&x.bits[SCALE], 3);
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "8 0 0 196608";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_mod_3) {
  s21_decimal x = {{91, 0, 0, 0}};
  s21_decimal y = {{50, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "41 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_mod_4) {
  s21_decimal x = {{91, 0, 0, 0}};
  s21_decimal y = {{95, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "91 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_mod_5) {
  s21_decimal x = {{91, 0, 0, 0}};
  s21_decimal y = {{0, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 3);
}
END_TEST

START_TEST(decimal_mod_6) {
  s21_decimal x = {{91, 0, 0, 28 << 16}};
  s21_decimal y = {{5, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  // set_exp(&x.bits[SCALE], 30);
  s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "91 0 0 1835008";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(decimal_mod_7) {
  s21_decimal x = {{125, 0, 0, 0}};
  s21_decimal y = {{3, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exp(&x.bits[SCALE], 1);
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "5 0 0 65536";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_mod_8) {
  s21_decimal x = {{125, 0, 0, 0}};
  s21_decimal y = {{3, 0, 0, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exp(&y.bits[SCALE], 1);
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "2 0 0 65536";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_mod_9) {
  s21_decimal x = {{14425, 1, 1, 0}};
  s21_decimal y = {{14425, 1, 1, 0}};
  s21_decimal z = {{0, 0, 0, 0}};
  set_exp(&x.bits[SCALE], 22);
  set_exp(&y.bits[SCALE], 22);
  int err = 0;
  err = s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(decimal_mod_10) {
  s21_decimal x = {{14425, 1, 1, 0}};
  s21_decimal y = {{14425, 1, 1, 0}};
  s21_decimal *z = NULL;
  set_exp(&x.bits[SCALE], 22);
  set_exp(&y.bits[SCALE], 22);
  int err = 0;
  err = s21_mod(x, y, z);
  ck_assert_int_eq(err, 0);
}
END_TEST

START_TEST(verter_mod_1) {
  s21_decimal x = {{1, 1, 1, 65536}};
  s21_decimal y = {{1, 1, 1, -2147418112}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_mod_2) {
  s21_decimal x = {{1, 1, 1, -2147418112}};
  s21_decimal y = {{1, 1, 1, -2146828288}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "0 0 0 0";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_mod_3) {
  s21_decimal x = {{1, 2, 3, -2147418112}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "589934595 294967296 0 2148139008";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

START_TEST(verter_mod_4) {
  s21_decimal x = {{1, 2, 3, 655360}};
  s21_decimal y = {{3, 2, 1, -2146828288}};
  s21_decimal z = {{0, 0, 0, 0}};
  s21_mod(x, y, &z);
  char ourRes[1000], expect[1000] = "4294967291 4294967293 0 655360";
  snprintf(ourRes, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(ourRes, expect);
}
END_TEST

Suite *suite_s21_mod() {
  Suite *suite = suite_create("s21_mod");
  TCase *tcase = tcase_create("case_s21_mod");

  tcase_add_test(tcase, decimal_mod_1);
  tcase_add_test(tcase, decimal_mod_2);
  tcase_add_test(tcase, decimal_mod_3);
  tcase_add_test(tcase, decimal_mod_4);
  tcase_add_test(tcase, decimal_mod_5);
  tcase_add_test(tcase, decimal_mod_6);
  tcase_add_test(tcase, decimal_mod_7);
  tcase_add_test(tcase, decimal_mod_8);
  tcase_add_test(tcase, decimal_mod_9);
  tcase_add_test(tcase, decimal_mod_10);
  tcase_add_test(tcase, verter_mod_1);
  tcase_add_test(tcase, verter_mod_2);
  tcase_add_test(tcase, verter_mod_3);
  tcase_add_test(tcase, verter_mod_4);

  suite_add_tcase(suite, tcase);

  return suite;
}
