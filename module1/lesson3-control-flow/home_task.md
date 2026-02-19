# Lesson 3: Homework -- Multiplication Table 16x16

## Objective

Create a program that prints a 16x16 multiplication table to Serial Monitor.
A push button cycles the display between three number systems:
Octal (OCT), Decimal (DEC), and Hexadecimal (HEX).

## Requirements

1. **Multiplication table**: Print a 16x16 grid (1..16 x 1..16) with a
   header row and header column showing the operands.
2. **Button cycles display mode**: Each press switches the mode:
   OCT -> DEC -> HEX -> OCT -> ...
3. **Reprint on press**: Every time the button is pressed, clear the
   screen (print several blank lines) and reprint the entire table
   in the new mode.
4. **Formatted columns**: Use `Serial.printf()` with width specifiers
   so columns are properly aligned in all three modes.
5. **Use functions**: Extract the table printing logic into a separate
   function.
6. **Use switch/case**: Select the format string based on the current mode.
7. **Debounce the button**: Filter contact bounce so one press = one switch.
8. **Use stdint.h types**: All variables must use explicit fixed-width
   types (uint8_t, int32_t, etc.) instead of int, char, etc.

## Expected Serial Output (DEC mode example)

```
Mode: DEC
       1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16
  1    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16
  2    2    4    6    8   10   12   14   16   18   20   22   24   26   28   30   32
  3    3    6    9   12   15   18   21   24   27   30   33   36   39   42   45   48
  ...
 16   16   32   48   64   80   96  112  128  144  160  176  192  208  224  240  256
```

## Hints

### printf width specifiers

```c
Serial.printf("%4d",  value);   // decimal, width 4, right-aligned
Serial.printf("%6o",  value);   // octal,   width 6
Serial.printf("%4X",  value);   // hex uppercase, width 4
Serial.printf("%04X", value);   // hex with leading zeros
```

### Mode cycling with modulo

```c
mode = (mode + 1) % 3;   // cycles 0 -> 1 -> 2 -> 0 -> ...
```

### Max value in the table

16 x 16 = 256, which fits in `uint16_t`. Choose your types accordingly.

## Grading

| Criteria                              | Points |
|---------------------------------------|--------|
| Table prints correctly in DEC mode    | 2      |
| Table prints correctly in OCT mode    | 2      |
| Table prints correctly in HEX mode    | 2      |
| Columns are properly aligned          | 1      |
| Button switches mode with debounce    | 1      |
| Print logic extracted into a function | 1      |
| stdint.h types used throughout        | 1      |
| **Total**                             | **10** |

## Submission

Push your code to your repository. The solution should be in
`src/main.cpp` (replace the practice code or create a new branch).
