#include <stdio.h>
#include <math.h>


typedef struct AvgDamage {
  int min_damage_dice;
  int max_damage_dice;
  int ability_modifier;
  int base_damage;
  int crit_damage;
  int miss_damage;
} AvgDamage;

typedef struct Dice {
  int dice_num;
  int size;
  int dc;
} Dice;

typedef struct AttackAccuracy {
  float total_accuracy;
  float crit_chance;
  float normal_hit_chance;
  float miss_chance;
} AttackAccuracy;

int avg_dmg(int min, int max);
float acc_calc(float a, float b);


int main (int argc, char *argv[]) {
  int hit_modifier = 0;
  int ac = 10;

  Dice d20 = {1, 20, ac};
  Dice d12 = {1, 12, 0};
  Dice d10 = {1, 10, 0};
  Dice d8 = {1, 8, 0};
  Dice d6 = {1, 6, 0};
  Dice d4 = {1, 4, 0};

  AttackAccuracy accuracy = {
    ((float)d20.size - (float)d20.dc + 1.0) / (float)d20.size,
    ((float)d20.size - 20.0 + 1.0) / (float)d20.size,
    accuracy.total_accuracy - accuracy.crit_chance,
    1.0 - accuracy.total_accuracy
  };

  AvgDamage average_damage = {
    d6.dice_num,
    average_damage.min_damage_dice * d6.size,
    5,
    avg_dmg(average_damage.min_damage_dice + average_damage.ability_modifier,
            average_damage.max_damage_dice + average_damage.ability_modifier),
    average_damage.base_damage * 2,
    average_damage.ability_modifier
  };

  AttackAccuracy final_accuracy = {0};

  final_accuracy.total_accuracy = acc_calc(accuracy.total_accuracy, d20.dice_num);
  final_accuracy.crit_chance = acc_calc(accuracy.crit_chance, d20.dice_num);
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


int avg_dmg(int min, int max) {
  int result = (min + max) / 2;
  return result;
}

float acc_calc(float a, float b) {
  float result = 1.0 - pow(1.0 - a, b);
  return result;
}