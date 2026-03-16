// Source: https://leetcode.com/problems/find-the-maximum-divisibility-score/   |   Difficulty: Easy
//
// Problem Description:
// You are given two integer arrays nums and divisors.
//
// The divisibility score of divisors[i] is the number of indices j such that nums[j] is divisible by divisors[i].
//
// Return the integer divisors[i] with the maximum divisibility score. If multiple integers have the maximum score, return the smallest one.
//
// Example:
// Input: nums = [2,9,15,50], divisors = [5,3,7,2]
//
// Output: 2
//
// Explanation:
//
// The divisibility score of divisors[0] is 2 since nums[2] and nums[3] are divisible by 5.
//
// The divisibility score of divisors[1] is 2 since nums[1] and nums[2] are divisible by 3.
//
// The divisibility score of divisors[2] is 0 since none of the numbers in nums is divisible by 7.
//
// The divisibility score of divisors[3] is 2 since nums[0] and nums[3] are divisible by 2.
//
// As divisors[0], divisors[1], and divisors[3] have the same divisibility score, we return the smaller one which is divisors[3].
//
// Constraints:
// 1 <= nums.length, divisors.length <= 1000
// 	1 <= nums[i], divisors[i] <= 109
//
// Helpful references (internal KB):
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this approach when you need to calculate the total count or sum of all positive divisors for a given integer, typically by leveraging its prime factorization.
//   • Idea: The number of divisors d(n) and sum of divisors sigma(n) are arithmetic functions derived from the prime factorization of an integer n. Both can be computed efficiently by first finding prime factors and their exponents, resulting in an O(sqrt(N)) or O(log N) complexity with precomputed primes.
//   • Invariants: The current count of divisors is the product of (exponent + 1) for all prime factors found so far.; The current sum of divisors is the product of (1 + p + ... + p^e) for all prime factors found so far.
//   • Tips: Precompute primes using a sieve for efficiency when dealing with multiple queries or large numbers.; For sum of divisors, the formula is sigma(n) = product((1 + p_i + ... + p_i^e_i)) for each prime factor p_i^e_i.
//   • Pitfalls: Forgetting to handle n=1 correctly, which has one divisor.; Integer overflow when calculating sums or products of large powers, especially for sum of divisors.
// - Euler's totient function
//  (array, number, enumeration)
//   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
//   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
//   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
//   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
//   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number[]} divisors
 * @return {number}
 */
var maxDivScore = function(nums, divisors) {
    let maxScore = -1;
    let result = -1;
    for (const divisor of divisors) {
        let score = 0;
        for (const num of nums) {
            if (num % divisor === 0) {
                score++;
            }
        }
        if (score > maxScore || (score === maxScore && divisor < result)) {
            maxScore = score;
            result = divisor;
        }
    }
    return result;
};
