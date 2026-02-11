/*
 * Task 2: Reverse String with Pointers
 * Level: Intermediate
 * 
 * Description:
 * Write a function that reverses a string in-place using pointers.
 * "In-place" means modifying the original string without creating a new one.
 * 
 * Skills tested:
 * - Pointers
 * - String manipulation
 * - Character swapping
 * - Loop control
 */

#include <stdio.h>
#include <string.h>

/*
 * Function: reverseString
 * -----------------------
 * Reverses a string in-place using two pointers (start and end)
 * 
 * str: pointer to string to reverse (null-terminated)
 * 
 * returns: nothing (modifies string in-place)
 * 
 * Hint: Use two pointers - one at start, one at end
 *       Swap characters and move pointers towards each other
 *       Stop when pointers meet in the middle
 */
void reverseString(char* str) {
    // TODO: Your code here
    // Example algorithm:
    // 1. Get pointer to start of string
    // 2. Get pointer to end of string (last character before '\0')
    // 3. While start < end:
    //    a. Swap characters at start and end
    //    b. Move start forward, end backward
    
}

/*
 * Helper function to test - DO NOT MODIFY
 */
void testReverse(const char* original, const char* expected) {
    char buffer[100];
    strcpy(buffer, original);
    
    reverseString(buffer);
    
    int passed = strcmp(buffer, expected) == 0;
    printf("Input:    \"%s\"\n", original);
    printf("Expected: \"%s\"\n", expected);
    printf("Got:      \"%s\" %s\n\n", buffer, passed ? "✓ PASS" : "✗ FAIL");
}

/*
 * Test function - DO NOT MODIFY
 */
void runTests() {
    printf("Running tests...\n\n");
    
    // Test 1: Simple word
    printf("Test 1:\n");
    testReverse("hello", "olleh");
    
    // Test 2: Palindrome (should be same after reverse)
    printf("Test 2:\n");
    testReverse("radar", "radar");
    
    // Test 3: Single character
    printf("Test 3:\n");
    testReverse("a", "a");
    
    // Test 4: Empty string
    printf("Test 4:\n");
    testReverse("", "");
    
    // Test 5: Even length string
    printf("Test 5:\n");
    testReverse("abcd", "dcba");
    
    // Test 6: Odd length string
    printf("Test 6:\n");
    testReverse("abc", "cba");
    
    // Test 7: String with spaces
    printf("Test 7:\n");
    testReverse("hello world", "dlrow olleh");
}

int main() {
    printf("==========================================\n");
    printf("Task 2: Reverse String with Pointers\n");
    printf("==========================================\n\n");
    
    runTests();
    
    return 0;
}
