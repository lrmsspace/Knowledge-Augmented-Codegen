// Source: https://leetcode.com/problems/minimum-operations-to-make-array-elements-zero/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D array queries, where queries[i] is of the form [l, r]. Each queries[i] defines an array of integers nums consisting of elements ranging from l to r, both inclusive.
//
// In one operation, you can:
//
//
// 	Select two integers a and b from the array.
// 	Replace them with floor(a / 4) and floor(b / 4).
//
//
// Your task is to determine the minimum number of operations required to reduce all elements of the array to zero for each query. Return the sum of the results for all queries.
//
// Example:
// Input: queries = [[1,2],[2,4]]
//
// Output: 3
//
// Explanation:
//
// For queries[0]:
//
//
// 	The initial array is nums = [1, 2].
// 	In the first operation, select nums[0] and nums[1]. The array becomes [0, 0].
// 	The minimum number of operations required is 1.
//
//
// For queries[1]:
//
//
// 	The initial array is nums = [2, 3, 4].
// 	In the first operation, select nums[0] and nums[2]. The array becomes [0, 3, 1].
// 	In the second operation, select nums[1] and nums[2]. The array becomes [0, 0, 0].
// 	The minimum number of operations required is 2.
//
//
// The output is 1 + 2 = 3.
//
// Constraints:
// 1 <= queries.length <= 105
// 	queries[i].length == 2
// 	queries[i] == [l, r]
// 	1 <= l < r <= 109
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Gray code (number, simulation)
//   • When to use: Use when generating a sequence of numbers where adjacent values must differ by only one bit, or for error detection in digital systems. It is also useful for certain combinatorial problems.
//   • Idea: Gray code is a binary numeral system where two successive values differ in exactly one bit position. It can be generated efficiently using bitwise operations in O(1) time per code, or O(N) for N codes.
//   • Invariants: The number of bits in the generated Gray code G(n) is equal to the number of bits in the input binary n.; G(0) is always 0, and G(1) is always 1.
//   • Tips: The most common formula for converting binary n to Gray code G(n) is G(n) = n ^ (n >> 1).; To convert Gray code G(n) back to binary n, use a series of XOR operations: n = G(n) ^ (G(n) >> 1) ^ (G(n) >> 2) ^ ... until zero.
//   • Pitfalls: Confusing Gray code with standard binary representation, which can have multiple bit changes between successive numbers.; Incorrectly implementing the conversion formulas, especially the Gray to binary conversion.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long minOperations(int** queries, int queriesSize, int* queriesColSize) {
    long long totalOperations = 0;

    for (int i = 0; i < queriesSize; i++) {
        int l = queries[i][0];
        int r = queries[i][1];
        long long operations = 0;

        // Calculate the number of elements in the range [l, r]
        long long n = (long long)(r - l + 1);

        // Each operation reduces two elements by a factor of 4
        // We can calculate the number of operations needed to reduce all elements to zero
        while (n > 0) {
            operations += n / 2; // Each operation can reduce two elements
            n /= 4; // After each operation, the effective size is reduced by a factor of 4
        }

        totalOperations += operations;
    }

    return totalOperations;     
}
