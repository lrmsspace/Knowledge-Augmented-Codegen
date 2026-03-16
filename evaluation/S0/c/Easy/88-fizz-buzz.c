// Source: https://leetcode.com/problems/fizz-buzz/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return a string array answer (1-indexed) where:
//
//
// 	answer[i] == "FizzBuzz" if i is divisible by 3 and 5.
// 	answer[i] == "Fizz" if i is divisible by 3.
// 	answer[i] == "Buzz" if i is divisible by 5.
// 	answer[i] == i (as a string) if none of the above conditions are true.
//
// Example:
// Input: n = 3
// Output: ["1","2","Fizz"]
//
// Constraints:
// 1 <= n <= 104
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** fizzBuzz(int n, int* returnSize) {
    char **result = (char **)malloc(n * sizeof(char *));
    *returnSize = n;

    for (int i = 1; i <= n; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            result[i - 1] = (char *)malloc(9 * sizeof(char)); // "FizzBuzz" + '\0'
            sprintf(result[i - 1], "FizzBuzz");
        } else if (i % 3 == 0) {
            result[i - 1] = (char *)malloc(5 * sizeof(char)); // "Fizz" + '\0'
            sprintf(result[i - 1], "Fizz");
        } else if (i % 5 == 0) {
            result[i - 1] = (char *)malloc(5 * sizeof(char)); // "Buzz" + '\0'
            sprintf(result[i - 1], "Buzz");
        } else {
            result[i - 1] = (char *)malloc(12 * sizeof(char)); // max digits for int + '\0'
            sprintf(result[i - 1], "%d", i);
        }
    }

    return result;      
}
