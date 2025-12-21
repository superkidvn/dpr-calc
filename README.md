# D&D 5E DAMAGE-PER-ROUND (DPR) CALCULATOR

This is an exercise, a practice program written in the C programming language. It takes in some command-line arguments and outputs to the terminal the DPR of a D&D 5E creature.

## Building:
You need the following prerequisites:
```
C compiler (gcc or clang)
make
```
Then you can run the following commands to build:
```
mkdir build
make
```
If you want to build for Windows using a cross compiler, set CC to the name of that compiler. For example:
`make CC=x86_64-w64-mingw32ucrt-gcc`
You can change the build destination with DESTDIR. Remember to create the build directory first. For example, I want to build into a directory called `output`:
```
mkdir output
make DESTDIR=output
```

## Usage:
```
dpr-calc -d <base damage> [OPTIONAL COMMANDS]

-d <damage>
    Average Base Damage; Must be 0 or higher.

OPTIONAL COMMANDS:
-ac <armor class>
    Armor Class, target number to hit; Must be higher than 0 (default 10).

-criton <1-20>
    Critical Hit on which number; Must be higher than 0 (default 20).

-b <number>
    Attack roll modifier; Number can be any integer (default 0).

-graze <damage>
    Missing deals damage; Must be 0 or higher (default 0).

-adv | -dis | -elf
    Advantage, Disadvantage, and Elven Accuracy respectively; Can only use one option.
```

## Missing features:
```
- Take a dice expression (e.g. 1d8 + 2d6 + 5) for the -d argument to dynamically calculate Average Base Damage based on user input.
- An option to set the Critical Hit rule, currently using double total damage rule.
```
