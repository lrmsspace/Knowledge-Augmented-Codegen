// Source: https://leetcode.com/problems/prime-arrangements/   |   Difficulty: Easy
//
// Problem Description:
// Return the number of permutations of 1 to n so that prime numbers are at prime indices (1-indexed.)
//
// (Recall that an integer is prime if and only if it is greater than 1, and cannot be written as a product of two positive integers both smaller than it.)
//
// Since the answer may be large, return the answer modulo 10^9 + 7.
//
// Example:
// Input: n = 5
// Output: 12
// Explanation: For example [1,2,5,4,3] is a valid permutation, but [5,2,3,4,1] is not because the prime number 5 is at index 1.
//
// Constraints:
// 1 <= n <= 100
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, bitset, sieve)
//   • When to use: When you need to find all prime numbers up to a certain limit N, or efficiently check primality for many numbers within that range. It is ideal for precomputing primes.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer N by iteratively marking multiples of each prime. It achieves O(N log log N) time complexity and O(N) space.
//   • Invariants: For any number i less than the current prime p, is_prime[i] correctly reflects its primality.; All multiples of primes smaller than the current prime p have already been marked as composite.
//   • Tips: Optimize by starting marking multiples from p*p for each prime p.; Use a bitset for memory efficiency when N is large.
//   • Pitfalls: Forgetting to explicitly handle 0 and 1 as non-prime.; Incorrectly marking multiples, e.g., starting from 2*p instead of p*p.
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
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numPrimeArrangements(int n) {
    const int MOD = 1000000007;

    // Sieve of Eratosthenes to count primes up to n
    int is_prime[101];
    for (int i = 0; i <= n; i++) {
        is_prime[i] = 1; // Assume all numbers are prime initially
    }
    is_prime[0] = is_prime[1] = 0; // 0 and 1 are not prime numbers

    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = 0; // Mark multiples of i as non-prime
            }
        }
    }

    int prime_count = 0;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            prime_count++;
        }
    }

    int non_prime_count = n - prime_count;

    // Function to compute factorial modulo MOD
    long long factorial_mod(int x) {
        long long result = 1;
        for (int i = 2; i <= x; i++) {
            result = (result * i) % MOD;
        }
        return result;
    }

    long long prime_factorial = factorial_mod(prime_count);
    long long non_prime_factorial = factorial_mod(non_prime_count);

    return (prime_factorial * non_prime_factorial) % MOD;       
}
