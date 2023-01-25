CC = gcc
EFLAGS = -Wall -Wextra -Werror -std=c11 -g
CFLAGS = $(EFLAGS) -c
OFLAGS = $(EFLAGS) -o
s21_DECIMAL_C = functions/*.c
s21_DECIMAL_O = s21_*.o
S21_SUITE_C = tests/*.c
S21_SUITE_O = suite_*.o
TG_TEST_C = tg_tests/test_*.c
TG_TEST_O = test_*.o

all: clean test

s21_decimal.a:
	$(CC) $(CFLAGS) $(s21_DECIMAL_C) -lm
	ar r s21_decimal.a $(s21_DECIMAL_O)
	rm -rf *.o
	ranlib s21_decimal.a

test: s21_decimal.a
	$(CC) $(CFLAGS) $(S21_SUITE_C) main.c
	$(CC) $(OFLAGS) test $(S21_SUITE_O) main.o s21_decimal.a -lcheck -lm
	rm -rf *.o *.a
	./test

valgrind: s21_decimal.a
	$(CC) $(CFLAGS) $(S21_SUITE_C) main.c
	$(CC) $(OFLAGS) test $(S21_SUITE_O) main.o s21_decimal.a -lcheck -lm -lsubunit
	rm -rf *.o *.a
	./test

gcov_report:
	$(CC) --coverage $(CFLAGS) $(s21_DECIMAL_C)
	ar r s21_decimal.a $(s21_DECIMAL_O)
	ranlib s21_decimal.a
	$(CC) $(CFLAGS) $(S21_SUITE_C) main.c
	$(CC) --coverage $(OFLAGS) test $(S21_SUITE_O) main.o s21_decimal.a -lcheck -lm
	rm -rf *.o *.a
	./test
	# gcov s21*.gcda
	gcovr -r . --html --html-details -o report.html

check:
	cppcheck --enable=all --inconclusive --std=c11 --suppress=missingIncludeSystem ./
	clang-format -n *.c *.h

clean:
	rm -rf *.o *.a test tgtests *.gcda *.gcno *.gcov *.html *.css *.out

rebuild: clean all
