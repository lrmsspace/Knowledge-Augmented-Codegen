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
// - Euler's totient function
//  (array, number, enumeration)
//   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
//   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
//   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
//   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
//   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
// - Integer factorization (number, array, enumeration, sieve, counting)
//   • When to use: Use when needing to find the prime factors of a composite number, especially for relatively small numbers or as a base case for more advanced algorithms.
//   • Idea: This algorithm finds the prime factorization of an integer by iteratively dividing it by its smallest prime factors. It typically checks divisors up to the square root of the number, achieving an O(sqrt(N)) time complexity.
//   • Invariants: The product of all found prime factors multiplied by the current remaining number equals the original input number.; All prime factors found so far are less than or equal to the current divisor being tested.
//   • Tips: Perform a primality test first to avoid unnecessary factorization attempts.; Only check divisors up to the square root of the number.
//   • Pitfalls: Trial division is pseudo-polynomial time, making it inefficient for very large numbers.; Forgetting to handle the case where the remaining number after division is itself a prime greater than its original square root.
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
    const maxN = Math.max(...queries.map(q => q[0]));
    const maxK = Math.max(...queries.map(q => q[1]));
        
    // Step 1: Precompute factorials and inverse factorials for combinations
    const fact = new Array(maxN + maxK).fill(1);
    const invFact = new Array(maxN + maxK).fill(1);
    for (let i = 2; i <= maxN + maxK; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    invFact[maxN + maxK] = modInverse(fact[maxN + maxK], MOD);
    for (let i = maxN + maxK - 1; i >= 0; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }

    // Step 2: Function to compute nCr % MOD
    function nCr(n, r) {
        if (r > n || r < 0) return 0;
        return (fact[n] * invFact[r] % MOD) * invFact[n - r] % MOD;
    }

    // Step 3: Function to compute modular inverse using Fermat's Little Theorem
    function modInverse(a, m) {
        let m0 = m, x0 = 0, x1 = 1;
        if (m === 1) return 0;
        while (a > 1) {
            let q = Math.floor(a / m);
            [a, m] = [m, a % m];
            [x0, x1] = [x1 - q * x0, x0];
        }
        if (x1 < 0) x1 += m0;
        return x1;
    }
    
    // Step 4: Process each query
    const result = [];
    for (const [n, k] of queries) {
        let ways = 0;
        // For each possible number of distinct prime factors (i), compute the number of ways to distribute k items among n positions with i distinct prime factors
        for (let i = 1; i <= Math.min(n, k); i++) {
            ways = (ways + nCr(n, i) * nCr(k - 1, i - 1)) % MOD;
        }
        result.push(ways);
    }
    return result;
        
};