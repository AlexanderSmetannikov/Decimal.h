#include <stdio.h>

typedef struct {
    int bits[4];
} s21_decimal;

// enum status {
//     OK,
//     INF,
//     NEGATIVE_INF,
//     NAN
// };

// ARIPHMETIC

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); // сложение
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); // вычитание
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); // умножение
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); // деление
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); // остаток от деления


// COMPARISON

int s21_is_less(s21_decimal, s21_decimal); // оператор меньше
int s21_is_less_or_equal(s21_decimal, s21_decimal); // оператор меньше или равно
int s21_is_greater(s21_decimal, s21_decimal); // оператор больше
int s21_is_greater_or_equal(s21_decimal, s21_decimal); // оператор больше или равно
int s21_is_equal(s21_decimal, s21_decimal); // оператор равно
int s21_is_not_equal(s21_decimal, s21_decimal); // не равно


// FROM-TO CONVERSION

int s21_from_int_to_decimal(int src, s21_decimal *dst); // from Int to Decimal
int s21_from_float_to_decimal(float src, s21_decimal *dst); // from Float to Decimal
int s21_from_decimal_to_int(s21_decimal src, int *dst); // from Decimal to Int
int s21_from_decimal_to_float(s21_decimal src, float *dst); // from Decimal to Float

// OTHER

int s21_floor(s21_decimal value, s21_decimal *result); /* Округляет указанное Decimal число
                                 до ближайшего целого числа в сторону отрицательной бесконечности. */

int s21_round(s21_decimal value, s21_decimal *result); /* Округляет Decimal до ближайшего целого числа. */

int s21_truncate(s21_decimal value, s21_decimal *result); /* Возвращает целые цифры указанного Decimal числа; 
                                любые дробные цифры отбрасываются, включая конечные нули.*/

int s21_negate(s21_decimal value, s21_decimal *result); // Возвращает результат умножения указанного Decimal на -1.