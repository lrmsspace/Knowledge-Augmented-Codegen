// Source: https://leetcode.com/problems/numbers-with-repeated-digits/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n, return the number of positive integers in the range [1, n] that have at least one repeated digit.
//
// Example:
// Input: n = 20
// Output: 1
// Explanation: The only positive number (<= 20) with at least 1 repeated digit is 11.
//
// Constraints:
// 1 <= n <= 109
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numDupDigitsAtMostN(int n) {
    int digits[10];
    int len = 0;
    int temp = n + 1; // consider numbers less than or equal to n
    while (temp > 0) {
        digits[len++] = temp % 10;
        temp /= 10;
    }

    // Count numbers with unique digits and length less than len
    int count = 0;
    for (int i = 1; i < len; ++i) {
        int uniqueDigits = 9;
        int availableDigits = 9;
        for (int j = 1; j < i; ++j) {
            uniqueDigits *= availableDigits;
            availableDigits--;
        }
        count += uniqueDigits;
    }

    // Count numbers with unique digits and length equal to len
    int usedMask = 0;
    for (int i = len - 1; i >= 0; --i) {
        int digit = digits[i];
        for (int d = (i == len - 1) ? 1 : 0; d < digit; ++d) {
            if (!(usedMask & (1 << d))) {
                int uniqueDigits = 1;
                int availableDigits = 10 - __builtin_popcount(usedMask) - 1;
                for (int j = 0; j < i; ++j) {
                    uniqueDigits *= availableDigits;
                    availableDigits--;
                }
                count += uniqueDigits;
            }
        }
        if (usedMask & (1 << digit)) {
            break;
        }
        usedMask |= (1 << digit);
        if (i == 0) {
            count++; // include the number n itself if it has all unique digits
        }
    }

    return n - count;       
}
