# D&D 5E DAMAGE-PER-ROUND (DPR) CALCULATOR

This is an exercise, a practice program written in the C programming language. It takes in some command-line arguments and outputs to the terminal the DPR of a D&D 5E creature.

## List of arguments:
```
-d int
    Average Base Damage; int must be 0 or higher.

-ac int (optional)
    Armor Class, target number to hit; int must be higher than 0 (default 10).

-criton int (optional)
    Critical Hit on which number; int must be higher than 0 (default 20).

-b int (optional)
    Attack roll modifier; int can be any integer (default 0).

-graze int (optional)
    Missing deals damage; int must be 0 or higher (default 0).

-adv (optional)
    Advantage, roll 2d20 and keep the highest result; exclusive with -dis and -elf.

-dis (optional)
    Disadvantage, roll 2d20 and keep the lowest result; exclusive with -adv and -elf.

-elf (optional)
    Elven Accuracy, roll 3d20 and keep the highest result; exclusive with -adv and -dis.
```

## Missing features:
```
- Haven't actually taken into account that there is always a 5% chance to miss (natural 1), so DPR result is inaccurate once the probablity of missing is low enough.
- Take a dice expression (e.g. 1d8 + 2d6 + 5) for the -d argument to dynamically calculate Average Base Damage based on user input.
- Still haven't actually checked for -adv/-dis/-elf exclusivity, so at the moment, the right-most argument will take precedent as it's processed last.
- An option to set the Critical Hit rule, currently using double total damage rule.
```