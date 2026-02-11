/*
 * Task 1: Find Maximum in Array
 * Level: Basic
 * 
 * Description:
 * Write a function that finds the maximum value in an array of integers.
 * 
 * Skills tested:
 * - Loops (for/while)
 * - Conditions (if/else)
 * - Arrays
 * - Function implementation
 */

#include <stdio.h>

/*
 * Function: findMax
 * -----------------
 * Finds the maximum value in an array
 * 
 * arr: array of integers
 * size: number of elements in array
 * 
 * returns: maximum value from the array
 */
int findMax(int arr[], int size) {
    // TODO: Your code here
    // Hint: Initialize max with first element, then iterate through array
    
    return 0; // Replace with actual result
}

/*
 * Test function - DO NOT MODIFY
 */
void runTests() {
    printf("Running tests...\n\n");
    
    // Test 1: Simple array
    int test1[] = {3, 7, 2, 9, 1};
    int result1 = findMax(test1, 5);
    printf("Test 1: {3, 7, 2, 9, 1}\n");
    printf("Expected: 9, Got: %d %s\n\n", result1, result1 == 9 ? "✓ PASS" : "✗ FAIL");
    
    // Test 2: Array with negative numbers
    int test2[] = {-5, -2, -10, -1};
    int result2 = findMax(test2, 4);
    printf("Test 2: {-5, -2, -10, -1}\n");
    printf("Expected: -1, Got: %d %s\n\n", result2, result2 == -1 ? "✓ PASS" : "✗ FAIL");
    
    // Test 3: Array with single element
    int test3[] = {42};
    int result3 = findMax(test3, 1);
    printf("Test 3: {42}\n");
    printf("Expected: 42, Got: %d %s\n\n", result3, result3 == 42 ? "✓ PASS" : "✗ FAIL");
    
    // Test 4: Max at the beginning
    int test4[] = {100, 50, 25, 10};
    int result4 = findMax(test4, 4);
    printf("Test 4: {100, 50, 25, 10}\n");
    printf("Expected: 100, Got: %d %s\n\n", result4, result4 == 100 ? "✓ PASS" : "✗ FAIL");
    
    // Test 5: All elements are the same
    int test5[] = {5, 5, 5, 5, 5};
    int result5 = findMax(test5, 5);
    printf("Test 5: {5, 5, 5, 5, 5}\n");
    printf("Expected: 5, Got: %d %s\n\n", result5, result5 == 5 ? "✓ PASS" : "✗ FAIL");
}

int main() {
    printf("=================================\n");
    printf("Task 1: Find Maximum in Array\n");
    printf("=================================\n\n");
    
    runTests();
    
    return 0;
}
