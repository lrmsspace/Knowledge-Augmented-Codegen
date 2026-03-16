// Source: https://leetcode.com/problems/minimize-length-of-array-using-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums containing positive integers.
//
// Your task is to minimize the length of nums by performing the following operations any number of times (including zero):
//
//
// 	Select two distinct indices i and j from nums, such that nums[i] > 0 and nums[j] > 0.
// 	Insert the result of nums[i] % nums[j] at the end of nums.
// 	Delete the elements at indices i and j from nums.
//
//
// Return an integer denoting the minimum length of nums after performing the operation any number of times.
//
// Example:
// Input: nums = [1,4,3,1]
// Output: 1
// Explanation: One way to minimize the length of the array is as follows:
// Operation 1: Select indices 2 and 1, insert nums[2] % nums[1] at the end and it becomes [1,4,3,1,3], then delete elements at indices 2 and 1.
// nums becomes [1,1,3].
// Operation 2: Select indices 1 and 2, insert nums[1] % nums[2] at the end and it becomes [1,1,3,1], then delete elements at indices 1 and 2.
// nums becomes [1,1].
// Operation 3: Select indices 1 and 0, insert nums[1] % nums[0] at the end and it becomes [1,1,0], then delete elements at indices 1 and 0.
// nums becomes [0].
// The length of nums cannot be reduced further. Hence, the answer is 1.
// It can be shown that 1 is the minimum achievable length.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Euler's totient function
//  (array, number, sieve, enumeration)
//   • When to use: Use when needing to count positive integers up to a given integer n that are relatively prime to n. It is also useful for problems involving modular arithmetic, group theory, and cryptographic applications.
//   • Idea: Euler's totient function, φ(n), counts the number of positive integers up to a given integer n that are relatively prime to n. It can be computed using prime factorization in O(sqrt(N)) or for a range using a sieve in O(N log log N).
//   • Invariants: For a sieve, phi[i] correctly stores the totient value for i after processing all its prime factors.; When factorizing n, n is continuously reduced by its smallest prime factor until it becomes 1.
//   • Tips: For a single n, find its prime factors and apply the product formula.; For computing φ(n) for all n up to a limit, use a sieve similar to Sieve of Eratosthenes.
//   • Pitfalls: Incorrectly handling repeated prime factors in the formula.; Integer overflow when calculating products for very large n.
// - Operations on polynomials and series (array, gcd)
//   • When to use: When performing algebraic operations on polynomials or power series, such as finding their greatest common divisor, differentiation, integration, or computing series expansions like inverse, logarithm, and exponential, especially in modular arithmetic.
//   • Idea: This card details various algebraic operations on polynomials and power series, including finding their greatest common divisor (GCD) and computing derivatives, integrals, inverses, logarithms, exponentials, and powers. These operations manipulate polynomial coefficients, often within a modular arithmetic context, with many achieving O(N log N) or O(N log NK) complexity.
//   • Invariants: The degree of the resulting polynomial/series is correctly maintained after each operation.; Coefficients are always reduced modulo m if modular arithmetic is applied.
//   • Tips: Represent polynomials as arrays of coefficients, typically from lowest to highest degree.; Modular arithmetic is crucial for many polynomial operations, including GCD, to prevent overflow and ensure results stay within a finite field.
//   • Pitfalls: Forgetting to handle modular inverses for division operations (e.g., integration, polynomial division in GCD, inverse, log).; Incorrectly handling the constant term or leading coefficients, especially for inverse, logarithm, or polynomial division.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
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
var minimumArrayLength = function(nums) {
    const uniqueNumbers = new Set(nums);
    return uniqueNumbers.size;
};
