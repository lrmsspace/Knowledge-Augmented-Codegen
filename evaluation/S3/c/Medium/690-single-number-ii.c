// Source: https://leetcode.com/problems/single-number-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums where every element appears three times except for one, which appears exactly once. Find the single element and return it.
//
// You must implement a solution with a linear runtime complexity and use only constant extra space.
//
// Example:
// Input: nums = [2,2,3,2]
// Output: 3
//
// Constraints:
// 1 <= nums.length <= 3 * 104
// 	-231 <= nums[i] <= 231 - 1
// 	Each element in nums appears exactly three times except for one element which appears once.
//
// Helpful references (internal KB):
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Bit manipulation (number, enumeration, simulation)
//   • When to use: When problems involve manipulating individual bits of numbers, representing sets as bitmasks, or optimizing operations on powers of two. It is also useful for certain combinatorics and dynamic programming problems.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators. This technique is often used to optimize computations, manage boolean flags efficiently, or represent subsets, typically achieving O(1) complexity for fixed-size integers.
//   • Invariants: Each bit in the mask accurately reflects the inclusion or exclusion status of its corresponding element.; Bitwise operations maintain the integrity of unaffected bits.
//   • Tips: Use (1 << k) to create a mask with the k-th bit set.; n & (n-1) clears the least significant set bit.
//   • Pitfalls: Incorrect operator precedence can lead to subtle bugs.; Mixing signed and unsigned integers in bitwise operations can yield unexpected results.
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

int singleNumber(int* nums, int numsSize) {
    int count[32] = {0}; // Count of bits at each position

    // Count the number of 1s in each bit position
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < 32; j++) {
            count[j] += (nums[i] >> j) & 1; // Increment count if the j-th bit is set
        }
    }

    int result = 0;
    // Reconstruct the single number from the counts
    for (int j = 0; j < 32; j++) {
        if (count[j] % 3 != 0) { // If count is not a multiple of 3, this bit belongs to the single number
            result |= (1 << j); // Set the j-th bit in the result
        }
    }

    return result;      
}
