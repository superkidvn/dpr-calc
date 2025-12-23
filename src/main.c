#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "dpr-calc.h"


int main (int argc, char *argv[]) {
  if (argc < 2) {
    fputs(HELP_STR, stderr);
    exit(EXIT_FAILURE);
  }

  int hit_modifier = 0;
  int criton = 20;
  int crit_mode = 1; // temporary default value, but real default is 0
  bool dis = false;
  Dice d20 = {1, 20, 10};
  AvgDamage average_damage = {0};
  AttackAccuracy final_accuracy = {0};
  AttackAccuracy accuracy = {0};


  for (int curr_argc = 1; curr_argc < argc; ++curr_argc) {

    if (strcmp(argv[curr_argc], "-h") == 0) {
      puts(HELP_STR);
      exit(EXIT_SUCCESS);
    }


    if (strcmp(argv[curr_argc], "-d") == 0) {
      if (curr_argc+1 == argc || atoi(argv[curr_argc+1]) <= 0) {
        fputs(ERR_NUMARG, stderr);
        exit(EXIT_FAILURE);
      }

      average_damage.base_damage = atoi(argv[curr_argc+1]);
      continue;
    }


    if (strcmp(argv[curr_argc], "-ac") == 0) {
      if (curr_argc+1 == argc || atoi(argv[curr_argc+1]) <= 0) {
        fputs(ERR_NUMARG, stderr);
        exit(EXIT_FAILURE);
      }

      d20.dc = atoi(argv[curr_argc+1]);
      continue;
    }


    if (strcmp(argv[curr_argc], "-criton") == 0) {
      if (curr_argc+1 == argc || atoi(argv[curr_argc+1]) <= 0) {
        fputs(ERR_NUMARG, stderr);
        exit(EXIT_FAILURE);
      }

      criton = atoi(argv[curr_argc+1]);
      continue;
    }


    if (strcmp(argv[curr_argc], "-b") == 0) {
      if (curr_argc+1 == argc) {
        fputs(ERR_HITMOD, stderr);
        exit(EXIT_FAILURE);
      }
      if (atoi(argv[curr_argc+1]) == 0) {
        if (strcmp(argv[curr_argc+1], "0") == 0) {
          hit_modifier = 0;
          continue;
        }
        fputs(ERR_HITMOD, stderr);
        exit(EXIT_FAILURE);
      }

      hit_modifier = atoi(argv[curr_argc+1]);
      continue;
    }


    if (strcmp(argv[curr_argc], "-graze") == 0) {
      if (curr_argc+1 == argc) {
        fputs(ERR_NUMARG, stderr);
        exit(EXIT_FAILURE);
      }
      if (atoi(argv[curr_argc+1]) <= 0) {
        if (strcmp(argv[curr_argc+1], "0") == 0) {
          average_damage.miss_damage = 0;
          continue;
        }
        fputs(ERR_NUMARG, stderr);
        exit(EXIT_FAILURE);
      }

      average_damage.miss_damage = atoi(argv[curr_argc+1]);
      continue;
    }


    if (strcmp(argv[curr_argc], "-elf") == 0) {
      if (d20.dice_num != 1) {
        fputs(ERR_ADV, stderr);
        exit(EXIT_FAILURE);
      }

      d20.dice_num = 3;
      dis = false;
      continue;
    }


    if (strcmp(argv[curr_argc], "-adv") == 0 || strcmp(argv[curr_argc], "-dis") == 0) {
      if (d20.dice_num != 1) {
        fputs(ERR_ADV, stderr);
        exit(EXIT_FAILURE);
      }

      d20.dice_num = 2;
      if (strcmp(argv[curr_argc], "-dis") == 0) {
        dis = true;
      } else {
        dis = false;
      }
      continue;
    }

  }

  // Check for mandatory <-d>
  if (average_damage.base_damage <= 0) {
    fputs(HELP_STR, stderr);
    exit(EXIT_FAILURE);
  }


  /*
Critical Hit Rule: currently only support crit_mode = 1.
  Double number of damage dice (vanille 5E):
      crit_mode = 0 (planned default)
  Double total damage:
      crit_mode = 1 (current)
  Highest damage dice value:
      crit_mode = 2
  Double number of damage dice and flat modifiers (3E):
      crit_mode = 3
  */
  switch (crit_mode) {
    case 0:
      puts("Rule: Vanilla 5E Critical Hit.");
      break;
    case 1:
      average_damage.crit_damage = average_damage.base_damage * 2;
      break;
    case 2:
      puts("Rule: Highest damage dice value.");
      break;
    case 3:
      puts("Rule: 3E Critical Hit.");
      break;
    default:
      fputs(ERR_CRITMODE, stderr);
  }


  // The number to roll on the d20 after accounting for attack roll modifier.
  int to_hit = d20.dc - hit_modifier;

  accuracy.total_accuracy = ((float)d20.size - (float)to_hit + 1.0) / (float)d20.size;
  accuracy.crit_chance = ((float)d20.size - (float)criton + 1.0) / (float)d20.size;
  acc_lim(&accuracy);

  final_accuracy.total_accuracy = multiroll_acc(accuracy.total_accuracy, d20.dice_num, dis);
  final_accuracy.crit_chance = multiroll_acc(accuracy.crit_chance, d20.dice_num, dis);
  final_accuracy.miss_chance = 1.0 - final_accuracy.total_accuracy;
  final_accuracy.normal_hit_chance = final_accuracy.total_accuracy - final_accuracy.crit_chance;

  float normal_hit_dpr = average_damage.base_damage * final_accuracy.normal_hit_chance;
  float crit_dpr = average_damage.crit_damage * final_accuracy.crit_chance;
  float miss_dpr = average_damage.miss_damage * final_accuracy.miss_chance;
  float total_dpr = normal_hit_dpr + crit_dpr + miss_dpr;

  printf("Normal Hit DPR: %f\n", normal_hit_dpr);
  printf("Critical Hit DPR: %f\n", crit_dpr);
  printf("Miss DPR: %f\n", miss_dpr);
  printf("Total DPR: %f\n", total_dpr);

  exit(EXIT_SUCCESS);
}
