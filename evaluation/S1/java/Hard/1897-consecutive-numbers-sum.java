// Source: https://leetcode.com/problems/consecutive-numbers-sum/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n, return the number of ways you can write n as the sum of consecutive positive integers.
//
// Example:
// Input: n = 5
// Output: 2
// Explanation: 5 = 2 + 3
//
// Constraints:
// 1 <= n <= 109
//
// Helpful references (internal KB):
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this approach when you need to calculate the total count or sum of all positive divisors for a given integer, typically by leveraging its prime factorization.
//   • Idea: The number of divisors d(n) and sum of divisors sigma(n) are arithmetic functions derived from the prime factorization of an integer n. Both can be computed efficiently by first finding prime factors and their exponents, resulting in an O(sqrt(N)) or O(log N) complexity with precomputed primes.
//   • Invariants: The current count of divisors is the product of (exponent + 1) for all prime factors found so far.; The current sum of divisors is the product of (1 + p + ... + p^e) for all prime factors found so far.
//   • Tips: Precompute primes using a sieve for efficiency when dealing with multiple queries or large numbers.; For sum of divisors, the formula is sigma(n) = product((1 + p_i + ... + p_i^e_i)) for each prime factor p_i^e_i.
//   • Pitfalls: Forgetting to handle n=1 correctly, which has one divisor.; Integer overflow when calculating sums or products of large powers, especially for sum of divisors.
// - Stars and bars (number, counting)
//   • When to use: Use when counting the number of ways to distribute identical items into distinct bins, or finding the number of non-negative or positive integer solutions to a linear equation of sums.
//   • Idea: A combinatorial technique to count the number of ways to distribute 'n' identical items into 'k' distinct bins, or find integer solutions to x1 + ... + xk = n.
//   • Invariants: The total number of 'stars' (items) remains constant throughout the distribution.; The number of 'bars' (dividers, k-1) remains constant, separating the k distinct bins.
//   • Tips: Distinguish between non-negative (xi >= 0) and positive (xi >= 1) integer solutions; the latter requires a variable transformation.; For positive integer solutions (xi >= 1), transform variables to yi = xi - 1, then solve for yi >= 0 with a reduced sum.
//   • Pitfalls: Confusing identical items/distinct bins with distinct items/distinct bins (which is k^n).; Incorrectly applying the formula for positive vs. non-negative constraints without transformation.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int consecutiveNumbersSum(int n) {
        int count = 0;
        // A number can be expressed as a sum of consecutive numbers
        // if and only if it has an odd divisor.
        // Thus, we need to count the number of odd divisors of n.
        for (int k = 1; k * k <= n; k++) {
            if (n % k == 0) {
                // k is a divisor
                if (k % 2 == 1) {
                    count++;
                }
                int otherDivisor = n / k;
                if (otherDivisor != k && otherDivisor % 2 == 1) {
                    count++;
                }
            }
        }
        return count;           
    }
}
