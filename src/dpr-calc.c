#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dpr-calc.h"


unsigned int avg_dmg(unsigned int min, unsigned int max) {
  unsigned int result = (min + max) / 2;
  return result;
}


float multiroll_acc(float a, int num_roll, bool dis) {
  if (dis == true && num_roll != 2) {
    fputs(ERR_MULTIROLL, stderr);
    exit(EXIT_FAILURE);
  }

  float result;
  if (dis == true) {
    switch (num_roll) {
      case 1:
        result = 1.0 - (1.0 - a);
        break;
      case 2:
        result = 1.0 - (1.0 - a*a);
        break;
      case 3:
        result = 1.0 - (1.0 - a*a*a);
        break;
      default:
        fputs(ERR_MULTIROLL, stderr);
        exit(EXIT_FAILURE);
    }
  } else {
    switch (num_roll) {
      case 1:
        result = 1.0 - (1.0 - a);
        break;
      case 2:
        result = (1.0 - a)*(1.0 - a);
        result = 1.0 - result;
        break;
      case 3:
        result = (1.0 - a)*(1.0 - a)*(1.0 - a);
        result = 1.0 - result;
        break;
      default:
        fputs(ERR_MULTIROLL, stderr);
        exit(EXIT_FAILURE);
    }
  }

  return result;
}


void acc_lim(AttackAccuracy *accuracy) {
  if (accuracy->total_accuracy < accuracy->crit_chance) {
    accuracy->total_accuracy = accuracy->crit_chance;
  } else if (accuracy->total_accuracy > 0.95) {
    accuracy->total_accuracy = 0.95;
  }
}
