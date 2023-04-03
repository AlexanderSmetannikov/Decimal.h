#include "../s21_decimal.h"

int is_bit_set(int number, int index) {
  return (number & (1 << index)) ? 1 : 0;
}

int set_bit(int number, int index) { return (number | (1 << index)); }

int reverse_bit(int number, int index) { return (number ^ (1 << index)); }

int reset_bit(int number, int index) { return (number & ~(1 << index)); }

void decimal_init(s21_decimal *dst) {
  dst->bits[LOW] = 0;
  dst->bits[MID] = 0;
  dst->bits[HIGH] = 0;
  dst->bits[SCALE] = 0;
}

void overflow_init(decimal_overflow *dst) {
  dst->bits[LOW] = 0;
  dst->bits[MID] = 0;
  dst->bits[HIGH] = 0;
  dst->bits[3] = 0;
  dst->bits[4] = 0;
  dst->bits[5] = 0;
}

void dec_overflow_assignment(decimal_overflow *number1,
                             decimal_overflow number2) {
  number1->bits[0] = number2.bits[0];
  number1->bits[1] = number2.bits[1];
  number1->bits[2] = number2.bits[2];
  number1->bits[3] = number2.bits[3];
  number1->bits[4] = number2.bits[4];
  number1->bits[5] = number2.bits[5];
}

int s21_abs(int number) { return (number < 0) ? number * (-1) : number; }

int get_sign(int number) { return (is_bit_set(number, 31)) ? 1 : 0; }

int get_exp(int number) {
  int res = number & EXP_INT_MASK;
  res = res >> 16;
  return res;
}

// int float_to_binary(float f) {
//   union float_binary fb;
//   fb.f = f;
//   return fb.i;
// }

int l_shift(s21_decimal *value) {
  short b[3] = {0};
  int result = 0;
  for (int i = 0; i < 3; i++) b[i] = is_bit_set(value->bits[i], 31);
  if (b[2] == 0) {
    for (int i = 0; i < 3; i++) value->bits[i] <<= 1;
    for (int i = 0; i < 2; i++)
      if (b[i]) value->bits[i + 1] = set_bit(value->bits[i + 1], 0);
  } else
    result = 1;
  return result;
}

int left_shift(s21_decimal *number, int shift) {
  int result = 0;
  for (int i = 0; i < shift && !result; i++) result = l_shift(number);
  return result;
}

int is_overflowed(decimal_overflow *number) {
  return (number->bits[3] || number->bits[4] || number->bits[5]);
}

int is_zero(s21_decimal number) {
  int isZero = 1;
  for (int i = 0; i < 3; i++) {
    if (number.bits[i] != 0) {
      isZero = 0;
    }
  }
  return isZero;
}

void decimal_assignment(s21_decimal *number1, s21_decimal number2) {
  number1->bits[0] = number2.bits[0];
  number1->bits[1] = number2.bits[1];
  number1->bits[2] = number2.bits[2];
  number1->bits[3] = number2.bits[3];
}

int simple_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  short error = 0, mind = 0;
  int term1, term2;
  decimal_init(result);
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 32; i++) {
      term1 = is_bit_set(value_1.bits[j], i);
      term2 = is_bit_set(value_2.bits[j], i);
      if (term1 && term2) {
        if (mind) {
          result->bits[j] = set_bit(result->bits[j], i);
        } else {
          mind = 1;
        }
      } else if (term1 ^ term2) {
        if (!mind) {
          result->bits[j] = set_bit(result->bits[j], i);
        }
      } else if (mind) {
        result->bits[j] = set_bit(result->bits[j], i);
        mind = 0;
      }
    }
    if (mind && j == 2) error = 1;
  }
  return error;
}

int simple_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  s21_decimal tmp = {0};
  s21_decimal res = {0};
  s21_decimal val1_cp = {0};
  if (result) {
    for (int i = 0; i < 96 && !status; i++) {
      if (is_bit_set(value_2.bits[i / 32], i % 32)) {
        decimal_init(&tmp);
        decimal_assignment(&val1_cp, value_1);
        decimal_assignment(&tmp, res);
        status = left_shift(&val1_cp, i) + simple_add(tmp, val1_cp, &res);
      }
    }
    if (status == 0)
      decimal_assignment(result,
                         res);  // приравниваем только когда нигде не было
                                // ошибок, сам цикл работает до тех пор
    // пока каждая из простых арифметических функций не возвращает ошибку
    // переполнения
  }
  return status;
}

