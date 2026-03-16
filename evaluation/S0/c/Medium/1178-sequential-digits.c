// Source: https://leetcode.com/problems/sequential-digits/   |   Difficulty: Medium
//
// Problem Description:
// An integer has sequential digits if and only if each digit in the number is one more than the previous digit.
//
// Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.
//
// Example:
// Input: low = 100, high = 300
// Output: [123,234]
//
// Constraints:
// 10 <= low <= high <= 10^9
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sequentialDigits(int low, int high, int* returnSize) {
    int base[] = {12, 123, 1234, 12345, 123456, 1234567, 12345678, 123456789};
    int* result = (int*)malloc(0);
    *returnSize = 0;

    for (int i = 0; i < sizeof(base) / sizeof(base[0]); i++) {
        int num = base[i];
        for (int j = 0; j <= 9 - (i + 2); j++) {
            int candidate = num + j * 111111111;
            if (candidate >= low && candidate <= high) {
                result = (int*)realloc(result, sizeof(int) * (*returnSize + 1));
                result[*returnSize] = candidate;
                (*returnSize)++;
            }
        }
    }

    return result;      
}
