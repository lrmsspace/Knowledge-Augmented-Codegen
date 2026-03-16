// Source: https://leetcode.com/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string num representing the digits of a very large integer and an integer k. You are allowed to swap any two adjacent digits of the integer at most k times.
//
// Return the minimum integer you can obtain also as a string.
//
// Example:
// Input: num = "4321", k = 4
// Output: "1342"
// Explanation: The steps to obtain the minimum integer from 4321 with 4 adjacent swaps are shown.
//
// Constraints:
// 1 <= num.length <= 3 * 104
// 	num consists of only digits and does not contain leading zeros.
// 	1 <= k <= 109
//
// Helpful references (internal KB):
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
//   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
//   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
//   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* minInteger(char* num, int k) {
    int len = strlen(num);
    int pos[10][len]; /* positions of each digit */
    int posCount[10]; /* counts of each digit */
    for (int i = 0; i < 10; ++i) posCount[i] = 0;
    for (int i = 0; i < len; ++i) {
        int d = num[i] - '0';
        pos[d][posCount[d]++] = i;
    }

    /* Fenwick Tree for counting shifts */
    int bit[len + 1];
    memset(bit, 0, sizeof(bit));
    #define BIT_ADD(i, v) do { for (++i; i <= len; i += i & -i) bit[i] += (v); } while(0)
    #define BIT_SUM(i) ({ int s = 0; for (++i; i > 0; i -= i & -i) s += bit[i]; s; })

    char *res = (char*)malloc((len + 1) * sizeof(char));
    int resPos = 0;
    for (int i = 0; i < len; ++i) {
        for (int d = 0; d < 10; ++d) {
            if (posCount[d] == 0) continue;
            int origIdx = pos[d][0];
            int shifts = BIT_SUM(origIdx);
            int currIdx = origIdx + shifts;
            int cost = currIdx - i;
            if (cost <= k) {
                k -= cost;
                res[resPos++] = (char)(d + '0');
                BIT_ADD(0, 1);
                BIT_ADD(origIdx, -1);
                /* remove used position */
                for (int j = 1; j < posCount[d]; ++j) {
                    pos[d][j - 1] = pos[d][j];
                }
                posCount[d]--;
                break;
            }
        }
    }
    res[resPos] = '\0';
    return res;     
}
