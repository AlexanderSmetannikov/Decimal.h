#include "s21_decimal.h"
#include "suitecases.h"

void run_testcase(Suite *testcase) {
  SRunner *runner = srunner_create(testcase);
  srunner_run_all(runner, CK_NORMAL);
  srunner_free(runner);
}

void run_all_testcases() {
  Suite *list_cases[] = {suite_s21_add(),
                         suite_s21_sub(),
                         suite_s21_mul(),
                         suite_s21_div(),
                         suite_s21_mod(),
                         suite_s21_is_greater(),
                         suite_s21_is_less_or_equal(),
                         suite_s21_is_greater_or_equal(),
                         suite_s21_is_less(),
                         suite_s21_is_equal(),
                         suite_s21_is_not_equal(),
                         suite_s21_from_decimal_to_float(),
                         suite_s21_from_float_to_decimal(),
                         suite_s21_from_decimal_to_int(),
                         suite_s21_from_int_to_decimal(),
                         suite_s21_truncate(),
                         suite_s21_floor(),
                         suite_s21_negate(),
                         suite_s21_round(),
                         NULL};

  for (int i = 0; list_cases[i] != NULL; i++) {
    run_testcase(list_cases[i]);
  }
}

int main() {
  run_all_testcases();

  return 0;
}
