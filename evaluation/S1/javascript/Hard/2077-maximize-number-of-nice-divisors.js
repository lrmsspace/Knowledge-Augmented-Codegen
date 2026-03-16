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
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} primeFactors
 * @return {number}
 */
var maxNiceDivisors = function(primeFactors) {
    const mod = 1e9 + 7;

    if (primeFactors <= 3) return primeFactors;

    let quotient = Math.floor(primeFactors / 3);
    let remainder = primeFactors % 3;

    if (remainder === 0) {
        return modExp(3, quotient, mod);
    } else if (remainder === 1) {
        return (modExp(3, quotient - 1, mod) * 4) % mod;
    } else {
        return (modExp(3, quotient, mod) * 2) % mod;
    }
};