int div10(s21_decimal *n) {
  unsigned int mod = 0;
  long long int tmp;
  for (int i = 2; i >= 0; --i) {
    tmp = (unsigned)n->bits[i] + ((long long)(mod) << 32);
    mod = tmp % 10;
    n->bits[i] = tmp / 10;
  }
  return mod;
}

void s21_sub_bin(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  for (int i = 0; i < 96; i++)
    value_2.bits[i / 32] = reverse_bit(value_2.bits[i / 32], i);
  value_2.bits[LOW]++;
  simple_add(value_1, value_2, result);
}

void set_exp(unsigned *scale, unsigned target) {
  unsigned sign = get_sign(*scale);
  *scale = target;
  *scale <<= 16;
  if (sign) *scale = set_bit(*scale, 31);
}

int is_divisible_by_10(s21_decimal n) {
  s21_decimal tmp = {0};
  for (int i = 0; i < 3; ++i)
    tmp.bits[i] = n.bits[i];  // копируем и проверяем остаток от деления на 10
  return !div10(&tmp);
}

int get_exp_float(double num) {
  union Data data;
  data.f = num;
  int exp = (data.i & MASK_FLOAT_EXP) >> 23;
  exp = exp - 127;

  return exp;
}

int get_sign_float(double num) {
  union Data data;
  data.f = num;
  int sign = is_bit_set(data.i, 31);
  return sign;
}

int round_float(double num) {
  int res;
  double dec1, rem1;
  rem1 = modf(num, &dec1);

  if (rem1 > 0.5) dec1 += 1;
  res = (int)dec1;

  return res;
}

int comparison_scale(decimal_overflow *num_1, decimal_overflow *num_2,
                     unsigned int scale_1, unsigned int scale_2) {
  int flag = 0;
  if (get_exp(scale_1) > get_exp(scale_2)) {
    normalization(num_2, get_exp(scale_1) - get_exp(scale_2));
    flag = scale_2 = scale_1;
  } else if (get_exp(scale_1) < get_exp(scale_2)) {
    normalization(num_1, get_exp(scale_2) - get_exp(scale_1));
    flag = scale_1 = scale_2;
  } else {
    flag = scale_1;
  }
  return flag;
}

void normalization(decimal_overflow *result, short scale) {
  decimal_overflow ten = {{10, 0, 0, 0, 0, 0}};
  for (int i = 0; i < scale; i++) {
    *result = overflow_mul(*result, ten);
  }
}

decimal_overflow overflow_mul(decimal_overflow value_1,
                              decimal_overflow value_2) {
  decimal_overflow tmp = {{0, 0, 0, 0, 0, 0}};
  decimal_overflow res = {{0, 0, 0, 0, 0, 0}};
  for (int i = 0; i < 192; i++) {
    if (is_bit_set(value_1.bits[i / 32], i % 32)) {
      overflow_init(&tmp);
      dec_overflow_assignment(&tmp, res);
      overflow_add(tmp, overflow_left_shift(value_2, i), &res);
    }
  }
  return res;
}

int overflow_is_greater(decimal_overflow number1, decimal_overflow number2) {
  int result = 0, flag = 0;
  for (int j = 5; j >= 0 && !result; j--) {
    unsigned int value1 = number1.bits[j];
    unsigned int value2 = number2.bits[j];
    if (!flag) {
      if (value1 > value2)
        result = 1;
      else if (value1 < value2)
        flag++;
    }
  }
  return result;
}

decimal_overflow overflow_left_shift(decimal_overflow number, int shift) {
  for (int i = 0; i < shift; i++) l_shift_overflow(&number);
  return number;
}

int s21_sub_bin_overflow(decimal_overflow value_1, decimal_overflow value_2,
                         decimal_overflow *result) {
  int err;
  if (!is_overflow_zero(value_2)) {
    for (int i = 0; i < 192; i++)
      value_2.bits[i / 32] = reverse_bit(value_2.bits[i / 32], i);
    value_2.bits[LOW]++;
  }
  err = overflow_add(value_1, value_2, result);
  return err;
}

int check_max(decimal_overflow val_1, int scale) {
  decimal_overflow max = {{MAX_DEC, MAX_DEC, MAX_DEC, 0, 0, 0}};
  int err = 0;
  for (int i = 0; i < get_exp(scale); i++) {
    div10_overflow(&val_1);
  }
  if (overflow_is_greater(val_1, max)) {
    err = get_sign(scale) ? 2 : 1;
  }
  return err;
}

