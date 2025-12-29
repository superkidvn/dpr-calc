#ifndef DPR_CALC_H
#define DPR_CALC_H

#define ERR_NUMARG "Invalid argument: Must pass a positive number to this argument\n"

#define ERR_ADV "Invalid argument: Can only have one: -adv | -dis | -elf\n"

#define ERR_HITMOD "Invalid Argument: Must pass a number to this argument\n"

#define ERR_CRITON "Invalid argument: Must be from 2 to 20.\n"

#define ERR_MULTIROLL "Error: Invalid exponent.\n"

#define ERR_CRITMODE "Error: Can't set Critical Hit rule.\n"

#define HELP_STR \
"Usage: dpr-calc -d <base damage> [OPTIONAL COMMANDS]\n\n"\
"-d <damage>\n"\
"    Average Base Damage; Must be 0 or higher.\n\n"\
\
"OPTIONAL COMMANDS:\n"\
"-ac <armor class>\n"\
"    Armor Class, target number to hit; Must be higher than 0 (default 10).\n\n"\
\
"-criton <1-20>\n"\
"    Critical Hit on which number; Must be higher than 0 (default 20).\n\n"\
\
"-b <number>\n"\
"    Attack roll modifier; Number can be any integer (default 0).\n\n"\
\
"-graze <damage>\n"\
"    Missing deals damage; Must be 0 or higher (default 0).\n\n"\
\
"-adv | -dis | -elf\n"\
"    Advantage, Disadvantage, and Elven Accuracy respectively; Can only use one option.\n"


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
unsigned int avg_dmg(unsigned int min, unsigned int max);
float multiroll_acc(float a, int num_roll, bool dis);
void acc_lim(AttackAccuracy *accuracy);

#endif
