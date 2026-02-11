# Homework Assignment: Christmas Tree Pattern

## Deadline
Submit before next class session (16.02).

## Task Description
Write a program that prints a Christmas tree pattern made of asterisks (*).  
The tree should have N levels (height N) and be centered.

## Examples

**Input:** N = 2  
**Output:**
```
 *
***
```

**Input:** N = 3  
**Output:**
```
  *
 ***
*****
```

**Input:** N = 5  
**Output:**
```
    *
   ***
  *****
 *******
*********
```

## Requirements

1. Complete the `printTree(int n)` function in `homework_tree.c`
2. Your tree must be:
   - Centered (correct number of spaces before asterisks)
   - Symmetrical
   - Have exactly N levels
   - Each level should have 2 more asterisks than the previous level

3. The provided tests should produce correct output

## How to Work on This

### Step 1: Understand the Pattern
Look at the examples and figure out:
- How many spaces before asterisks on each level?
- How many asterisks on each level?
- What's the mathematical relationship?

### Step 2: Plan Your Approach
You'll need:
- An outer loop (for each level)
- Inner loops (for spaces and asterisks)
- The right formulas

### Step 3: Write Code
Start simple:
1. First, try to print just the asterisks (ignore centering)
2. Then add the spaces to center it
3. Test with small values (N=1, N=2, N=3)

### Step 4: Test
Compile and run:
```bash
gcc homework_tree.c -o tree
./tree
```

Check that your output matches the expected patterns!

## Submission

1. Complete the code in `homework_tree.c`
2. Test it thoroughly
3. Commit and push to your course repository:
   ```bash
   git add homework_tree.c
   git commit -m "Homework: Christmas tree pattern completed"
   git push
   ```
4. Make sure the file is in the `module1/` folder of your repository

## Grading Criteria

- Tree is properly centered (30%)
- Correct number of levels (20%)
- Correct number of asterisks per level (30%)
- Clean code with good loop structure (20%)

## Bonus Challenges (Optional)

If you finish early and want extra practice:

1. **Add a trunk**: Print 1-2 rows of `|` at the bottom, centered
2. **Decorations**: Use different characters (O, @, *) randomly
3. **Multiple trees**: Print 3 trees side by side
4. **Inverted tree**: Make an upside-down tree
5. **User input**: Ask user for height instead of using tests

## Need Help?

- Review the lecture slides on loops
- Look at the examples in Task 1 (find max) for loop patterns
- Ask questions in class or via email
- Remember: the goal is to learn, not just to finish!
- Don't use AI, use your brain. 
- If need - ask AI speficiv qestion, like "What param and settings have a 'printf' function?" 
- Or - 'How to enter number to my C programm?'

## Academic Integrity

- Write your own code
- You may discuss the approach with classmates
- Do NOT copy code from others or the internet
- Understanding the solution is more important than having it work immediately

Good luck! 🎄
