#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int status = 1;
  if (dst) {
    status = 0;
    int sign = get_sign(src.bits[SCALE]);

    s21_truncate(src, &src);

    if (src.bits[HIGH] == 0 && src.bits[MID] == 0 &&
        src.bits[LOW] <= 2147483648) {
      if (!sign && src.bits[LOW] == 2147483648) {
        status = 1;
      } else {
        status = 0;
      }
    } else {
      status = 1;
    }

    if (!status) {
      *dst = (int)(src.bits[LOW]);
      if (sign) *dst *= -1;
    } else {
      *dst = 0;
    }
  }
  return status;
}
