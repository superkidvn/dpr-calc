#include <stdbool.h>
#include <math.h>
#include "dpr_calc.h"


int avg_dmg(int min, int max) {
  int result = (min + max) / 2;
  return result;
}


float multiroll_acc(float a, int e, bool dis) {
  float result;
  if (dis == true) {
    result = 1.0 - (1.0 - pow(a, (float)e));
    return result;
  }
  result = 1.0 - pow(1.0 - a, (float)e);
  return result;
}