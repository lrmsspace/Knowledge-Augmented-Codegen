// Source: https://leetcode.com/problems/smallest-missing-non-negative-integer-after-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer value.
//
// In one operation, you can add or subtract value from any element of nums.
//
//
// 	For example, if nums = [1,2,3] and value = 2, you can choose to subtract value from nums[0] to make nums = [-1,2,3].
//
//
// The MEX (minimum excluded) of an array is the smallest missing non-negative integer in it.
//
//
// 	For example, the MEX of [-1,2,3] is 0 while the MEX of [1,0,3] is 2.
//
//
// Return the maximum MEX of nums after applying the mentioned operation any number of times.
//
// Example:
// Input: nums = [1,-10,7,13,6,8], value = 5
// Output: 4
// Explanation: One can achieve this result by applying the following operations:
// - Add value to nums[1] twice to make nums = [1,0,7,13,6,8]
// - Subtract value from nums[2] once to make nums = [1,0,2,13,6,8]
// - Subtract value from nums[3] twice to make nums = [1,0,2,3,6,8]
// The MEX of nums is 4. It can be shown that 4 is the maximum MEX we can achieve.
//
// Constraints:
// 1 <= nums.length, value <= 105
// 	-109 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Hash Tables (array, number, string, hashing)
//   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
//   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
//   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
//   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
//   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
// - Garner's algorithm
//  (number, array, enumeration)
//   • When to use: Use when reconstructing a large integer from a system of congruences with pairwise coprime moduli, offering an alternative to the direct Chinese Remainder Theorem approach.
//   • Idea: Garner's algorithm efficiently reconstructs an integer from its remainders modulo a set of pairwise coprime numbers, by computing its mixed radix representation coefficients. It typically runs in O(k^2 log M) time, where k is the number of moduli and M is the maximum modulus, assuming modular inverse takes log M time.
//   • Invariants: At the start of iteration j, the partial sum $V_{j-1}$ satisfies $V_{j-1} \equiv a_i \pmod{p_i}$ for all $i < j$.; For each iteration j, the coefficient $x_j$ is uniquely determined in the range $[0, p_j - 1]$.
//   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Precompute modular inverses for efficiency, especially if many are needed.
//   • Pitfalls: Incorrectly calculating modular inverses, leading to wrong coefficients.; Not handling large intermediate products, which can cause integer overflow.
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

int findSmallestInteger(int* nums, int numsSize, int value) {
    int count[value];
    for (int i = 0; i < value; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < numsSize; i++) {
        int mod = nums[i] % value;
        if (mod < 0) {
            mod += value;
        }
        if (nums[i] >= 0) {
            count[mod]++;
        }
    }

    int mex = 0;
    while (1) {
        int mod = mex % value;
        if (count[mod] == 0) {
            return mex;
        }
        count[mod]--;
        mex++;
    }       
}