void reverse_normalization(decimal_overflow value, s21_decimal *result) {
  while (value.bits[3] || value.bits[4] || value.bits[5] ||
         (get_exp(result->bits[3]) > 28)) {
    bank_round(value, &value);
    result->bits[3] -= 1 << 16;
  }
  result->bits[0] = value.bits[0];
  result->bits[1] = value.bits[1];
  result->bits[2] = value.bits[2];
}

void l_shift_overflow(decimal_overflow *value) {
  short b[5];
  for (int i = 0; i < 5; i++) b[i] = is_bit_set(value->bits[i], 31);
  for (int i = 0; i < 6; i++) value->bits[i] <<= 1;
  for (int i = 0; i < 5; i++)
    if (b[i]) value->bits[i + 1] = set_bit(value->bits[i + 1], 0);
}

int is_overflow_zero(decimal_overflow number) {
  int isZero = 1;
  for (int i = 0; i < 6; i++) {
    if (number.bits[i] != 0) {
      isZero = 0;
    }
  }
  return isZero;
}

int div10_overflow(decimal_overflow *n) {
  unsigned int mod = 0;
  long long int tmp;
  for (int i = 5; i >= 0; --i) {
    tmp = (unsigned)n->bits[i] + ((long long)(mod) << 32);
    mod = tmp % 10;
    n->bits[i] = tmp / 10;
  }
  return mod;
}

void bank_round(decimal_overflow value, decimal_overflow *result) {
  if (result) {
    overflow_init(result);
    decimal_overflow mod1, mod2;
    overflow_init(&mod1);
    overflow_init(&mod2);
    decimal_overflow one = {{1, 0, 0, 0, 0, 0}};
    mod10(value, &mod1);
    div10_overflow(&value);
    if (mod1.bits[LOW] > 5) {
      overflow_add(value, one, &value);
    } else if (mod1.bits[LOW] == 5) {
      mod10(value, &mod2);
      if (mod2.bits[LOW] % 2 != 0) overflow_add(value, one, &value);
    }
  }
  *result = value;
}

void mod10(decimal_overflow value, decimal_overflow *mod) {
  decimal_overflow ten = {{10, 0, 0, 0, 0, 0}};
  decimal_overflow tmp = value;
  if (mod) {
    div10_overflow(&tmp);
    tmp = overflow_mul(tmp, ten);
    s21_sub_bin_overflow(value, tmp, mod);
  }
}

decimal_overflow left_shift_overflow(s21_decimal number, int shift) {
  decimal_overflow res = {
      {number.bits[LOW], number.bits[MID], number.bits[HIGH], 0, 0, 0}};
  for (int i = 0; i < shift; i++) l_shift_overflow(&res);
  return res;
}

int overflow_add(decimal_overflow value_1, decimal_overflow value_2,
                 decimal_overflow *result) {
  short error = 0, mind = 0;
  int term1, term2;
  overflow_init(result);
  for (int j = 0; j < 6; j++) {
    for (int i = 0; i < 32; i++) {
      term1 = is_bit_set(value_1.bits[j], i);
      term2 = is_bit_set(value_2.bits[j], i);
      if (term1 && term2) {
        if (mind) {
          result->bits[j] = set_bit(result->bits[j], i);
        } else {
          mind = 1;
        }
      } else if (term1 ^ term2) {
        if (!mind) {
          result->bits[j] = set_bit(result->bits[j], i);
        }
      } else if (mind) {
        result->bits[j] = set_bit(result->bits[j], i);
        mind = 0;
      }
    }
    if (mind && j == 5) error = 1;
  }
  return error;
}

