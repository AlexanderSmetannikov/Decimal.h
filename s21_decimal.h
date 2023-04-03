#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H
#include <math.h>  // ДОБАВИТЬ ФЛАГ ДЛЯ КОМПИЛЯЦИИ
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// union float_binary {
//   float f;
//   int i;
// };

union Data {
  int i;
  float f;
};

typedef struct {
  unsigned int bits[6];
} decimal_overflow;

typedef struct {         // bits[0] младшие 32 бита
  unsigned int bits[4];  // bits[1] средние 32 бита
} s21_decimal;           // bits[2] старшие 32 бита

/* - Биты от 0 до 15, младшее слово, не используются и должны быть равны нулю
- Биты с 16 по 23 должны содержать показатель степени от 0 до 28, который
указывает степень 10 для разделения целого числа
- Биты с 24 по 30 не используются и должны быть равны нулю
- Бит 31 содержит знак; 0 означает положительный, а 1 означает отрицательный */

#define LOW 0
#define MID 1
#define HIGH 2
#define SCALE 3

#define MINUS 2147483648
#define EXP_INT_MASK 8355840
#define MASK_FLOAT_EXP 1069547520
#define MAX_DEC 4294967295

// ADDITIONAL HELP FUNCTIONS
int div10(s21_decimal *value);
int is_bit_set(int number, int index);  // check is bit in index position is 1
int set_bit(int number, int index);     // set index bit to 1
int reverse_bit(int number,
                int index);  // reverse index bit from 1 to 0 and from 0 to 1
int reset_bit(int number, int index);  // set index bit to 0
void decimal_init(s21_decimal *dst);   // create and fill 0 decimal number
int s21_abs(int number);

// ARIPHMETIC
int s21_add(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // сложение
int s21_sub(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // вычитание
int s21_mul(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // умножение
int s21_div(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // деление
int s21_mod(s21_decimal value_1, s21_decimal value_2,
            s21_decimal *result);  // остаток от деления

// COMPARISON
int s21_is_less(s21_decimal, s21_decimal);  // оператор меньше
int s21_is_less_or_equal(s21_decimal,
                         s21_decimal);  // оператор меньше или равно
int s21_is_greater(s21_decimal, s21_decimal);  // оператор больше
int s21_is_greater_or_equal(s21_decimal,
                            s21_decimal);  // оператор больше или равно
int s21_is_equal(s21_decimal, s21_decimal);      // оператор равно
int s21_is_not_equal(s21_decimal, s21_decimal);  // не равно

// FROM-TO CONVERSION
int s21_from_int_to_decimal(int src, s21_decimal *dst);  // from Int to Decimal
int s21_from_float_to_decimal(float src,
                              s21_decimal *dst);  // from Float to Decimal
int s21_from_decimal_to_int(s21_decimal src, int *dst);  // from Decimal to Int
int s21_from_decimal_to_float(s21_decimal src,
                              float *dst);  // from Decimal to Float

// OTHER
int s21_floor(
    s21_decimal value,
    s21_decimal *result); /* Округляет указанное Decimal число
    до ближайшего целого числа в сторону отрицательной бесконечности. */

int s21_round(
    s21_decimal value,
    s21_decimal *result); /* Округляет Decimal до ближайшего целого числа. */

int s21_truncate(
    s21_decimal value,
    s21_decimal *result); /* Возвращает целые цифры указанного Decimal числа;
любые дробные цифры отбрасываются, включая конечные нули.*/

int s21_negate(s21_decimal value,
               s21_decimal *result);  // Возвращает результат умножения
                                      // указанного Decimal на -1.

int get_sign(int number);  // узнать знак числа
int get_exp(int number);   // узнать показатель степени

int overflow_add(decimal_overflow value_1, decimal_overflow value_2,
                 decimal_overflow *result);
void overflow_init(decimal_overflow *dst);
void dec_overflow_assignment(decimal_overflow *number1,
                             decimal_overflow number2);
void l_shift_overflow(decimal_overflow *value);
void r_shift(decimal_overflow *value);
decimal_overflow left_shift_overflow(s21_decimal number, int shift);
// decimal_overflow right_shift(s21_decimal number, int shift);

int l_shift(s21_decimal *value);
int left_shift(s21_decimal *number, int shift);
void print_binary_overflow(decimal_overflow number);
void print_int_overflow(decimal_overflow number);
void print_binary(int number);
int is_overflowed(decimal_overflow *number);
unsigned int set_mask(int shift);
void print_binary_dec(s21_decimal number);
void print_int_dec(s21_decimal number);
int comparison_scale(decimal_overflow *num_1, decimal_overflow *num_2,
                     unsigned int scale_1, unsigned int scale_2);
void normalization(decimal_overflow *result, short scale);
void decimal_assignment(s21_decimal *number1, s21_decimal number2);
int is_zero(s21_decimal number);
int simple_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void set_exp(unsigned *scale, unsigned target);
int is_divisible_by_10(s21_decimal n);
int simple_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_sub_bin(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int round_float(double num);
int get_sign_float(double num);
int get_exp_float(double num);
decimal_overflow overflow_mul(decimal_overflow value_1,
                              decimal_overflow value_2);
int overflow_is_greater(decimal_overflow number1, decimal_overflow number2);
decimal_overflow overflow_left_shift(decimal_overflow number, int shift);
int s21_sub_bin_overflow(decimal_overflow value_1, decimal_overflow value_2,
                         decimal_overflow *result);
int check_max(decimal_overflow val_1, int scale);
void reverse_normalization(decimal_overflow value, s21_decimal *result);
int is_overflow_zero(decimal_overflow number);
int div10_overflow(decimal_overflow *n);
void bank_round(decimal_overflow value, decimal_overflow *result);
void mod10(decimal_overflow value, decimal_overflow *mod);
int dividing(s21_decimal val1, s21_decimal val2, decimal_overflow *result);
int find_scale(decimal_overflow res, decimal_overflow celoe);
int find_down(decimal_overflow res, decimal_overflow celoe);
void upscale(decimal_overflow *v1, int diff1);
decimal_overflow bin_div(decimal_overflow v1, decimal_overflow v2);
int is_divisible_by_10_overflow(decimal_overflow n);
int overflow_is_equal(decimal_overflow number1, decimal_overflow number2);
int overflow_is_less_or_equal(decimal_overflow number1,
                              decimal_overflow number2);
void r_shift(decimal_overflow *value);
void comp_scale(decimal_overflow *num_1, decimal_overflow *num_2,
                unsigned int *scale_1, unsigned int *scale_2);
#endif