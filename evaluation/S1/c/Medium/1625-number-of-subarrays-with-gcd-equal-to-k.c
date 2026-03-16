// Source: https://leetcode.com/problems/number-of-subarrays-with-gcd-equal-to-k/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return the number of subarrays of nums where the greatest common divisor of the subarray's elements is k.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// The greatest common divisor of an array is the largest integer that evenly divides all the array elements.
//
// Example:
// Input: nums = [9,3,1,2,6,3], k = 3
// Output: 4
// Explanation: The subarrays of nums where 3 is the greatest common divisor of all the subarray's elements are:
// - [9,3,1,2,6,3]
// - [9,3,1,2,6,3]
// - [9,3,1,2,6,3]
// - [9,3,1,2,6,3]
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i], k <= 109
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Euclidean algorithm for computing the greatest common divisor (number, gcd)
//   • When to use: Use this algorithm to efficiently find the greatest common divisor of two or more integers, or as a subroutine for tasks like simplifying fractions or finding the least common multiple.
//   • Idea: The Euclidean algorithm is an efficient method for computing the greatest common divisor (GCD) of two non-negative integers by repeatedly applying the division algorithm. It operates in logarithmic time complexity, O(log min(a, b)).
//   • Invariants: The greatest common divisor of the current pair (a, b) remains constant and equal to the GCD of the original inputs.; The second number (b) is always non-negative.
//   • Tips: Handle the base case where one of the numbers is zero; gcd(a, 0) = a.; The algorithm works for any order of inputs; if a < b, the first step swaps them effectively.
//   • Pitfalls: Forgetting to take absolute values if negative inputs are possible, as GCD is typically defined for non-negative integers.; Incorrectly handling the zero input case, which can lead to infinite loops or incorrect results.
// - Garner's algorithm
//  (number, array, enumeration)
//   • When to use: Use when reconstructing a large integer from a system of congruences with pairwise coprime moduli, offering an alternative to the direct Chinese Remainder Theorem approach.
//   • Idea: Garner's algorithm efficiently reconstructs an integer from its remainders modulo a set of pairwise coprime numbers, by computing its mixed radix representation coefficients. It typically runs in O(k^2 log M) time, where k is the number of moduli and M is the maximum modulus, assuming modular inverse takes log M time.
//   • Invariants: At the start of iteration j, the partial sum $V_{j-1}$ satisfies $V_{j-1} \equiv a_i \pmod{p_i}$ for all $i < j$.; For each iteration j, the coefficient $x_j$ is uniquely determined in the range $[0, p_j - 1]$.
//   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Precompute modular inverses for efficiency, especially if many are needed.
//   • Pitfalls: Incorrectly calculating modular inverses, leading to wrong coefficients.; Not handling large intermediate products, which can cause integer overflow.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int subarrayGCD(int* nums, int numsSize, int k) {
    int count = 0;

    for (int i = 0; i < numsSize; i++) {
        int current_gcd = 0;
        for (int j = i; j < numsSize; j++) {
            // Compute GCD of current_gcd and nums[j]
            int a = current_gcd;
            int b = nums[j];
            while (b != 0) {
                int temp = b;
                b = a % b;
                a = temp;
            }
            current_gcd = a;

            if (current_gcd == k) {
                count++;
            } else if (current_gcd < k) {
                break; // No need to continue if GCD is already less than k
            }
        }
    }

    return count;       
}
