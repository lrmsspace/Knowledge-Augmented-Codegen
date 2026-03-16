// Source: https://leetcode.com/problems/keep-multiplying-found-values-by-two/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of integers nums. You are also given an integer original which is the first number that needs to be searched for in nums.
//
// You then do the following steps:
//
//
// 	If original is found in nums, multiply it by two (i.e., set original = 2 * original).
// 	Otherwise, stop the process.
// 	Repeat this process with the new number as long as you keep finding the number.
//
//
// Return the final value of original.
//
// Example:
// Input: nums = [5,3,6,1,12], original = 3
// Output: 24
// Explanation: 
// - 3 is found in nums. 3 is multiplied by 2 to obtain 6.
// - 6 is found in nums. 6 is multiplied by 2 to obtain 12.
// - 12 is found in nums. 12 is multiplied by 2 to obtain 24.
// - 24 is not found in nums. Thus, 24 is returned.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i], original <= 1000
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Binary Exponentiation (number, mod-exp, divide-and-conquer)
//   • When to use: Use when calculating a^n efficiently, especially for large n or when results need to be taken modulo some number. It reduces the number of multiplications from linear to logarithmic.
//   • Idea: Binary exponentiation computes a^n by repeatedly squaring the base and multiplying terms corresponding to the set bits in the exponent's binary representation. This method achieves a time complexity of O(log n) multiplications.
//   • Invariants: The product of `result` and `current_base` raised to the `remaining_exponent` equals the initial `a^N`.; `current_base` always represents `a` raised to the power of `2^k` for the current iteration `k`.
//   • Tips: Handle base cases like n=0 (result is 1) and n=1 (result is a).; Use long long or appropriate large integer types for intermediate products to prevent overflow.
//   • Pitfalls: Integer overflow if not using appropriate data types or modulo arithmetic.; Incorrectly handling negative exponents (typically not covered by basic binary exponentiation).
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int findFinalValue(int* nums, int numsSize, int original) {
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == original) {
            original *= 2;
            i = -1; // Reset loop to check for the new original value
        }
    }
    return original;        
}
