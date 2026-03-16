// Source: https://leetcode.com/problems/maximum-odd-binary-number/   |   Difficulty: Easy
//
// Problem Description:
// You are given a binary string s that contains at least one '1'.
//
// You have to rearrange the bits in such a way that the resulting binary number is the maximum odd binary number that can be created from this combination.
//
// Return a string representing the maximum odd binary number that can be created from the given combination.
//
// Note that the resulting string can have leading zeros.
//
// Example:
// Input: s = "010"
// Output: "001"
// Explanation: Because there is just one '1', it must be in the last position. So the answer is "001".
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists only of '0' and '1'.
// 	s contains at least one '1'.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
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

char* maximumOddBinaryNumber(char* s) {
    int count0 = 0, count1 = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '0') {
            count0++;
        } else {
            count1++;
        }
    }

    // The maximum odd binary number will have all '1's followed by all '0's, with at least one '1' at the end.
    // So we need to place all '1's first and then all '0's, ensuring the last character is '1'.
    // This means we will have (count1 - 1) '1's followed by count0 '0's and then one '1' at the end.

    int totalLength = count0 + count1;
    char* result = (char*)malloc((totalLength + 1) * sizeof(char)); // +1 for null terminator
    if (result == NULL) {
        return NULL; // Handle memory allocation failure
    }

    int index = 0;
    for (int i = 0; i < count1 - 1; i++) {
        result[index++] = '1';
    }
    for (int i = 0; i < count0; i++) {
        result[index++] = '0';
    }
    result[index++] = '1'; // Add the last '1'
    result[index] = '\0'; // Null-terminate the string

    return result;      
}
