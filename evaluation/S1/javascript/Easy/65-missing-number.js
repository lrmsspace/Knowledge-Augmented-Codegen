// Source: https://leetcode.com/problems/missing-number/   |   Difficulty: Easy
//
// Problem Description:
// Given an array nums containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.
//
// Example:
// Input: nums = [3,0,1]
//
// Output: 2
//
// Explanation:
//
// n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 2 is the missing number in the range since it does not appear in nums.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 104
// 	0 <= nums[i] <= n
// 	All the numbers of nums are unique.
//
//
//  
// Follow up: Could you implement a solution using only O(1) extra space complexity and O(n) runtime complexity?
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Gray code (number, prefix-xor)
//   • When to use: Use when a sequence of binary numbers is needed where successive values differ by only one bit. This is useful for error detection in digital systems or position encoders.
//   • Idea: Gray code is a binary numeral system where two successive values differ in only one bit position. Conversion from a binary number `n` to its Gray code `G(n)` is `n ^ (n >> 1)`, and the inverse operation can also be performed efficiently in O(log N) time.
//   • Invariants: For binary to Gray: The resulting Gray code `G(n)` differs from `n` by exactly one bit for each `n`.; For inverse Gray to binary: The variable `n` accumulates the correct binary value from MSB to LSB.
//   • Tips: Understand the core `n ^ (n >> 1)` transformation for binary to Gray.; The inverse Gray code conversion involves iteratively XORing with right-shifted values.
//   • Pitfalls: Confusing Gray code with standard binary representation.; Incorrectly implementing the iterative inverse transformation logic.
// - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
//   • When to use: When you need O(1) query time for any associative operation (like sum, min, max, GCD) on a static array, after an O(N log N) preprocessing step.
//   • Idea: A Disjoint Sparse Table is a data structure that supports O(1) range queries for any associative operation on a static array. It achieves this by precomputing results for specific disjoint and overlapping ranges, with an O(N log N) construction time and space complexity.
//   • Invariants: table[k][i] stores the result of the operation for a range of length 2^k starting at index i.; For any query [L, R], the result is obtained by combining two precomputed values from blocks that cover [L, mid] and [mid+1, R].
//   • Tips: Understand the block decomposition based on powers of two for construction.; Queries combine results from two precomputed blocks that cover the query range.
//   • Pitfalls: Does not support point updates efficiently; any modification requires a full rebuild.; Higher space complexity of O(N log N) compared to some other range query structures.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var missingNumber = function(nums) {
    const n = nums.length;
    const expectedSum = (n * (n + 1)) / 2;
    const actualSum = nums.reduce((acc, num) => acc + num, 0);
    return expectedSum - actualSum; 
};
