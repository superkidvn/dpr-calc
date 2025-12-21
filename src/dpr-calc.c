#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "dpr-calc.h"


unsigned int avg_dmg(unsigned int min, unsigned int max) {
  unsigned int result = (min + max) / 2;
  return result;
}


float multiroll_acc(float a, int e, bool dis) {
  if (dis == true && e != 2) {
    fprintf(stderr, ERR_MULTIROLL);
    exit(EXIT_FAILURE);
  }

  float result;
  if (dis == true) {
    result = 1.0 - (1.0 - pow(a, (float)e));
    return result;
  }
  result = 1.0 - pow(1.0 - a, (float)e);
  return result;
}


void acc_lim(AttackAccuracy *accuracy) {
  if (accuracy->total_accuracy < accuracy->crit_chance) {
    accuracy->total_accuracy = accuracy->crit_chance;
  } else if (accuracy->total_accuracy > 0.95) {
    accuracy->total_accuracy = 0.95;
  }
}
