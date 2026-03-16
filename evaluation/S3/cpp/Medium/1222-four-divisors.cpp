// Source: https://leetcode.com/problems/four-divisors/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return the sum of divisors of the integers in that array that have exactly four divisors. If there is no such integer in the array, return 0.
//
// Example:
// Input: nums = [21,4,7]
// Output: 32
// Explanation: 
// 21 has 4 divisors: 1, 3, 7, 21
// 4 has 3 divisors: 1, 2, 4
// 7 has 2 divisors: 1, 7
// The answer is the sum of divisors of 21 only.
//
// Constraints:
// 1 <= nums.length <= 104
// 	1 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this approach when you need to calculate the total count or sum of all positive divisors for a given integer, typically by leveraging its prime factorization.
//   • Idea: The number of divisors d(n) and sum of divisors sigma(n) are arithmetic functions derived from the prime factorization of an integer n. Both can be computed efficiently by first finding prime factors and their exponents, resulting in an O(sqrt(N)) or O(log N) complexity with precomputed primes.
//   • Invariants: The current count of divisors is the product of (exponent + 1) for all prime factors found so far.; The current sum of divisors is the product of (1 + p + ... + p^e) for all prime factors found so far.
//   • Tips: Precompute primes using a sieve for efficiency when dealing with multiple queries or large numbers.; For sum of divisors, the formula is sigma(n) = product((1 + p_i + ... + p_i^e_i)) for each prime factor p_i^e_i.
//   • Pitfalls: Forgetting to handle n=1 correctly, which has one divisor.; Integer overflow when calculating sums or products of large powers, especially for sum of divisors.
// - Integer factorization (number, array, enumeration, sieve, counting)
//   • When to use: Use when needing to find the prime factors of a composite number, especially for relatively small numbers or as a base case for more advanced algorithms.
//   • Idea: This algorithm finds the prime factorization of an integer by iteratively dividing it by its smallest prime factors. It typically checks divisors up to the square root of the number, achieving an O(sqrt(N)) time complexity.
//   • Invariants: The product of all found prime factors multiplied by the current remaining number equals the original input number.; All prime factors found so far are less than or equal to the current divisor being tested.
//   • Tips: Perform a primality test first to avoid unnecessary factorization attempts.; Only check divisors up to the square root of the number.
//   • Pitfalls: Trial division is pseudo-polynomial time, making it inefficient for very large numbers.; Forgetting to handle the case where the remaining number after division is itself a prime greater than its original square root.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int total_sum = 0;

        for (int n : nums) {
            int divisor_count = 0;
            int divisor_sum = 0;

            for (int i = 1; i * i <= n; ++i) {
                if (n % i == 0) {
                    divisor_count++;
                    divisor_sum += i;

                    if (i != n / i) {
                        divisor_count++;
                        divisor_sum += n / i;
                    }
                }

                if (divisor_count > 4) {
                    break;
                }
            }

            if (divisor_count == 4) {
                total_sum += divisor_sum;
            }
        }

        return total_sum;           
    }
};
