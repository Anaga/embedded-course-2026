/*
 * Homework: Christmas Tree Pattern
 * 
 * Description:
 * Write a program that prints a Christmas tree made of asterisks (*).
 * The tree should have N levels (height N).
 * 
 * Pattern explanation:
 * - Each level has a certain number of spaces and asterisks
 * - Level 1 (top): maximum spaces, 1 asterisk
 * - Each next level: one less space, two more asterisks
 * - The tree should be centered
 * 
 * Skills practiced:
 * - Nested loops
 * - Mathematical thinking (calculating spaces and asterisks)
 * - Formatted output
 * 
 * Example patterns:
 * 
 * N = 1:
 * *
 * 
 * N = 2:
 *  *
 * ***
 * 
 * N = 3:
 *   *
 *  ***
 * *****
 * 
 * N = 4:
 *    *
 *   ***
 *  *****
 * *******
 * 
 * N = 5:
 *     *
 *    ***
 *   *****
 *  *******
 * *********
 */

#include <stdio.h>

/*
 * Function: printTree
 * -------------------
 * Prints a Christmas tree of height N
 * 
 * n: height of the tree (number of levels)
 * 
 * Hints:
 * 1. For each level i (from 1 to n):
 *    - Print (n - i) spaces
 *    - Print (2*i - 1) asterisks
 *    - Print newline
 * 
 * 2. You'll need nested loops:
 *    - Outer loop: for each level
 *    - Inner loop 1: for printing spaces
 *    - Inner loop 2: for printing asterisks
 * 
 * Alternative approach:
 * - For level i (from 0 to n-1):
 *   - Spaces: n - i - 1
 *   - Asterisks: 2*i + 1
 */
void printTree(int n) {
    // TODO: Your code here
    
}

/*
 * Helper function to compare output - DO NOT MODIFY
 */
void testTree(int n, const char* description) {
    printf("Test: %s (N = %d)\n", description, n);
    printf("Output:\n");
    printTree(n);
    printf("\n");
}

/*
 * Test function - DO NOT MODIFY
 */
void runTests() {
    printf("=================================\n");
    printf("Christmas Tree Pattern Tests\n");
    printf("=================================\n\n");
    
    // Test 1: Smallest tree
    testTree(1, "Single level tree");
    
    // Test 2: Small tree
    testTree(2, "Two level tree");
    
    // Test 3: Medium tree
    testTree(3, "Three level tree");
    
    // Test 4: Larger tree
    testTree(5, "Five level tree");
    
    // Test 5: Big tree
    testTree(7, "Seven level tree");
    
    printf("\n=================================\n");
    printf("Visual inspection required!\n");
    printf("Check that trees are:\n");
    printf("- Centered (same spaces on left)\n");
    printf("- Symmetrical\n");
    printf("- Growing by 2 asterisks per level\n");
    printf("=================================\n");
}

/*
 * Bonus challenge (optional):
 * ----------------------------
 * 1. Add a tree trunk (1-2 rows of | at the bottom)
 * 2. Print a tree with decorations (use different characters like O, @, *)
 * 3. Print multiple trees side by side
 */

int main() {
    runTests();
    
    // Uncomment to test with user input:
    /*
    int height;
    printf("Enter tree height: ");
    scanf("%d", &height);
    printf("\n");
    printTree(height);
    */
    
    return 0;
}

/*
 * Expected outputs for reference:
 * 
 * N = 1:
 * *
 * 
 * N = 2:
 *  *
 * ***
 * 
 * N = 3:
 *   *
 *  ***
 * *****
 * 
 * N = 5:
 *     *
 *    ***
 *   *****
 *  *******
 * *********
 * 
 * N = 7:
 *       *
 *      ***
 *     *****
 *    *******
 *   *********
 *  ***********
 * *************
 */
