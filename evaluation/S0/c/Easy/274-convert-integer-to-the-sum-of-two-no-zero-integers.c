// Source: https://leetcode.com/problems/convert-integer-to-the-sum-of-two-no-zero-integers/   |   Difficulty: Easy
//
// Problem Description:
// No-Zero integer is a positive integer that does not contain any 0 in its decimal representation.
//
// Given an integer n, return a list of two integers [a, b] where:
//
//
// 	a and b are No-Zero integers.
// 	a + b = n
//
//
// The test cases are generated so that there is at least one valid solution. If there are many valid solutions, you can return any of them.
//
// Example:
// Input: n = 2
// Output: [1,1]
// Explanation: Let a = 1 and b = 1.
// Both a and b are no-zero integers, and a + b = 2 = n.
//
// Constraints:
// 2 <= n <= 104
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getNoZeroIntegers(int n, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    for (int a = 1; a < n; ++a) {
        int b = n - a;
        int tempA = a, tempB = b;
        int hasZero = 0;

        while (tempA > 0) {
            if (tempA % 10 == 0) {
                hasZero = 1;
                break;
            }
            tempA /= 10;
        }

        while (tempB > 0) {
            if (tempB % 10 == 0) {
                hasZero = 1;
                break;
            }
            tempB /= 10;
        }

        if (!hasZero) {
            result[0] = a;
            result[1] = b;
            *returnSize = 2;
            return result;
        }
    }

    // This line should never be reached due to problem constraints
    *returnSize = 0;
    return NULL;        
}
