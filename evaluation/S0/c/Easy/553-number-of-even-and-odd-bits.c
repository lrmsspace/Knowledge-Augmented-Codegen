// Source: https://leetcode.com/problems/number-of-even-and-odd-bits/   |   Difficulty: Easy
//
// Problem Description:
// You are given a positive integer n.
//
// Let even denote the number of even indices in the binary representation of n with value 1.
//
// Let odd denote the number of odd indices in the binary representation of n with value 1.
//
// Note that bits are indexed from right to left in the binary representation of a number.
//
// Return the array [even, odd].
//
// Example:
// Input: n = 50
//
// Output: [1,2]
//
// Explanation:
//
// The binary representation of 50 is 110010.
//
// It contains 1 on indices 1, 4, and 5.
//
// Constraints:
// 1 <= n <= 1000
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* evenOddBit(int n, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    result[0] = 0; // even count
    result[1] = 0; // odd count
    int index = 0;

    while (n > 0) {
        if (n & 1) {
            if (index % 2 == 0) {
                result[0]++; // even index
            } else {
                result[1]++; // odd index
            }
        }
        n >>= 1; // right shift to process the next bit
        index++;
    }

    *returnSize = 2;
    return result;      
}