int dividing(s21_decimal val1, s21_decimal val2, decimal_overflow *result) {
  decimal_overflow val_1 = {{val1.bits[LOW], val1.bits[MID], val1.bits[HIGH], 0,
                             0, 0}},
                   val_2 = {{val2.bits[LOW], val2.bits[MID], val2.bits[HIGH], 0,
                             0, 0}},
                   celoe = {0}, v1cpy = val_1, v2cpy = val_2;
  s21_decimal one = {{1, 0, 0, 0}};
  decimal_overflow big_one = {{1, 0, 0, 0, 0, 0}};
  int ans = get_exp(val1.bits[SCALE]);

  if (!s21_is_equal(val2, one)) {
    int scale1 = get_exp(val1.bits[SCALE]);
    int scale2 = get_exp(val2.bits[SCALE]);
    int up = (scale1 != scale2) ? 28 + s21_abs(scale1 - scale2) - 1 : 29;
    comp_scale(&v1cpy, &v2cpy, &val1.bits[SCALE], &val2.bits[SCALE]);

    celoe = bin_div(v1cpy, v2cpy);
    if (scale1 != scale2) {
      if (s21_is_less(val1, val2) && !s21_is_equal(val2, one)) {
        upscale(&val_1, up);
      } else if (!s21_is_equal(val2, one))
        upscale(&val_1, 29);
    } else if (!s21_is_equal(val2, one))
      upscale(&val_1, 28);
    *result = bin_div(val_1, val_2);
    int scale = find_down(*result, celoe);
    int down = scale <= 28 ? scale : 28;
    while ((is_overflowed(result) && down > 0) ||
           (is_divisible_by_10_overflow(*result) && down > 0)) {
      bank_round(*result, result);
      down--;
    }
    ans = find_scale(*result, celoe);
  } else {
    *result = bin_div(val_1, big_one);
  }
  return ans;
}

int find_scale(decimal_overflow res, decimal_overflow celoe) {
  int scale = 0;
  int down = 28;
  while (!overflow_is_equal(res, celoe) && down > 0) {
    div10_overflow(&res);
    scale++;
    down--;
  }
  return scale;
}

int find_down(decimal_overflow res, decimal_overflow celoe) {
  int scale = 0;
  int down = 28;
  while (!overflow_is_equal(res, celoe) && down >= 0) {
    div10_overflow(&res);
    scale++;
    down--;
  }
  return scale;
}

void upscale(decimal_overflow *v1, int diff1) {
  decimal_overflow ten = {{10, 0, 0, 0, 0, 0}};

  while (diff1) {
    *v1 = overflow_mul(*v1, ten);
    diff1--;
  }
}

decimal_overflow bin_div(decimal_overflow v1, decimal_overflow v2) {
  decimal_overflow l = {0}, r = v1, mid = {0};

  decimal_overflow tmp = {0};
  decimal_overflow one = {{1, 0, 0, 0, 0, 0}};
  decimal_overflow res = {0};
  while (overflow_is_less_or_equal(l, r)) {
    s21_sub_bin_overflow(r, l, &tmp);

    r_shift(&tmp);
    overflow_add(l, tmp, &mid);
    tmp = overflow_mul(v2, mid);
    if (overflow_is_greater(tmp, v1)) {
      s21_sub_bin_overflow(mid, one, &r);
    } else {
      dec_overflow_assignment(&res, mid);
      overflow_add(mid, one, &l);
    }
  }
  return res;
}

int is_divisible_by_10_overflow(decimal_overflow n) {
  decimal_overflow tmp = {0};
  for (int i = 0; i < 6; ++i)
    tmp.bits[i] = n.bits[i];  // копируем и проверяем остаток от деления на 10
  return !div10_overflow(&tmp);
}

int overflow_is_equal(decimal_overflow number1, decimal_overflow number2) {
  int result = 1;
  for (int i = 5; i >= 0; i--) {
    unsigned int value1 = number1.bits[i];
    unsigned int value2 = number2.bits[i];
    if (value1 != value2) {
      result = 0;
    }
  }
  return result;
}

int overflow_is_less_or_equal(decimal_overflow number1,
                              decimal_overflow number2) {
  return !overflow_is_greater(number1, number2);
}

void r_shift(decimal_overflow *value) {  // деление на 2
  short b[5];
  for (int i = 1; i < 5; i++) b[i] = is_bit_set(value->bits[i], 0);
  for (int i = 0; i < 6; i++) value->bits[i] >>= 1;
  for (int i = 4; i > 0; i--)
    if (b[i]) value->bits[i - 1] = set_bit(value->bits[i - 1], 31);
}

void comp_scale(decimal_overflow *num_1, decimal_overflow *num_2,
                unsigned int *scale_1, unsigned int *scale_2) {
  if (get_exp(*scale_1) > get_exp(*scale_2)) {
    normalization(num_2, get_exp(*scale_1) - get_exp(*scale_2));
    *scale_2 = *scale_1;
  } else if (get_exp(*scale_1) < get_exp(*scale_2)) {
    normalization(num_1, get_exp(*scale_2) - get_exp(*scale_1));
    *scale_1 = *scale_2;
  }
}
