// Source: https://leetcode.com/problems/special-permutations/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums containing n distinct positive integers. A permutation of nums is called special if:
//
//
// 	For all indexes 0 <= i < n - 1, either nums[i] % nums[i+1] == 0 or nums[i+1] % nums[i] == 0.
//
//
// Return the total number of special permutations. As the answer could be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [2,3,6]
// Output: 2
// Explanation: [3,6,2] and [2,6,3] are the two special permutations of nums.
//
// Constraints:
// 2 <= nums.length <= 14
// 	1 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Binomial Coefficients (array, number, dp-1d, mod-exp)
//   • When to use: Use when calculating binomial coefficients C(n, k) modulo a composite number M, especially when M is not prime and direct modular inverse computation for factorials is not possible.
//   • Idea: This technique computes binomial coefficients modulo an arbitrary composite number M by factoring M into prime powers. For each prime power, it calculates prime exponents in factorials and combines coprime parts, then uses Chinese Remainder Theorem.
//   • Invariants: For any `i <= N`, `c[i]` correctly stores the exponent of prime `p` in `i!`.; For any `i <= N`, `g[i]` correctly stores `(i! / p^c[i]) % (p^b)`.
//   • Tips: Precompute factorials and their prime exponents up to N using dynamic programming.; Apply Legendre's formula to efficiently find the exponent of a prime 'p' in 'x!'.
//   • Pitfalls: Failing to correctly factorize the modulus 'M' into its prime power components.; Incorrectly computing modular inverses when a number is not coprime to the modulus.
// - Euler's totient function
//  (array, number, sieve, enumeration)
//   • When to use: Use when needing to count positive integers up to a given integer n that are relatively prime to n. It is also useful for problems involving modular arithmetic, group theory, and cryptographic applications.
//   • Idea: Euler's totient function, φ(n), counts the number of positive integers up to a given integer n that are relatively prime to n. It can be computed using prime factorization in O(sqrt(N)) or for a range using a sieve in O(N log log N).
//   • Invariants: For a sieve, phi[i] correctly stores the totient value for i after processing all its prime factors.; When factorizing n, n is continuously reduced by its smallest prime factor until it becomes 1.
//   • Tips: For a single n, find its prime factors and apply the product formula.; For computing φ(n) for all n up to a limit, use a sieve similar to Sieve of Eratosthenes.
//   • Pitfalls: Incorrectly handling repeated prime factors in the formula.; Integer overflow when calculating products for very large n.
// - Lattice points inside non-lattice polygon (number, recursion, counting, gcd)
//   • When to use: Use when counting pairs or elements satisfying divisibility or GCD conditions. Also applicable for summing functions over pairs using number theory properties.
//   • Idea: This approach leverages number theoretic properties like GCD, LCM, and prime factorization to efficiently count elements or pairs satisfying specific criteria. It often involves iterating through divisors or multiples, achieving complexities like O(N log N) or O(sqrt N) per query.
//   • Invariants: All numbers processed so far have their relevant number-theoretic properties (e.g., prime factors, divisors) correctly determined.; The current count or sum accurately reflects all valid combinations found up to the current iteration.
//   • Tips: Precompute primes or divisors using a sieve for efficiency.; Utilize properties of GCD and LCM, such as gcd(a,b) * lcm(a,b) = a * b.
//   • Pitfalls: Overcounting or undercounting when using inclusion-exclusion.; Integer overflow with large products or sums.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int specialPerm(int* nums, int numsSize) {
    int mod = 1000000007;
    int graph[14][14];
    int dp[1 << 14][14];
    
    // Build the graph based on divisibility conditions
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < numsSize; j++) {
            graph[i][j] = (nums[i] % nums[j] == 0 || nums[j] % nums[i] == 0) ? 1 : 0;
        }
    }
    
    // Initialize dp for single element permutations
    for (int i = 0; i < numsSize; i++) {
        dp[1 << i][i] = 1;
    }
    
    // Fill the dp table
    for (int mask = 1; mask < (1 << numsSize); mask++) {
        for (int last = 0; last < numsSize; last++) {
            if ((mask & (1 << last)) == 0) continue; // last must be in the current subset
            
            for (int next = 0; next < numsSize; next++) {
                if ((mask & (1 << next)) != 0) continue; // next must not be in the current subset
                if (graph[last][next]) {
                    dp[mask | (1 << next)][next] = (dp[mask | (1 << next)][next] + dp[mask][last]) % mod;
                }
            }
        }
    }
    
    // Sum up all valid permutations of size numsSize
    int result = 0;
    for (int i = 0; i < numsSize; i++) {
        result = (result + dp[(1 << numsSize) - 1][i]) % mod;
    }
    
    return result;      
}
