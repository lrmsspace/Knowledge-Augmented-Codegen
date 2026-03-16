// Source: https://leetcode.com/problems/maximize-number-of-nice-divisors/   |   Difficulty: Hard
//
// Problem Description:
// You are given a positive integer primeFactors. You are asked to construct a positive integer n that satisfies the following conditions:
//
//
//   The number of prime factors of n (not necessarily distinct) is at most primeFactors.
//   The number of nice divisors of n is maximized. Note that a divisor of n is nice if it is divisible by every prime factor of n. For example, if n = 12, then its prime factors are [2,2,3], then 6 and 12 are nice divisors, while 3 and 4 are not.
//
//
// Return the number of nice divisors of n. Since that number can be too large, return it modulo 109 + 7.
//
// Note that a prime number is a natural number greater than 1 that is not a product of two smaller natural numbers. The prime factors of a number n is a list of prime numbers such that their product equals n.
//
// Example:
// Input: primeFactors = 5
// Output: 6
// Explanation: 200 is a valid value of n.
// It has 5 prime factors: [2,2,2,5,5], and it has 6 nice divisors: [10,20,40,50,100,200].
// There is not other value of n that has at most 5 prime factors and more nice divisors.
//
// Constraints:
// 1 <= primeFactors <= 109
//
// Helpful references (internal KB):
// - Factorial modulo 
// p (number, counting)
//   • When to use: Use this when calculating factorials or expressions involving factorials in fractions modulo a prime `p`, especially when `p` is small and factors of `p` need to be explicitly handled for cancellation.
//   • Idea: This technique computes `n! mod p` by separating the factors of `p` from the remaining product, allowing for correct modular division in expressions like binomial coefficients.
//   • Invariants: The running product `P` always holds the value of `(i-1)!` with all factors of `p` removed, modulo `p`.; The variable `count_p` accurately stores the total exponent of `p` in `(i-1)!`.
//   • Tips: Precompute factorials and inverse factorials modulo `p` for terms not divisible by `p`.; Use Fermat's Little Theorem to find modular inverses when `p` is prime.
//   • Pitfalls: Incorrectly applying modular inverse when the divisor is a multiple of `p` or `p` is not prime.; Forgetting to handle the exponent of `p` separately, which can lead to an incorrect zero result.
// - Primality tests (number, mod-exp, randomized, probability-statistics)
//   • When to use: To efficiently determine if a large number is prime or composite with a high probability, especially when deterministic primality tests are too slow. It's suitable for cryptographic applications or number theory problems.
//   • Idea: Primality tests, like Fermat's and Miller-Rabin, use properties of modular arithmetic to probabilistically determine if a given number is prime. They offer a fast, polynomial-time approach, often relying on modular exponentiation.
//   • Invariants: The number $N$ being tested for primality remains constant throughout the algorithm.; For each chosen base $a$, the modular exponentiation $a^E \pmod N$ is computed correctly.
//   • Tips: Use modular exponentiation (binary exponentiation) for efficient calculation of $a^E \pmod N$.; Repeat the test with multiple distinct random bases to significantly increase the confidence level.
//   • Pitfalls: Fermat's test can yield false positives for Carmichael numbers, which are composite but pass the test for many bases.; A single 'probably prime' result from a probabilistic test is not a definitive proof of primality.
// - Linear Diophantine Equation (number, greedy)
//   • When to use: Use when a problem can be solved by making the locally optimal choice at each step, hoping this leads to a globally optimal solution. This strategy is often simpler and faster than dynamic programming.
//   • Idea: The greedy algorithm makes the best choice at each stage with the hope of finding a global optimum, without reconsidering previous choices. Its time complexity is typically O(N log N) or O(N).
//   • Invariants: At each step, the chosen element is the best available according to the greedy criterion.; The partial solution constructed so far remains optimal for the subproblem considered.
//   • Tips: Prove correctness by exchange argument or induction.; Sort input data if it helps identify the greedy choice.
//   • Pitfalls: Failing to prove the greedy choice property.; Making a locally optimal choice that prevents a global optimum.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maxNiceDivisors(int primeFactors) {
        long MOD = 1_000_000_007;
        if (primeFactors <= 3) {
            return primeFactors;
        }
        long result = 1;
        if (primeFactors % 3 == 0) {
            while (primeFactors > 0) {
                result = (result * 3) % MOD;
                primeFactors -= 3;
            }
        } else if (primeFactors % 3 == 1) {
            while (primeFactors > 4) {
                result = (result * 3) % MOD;
                primeFactors -= 3;
            }
            result = (result * 4) % MOD;
        } else { // primeFactors % 3 == 2
            while (primeFactors > 2) {
                result = (result * 3) % MOD;
                primeFactors -= 3;
            }
            result = (result * 2) % MOD;
        }
        return (int) result;            
    }
}
