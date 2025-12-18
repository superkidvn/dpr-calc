#ifndef DPR_CALC_H
#define DPR_CALC_H

#define ERR_USAGE \
  fprintf(stderr, "Usage: %s -d int -ac int -criton int\n", argv[0]);\
  exit(EXIT_FAILURE);

#define ERR_NUMARG \
  fprintf(stderr, "Invalid argument: Must pass a positive integer to this argument\n");\
  exit(EXIT_FAILURE);\


typedef struct AvgDamage {
  unsigned int base_damage;
  unsigned int crit_damage;
  unsigned int miss_damage;
} AvgDamage;

typedef struct Dice {
  unsigned int dice_num;
  unsigned int size;
  unsigned int dc;
} Dice;

typedef struct AttackAccuracy {
  float total_accuracy;
  float crit_chance;
  float normal_hit_chance;
  float miss_chance;
} AttackAccuracy;

/* avg_dmg is declared and defined, but not yet used */
int avg_dmg(int min, int max);
float multiroll_acc(float a, int e, bool dis);

#endif