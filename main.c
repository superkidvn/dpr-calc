#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "dpr_calc.h"


int main (int argc, char *argv[]) {
  if (argc < 2 || argc > 12) {
    ERR_USAGE;
  }

  int hit_modifier = 0;
  int criton = 20;
  bool dis = false;
  Dice d20 = {1, 20, 10};
  AvgDamage average_damage = {0};
  AttackAccuracy final_accuracy = {0};
  AttackAccuracy accuracy = {0};


  /* List of arguments:
        -d int => Average Base Damage
        -ac int (optional) => Armor Class, target number to hit, default 10
        -criton int (optional) => Critical Hit on which number, default 20
        -b int (optional) => Attack roll modifier, default 0
        -graze int (optional) => Missing deals damage equal to int
        -adv (optional) => Advantage (2d20kh1)
        -dis (optional) => Disadvantage (2d20kl1)
        -elf (optional) => Elven Accuracy (3d20kh1)
  */
  for (int curr_argc = 1; curr_argc < argc; ++curr_argc) {

    if (strcmp(argv[curr_argc], "-d") == 0) {
      if (curr_argc+1 == argc) {
        ERR_NUMARG;
      } else if (atoi(argv[curr_argc+1]) == 0) {
        if (strcmp(argv[curr_argc+1], "0") == 0) {
          average_damage.base_damage = 0;
          continue;
        } else {
          ERR_NUMARG;
        }
      }
      if (atoi(argv[curr_argc+1]) < 0) {
        ERR_NUMARG;
      } else {
        average_damage.base_damage = atoi(argv[curr_argc+1]);
      }
      continue;
    } 


    if (strcmp(argv[curr_argc], "-ac") == 0) {
      if (curr_argc+1 == argc || atoi(argv[curr_argc+1]) <= 0) {
        ERR_NUMARG;
      }
      d20.dc = atoi(argv[curr_argc+1]);
      continue;
    }


    if (strcmp(argv[curr_argc], "-criton") == 0) {
      if (curr_argc+1 == argc || atoi(argv[curr_argc+1]) <= 0) {
        ERR_NUMARG;
      }
      criton = atoi(argv[curr_argc+1]);
      continue;
    }


    if (strcmp(argv[curr_argc], "-b") == 0) {
      if (curr_argc+1 == argc) {
        fprintf(stderr, "Invalid Argument: Must pass an integer to this argument\n");
        exit(EXIT_FAILURE);
      } else if (atoi(argv[curr_argc+1]) == 0) {
        if (strcmp(argv[curr_argc+1], "0") == 0) {
          hit_modifier = 0;
          continue;
        } else {
          fprintf(stderr, "Invalid Argument: Must pass an integer to this argument\n");
          exit(EXIT_FAILURE);
        }
      }
      hit_modifier = atoi(argv[curr_argc+1]);
      continue;
    }


    if (strcmp(argv[curr_argc], "-graze") == 0) {
      if (curr_argc+1 == argc) {
        ERR_NUMARG;
      } else if (atoi(argv[curr_argc+1]) == 0) {
        if (strcmp(argv[curr_argc+1], "0") == 0) {
          average_damage.miss_damage = 0;
          continue;
        } else {
          ERR_NUMARG;
        }
      }
      if (atoi(argv[curr_argc+1]) < 0) {
        ERR_NUMARG;
      } else {
        average_damage.miss_damage = atoi(argv[curr_argc+1]);
      }
      continue;
    }


    if (strcmp(argv[curr_argc], "-elf") == 0) {
      d20.dice_num = 3;
      continue;
    }


    if (strcmp(argv[curr_argc], "-adv") == 0 || strcmp(argv[curr_argc], "-dis") == 0) {
      d20.dice_num = 2;
      if (strcmp(argv[curr_argc], "-dis") == 0) dis = true;
      continue;
    }


  }

  average_damage.crit_damage = average_damage.base_damage * 2;

  accuracy.total_accuracy = ((float)d20.size - (float)d20.dc + 1.0) / (float)d20.size;
  accuracy.crit_chance = ((float)d20.size - (float)criton + 1.0) / (float)d20.size;
  if (accuracy.total_accuracy < accuracy.crit_chance) accuracy.total_accuracy = accuracy.crit_chance;
  accuracy.normal_hit_chance = accuracy.total_accuracy - accuracy.crit_chance;
  accuracy.miss_chance = 1.0 - accuracy.total_accuracy;

  final_accuracy.total_accuracy = multiroll_acc(accuracy.total_accuracy, d20.dice_num, dis);
  final_accuracy.crit_chance = multiroll_acc(accuracy.crit_chance, d20.dice_num, dis);
  if (final_accuracy.total_accuracy < final_accuracy.crit_chance) final_accuracy.total_accuracy = final_accuracy.crit_chance;
  final_accuracy.normal_hit_chance = final_accuracy.total_accuracy - final_accuracy.crit_chance;
  final_accuracy.miss_chance = 1.0 - final_accuracy.total_accuracy;

  float normal_hit_dpr = average_damage.base_damage * final_accuracy.normal_hit_chance;
  float crit_dpr = average_damage.crit_damage * final_accuracy.crit_chance;
  float miss_dpr = average_damage.miss_damage * final_accuracy.miss_chance;
  float total_dpr = normal_hit_dpr + crit_dpr + miss_dpr;

  printf("Normal Hit DPR: %f\n", normal_hit_dpr);
  printf("Critical Hit DPR: %f\n", crit_dpr);
  printf("Miss DPR: %f\n", miss_dpr);
  printf("Total DPR: %f\n", total_dpr);

  return 0;
}