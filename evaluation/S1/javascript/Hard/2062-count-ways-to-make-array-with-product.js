// Source: https://leetcode.com/problems/count-ways-to-make-array-with-product/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array, queries. For each queries[i], where queries[i] = [ni, ki], find the number of different ways you can place positive integers into an array of size ni such that the product of the integers is ki. As the number of ways may be too large, the answer to the ith query is the number of ways modulo 109 + 7.
//
// Return an integer array answer where answer.length == queries.length, and answer[i] is the answer to the ith query.
//
// Example:
// Input: queries = [[2,6],[5,1],[73,660]]
// Output: [4,1,50734910]
// Explanation: Each query is independent.
// [2,6]: There are 4 ways to fill an array of size 2 that multiply to 6: [1,6], [2,3], [3,2], [6,1].
// [5,1]: There is 1 way to fill an array of size 5 that multiply to 1: [1,1,1,1,1].
// [73,660]: There are 1050734917 ways to fill an array of size 73 that multiply to 660. 1050734917 modulo 109 + 7 = 50734910.
//
// Constraints:
// 1 <= queries.length <= 104 
// 	1 <= ni, ki <= 104
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this approach when you need to calculate the total count or sum of all positive divisors for a given integer, typically by leveraging its prime factorization.
//   • Idea: The number of divisors d(n) and sum of divisors sigma(n) are arithmetic functions derived from the prime factorization of an integer n. Both can be computed efficiently by first finding prime factors and their exponents, resulting in an O(sqrt(N)) or O(log N) complexity with precomputed primes.
//   • Invariants: The current count of divisors is the product of (exponent + 1) for all prime factors found so far.; The current sum of divisors is the product of (1 + p + ... + p^e) for all prime factors found so far.
//   • Tips: Precompute primes using a sieve for efficiency when dealing with multiple queries or large numbers.; For sum of divisors, the formula is sigma(n) = product((1 + p_i + ... + p_i^e_i)) for each prime factor p_i^e_i.
//   • Pitfalls: Forgetting to handle n=1 correctly, which has one divisor.; Integer overflow when calculating sums or products of large powers, especially for sum of divisors.
// - Binomial Coefficients (array, number, mod-exp, enumeration)
//   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
//   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
//   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
//   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
//   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} queries
 * @return {number[]}
 */
var waysToFillArray = function(queries) {
    const MOD = 1e9 + 7;
    const MAXN = 10000;

    // Step 1: Sieve of Eratosthenes to find primes up to MAXN
    const sieve = new Array(MAXN + 1).fill(true);
    sieve[0] = sieve[1] = false;
    for (let i = 2; i * i <= MAXN; i++) {
        if (sieve[i]) {
            for (let j = i * i; j <= MAXN; j += i) {
                sieve[j] = false;
            }
        }
    }
    const primes = [];
    for (let i = 2; i <= MAXN; i++) {
        if (sieve[i]) primes.push(i);
    }

    // Step 2: Precompute factorials and inverse factorials for binomial coefficients
    const fact = new Array(MAXN + 1).fill(1);
    for (let i = 2; i <= MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    const invFact = new Array(MAXN + 1).fill(1);
    invFact[MAXN] = modInverse(fact[MAXN], MOD);
    for (let i = MAXN - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }

    const nCr = (n, r) => {
        if (r > n || r < 0) return 0;
        return ((fact[n] * invFact[r]) % MOD * invFact[n - r]) % MOD;
    };

    const results = [];
    for (const [n, k] of queries) {
        let ways = 1;
        let tempK = k;

        for (const prime of primes) {
            if (prime > tempK) break;
            let count = 0;
            while (tempK % prime === 0) {
                tempK /= prime;
                count++;
            }
            if (count > 0) {
                ways = (ways * nCr(count + n - 1, count)) % MOD;
            }
        }
        if (tempK > 1) {
            ways = (ways * nCr(1 + n - 1, 1)) % MOD; // For the remaining prime factor
        }
        results.push(ways);
    }
    return results;

    function modInverse(a, m) { 
        let m0 = m, t, q;
        let x0 = 0, x1 = 1;
        if (m === 1) return 0;
        while (a > 1) {
            q = Math.floor(a / m);
            t = m;
            m = a % m; a = t;
            t = x0;
            x0 = x1 - q * x0;
            x1 = t;
        }
        if (x1 < 0) x1 += m0;
        return x1;
    }
    
};
