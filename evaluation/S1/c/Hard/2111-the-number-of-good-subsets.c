// Source: https://leetcode.com/problems/the-number-of-good-subsets/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. We call a subset of nums good if its product can be represented as a product of one or more distinct prime numbers.
//
//
// 	For example, if nums = [1, 2, 3, 4]:
//
// 	
// 		[2, 3], [1, 2, 3], and [1, 3] are good subsets with products 6 = 2*3, 6 = 2*3, and 3 = 3 respectively.
// 		[1, 4] and [4] are not good subsets with products 4 = 2*2 and 4 = 2*2 respectively.
// 	
// 	
//
//
// Return the number of different good subsets in nums modulo 109 + 7.
//
// A subset of nums is any array that can be obtained by deleting some (possibly none or all) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 6
// Explanation: The good subsets are:
// - [1,2]: product is 2, which is the product of distinct prime 2.
// - [1,2,3]: product is 6, which is the product of distinct primes 2 and 3.
// - [1,3]: product is 3, which is the product of distinct prime 3.
// - [2]: product is 2, which is the product of distinct prime 2.
// - [2,3]: product is 6, which is the product of distinct primes 2 and 3.
// - [3]: product is 3, which is the product of distinct prime 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 30
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, sieve, enumeration)
//   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
//   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
//   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
//   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Binomial Coefficients (array, number, dp-1d, mod-exp)
//   • When to use: Use when calculating binomial coefficients C(n, k) modulo a composite number M, especially when M is not prime and direct modular inverse computation for factorials is not possible.
//   • Idea: This technique computes binomial coefficients modulo an arbitrary composite number M by factoring M into prime powers. For each prime power, it calculates prime exponents in factorials and combines coprime parts, then uses Chinese Remainder Theorem.
//   • Invariants: For any `i <= N`, `c[i]` correctly stores the exponent of prime `p` in `i!`.; For any `i <= N`, `g[i]` correctly stores `(i! / p^c[i]) % (p^b)`.
//   • Tips: Precompute factorials and their prime exponents up to N using dynamic programming.; Apply Legendre's formula to efficiently find the exponent of a prime 'p' in 'x!'.
//   • Pitfalls: Failing to correctly factorize the modulus 'M' into its prime power components.; Incorrectly computing modular inverses when a number is not coprime to the modulus.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int numberOfGoodSubsets(int* nums, int numsSize) {
    const int MOD = 1000000007;
    int primeList[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    int primeCount = sizeof(primeList) / sizeof(primeList[0]);
    
    // Precompute frequency of each number in nums
    int freq[31] = {0};
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
    }
    
    // Precompute valid masks for numbers 2 to 30
    int validMasks[31] = {0};
    for (int num = 2; num <= 30; num++) {
        int mask = 0;
        int temp = num;
        int isValid = 1;
        for (int j = 0; j < primeCount; j++) {
            int prime = primeList[j];
            int count = 0;
            while (temp % prime == 0) {
                temp /= prime;
                count++;
            }
            if (count > 1) {
                isValid = 0; // Not square-free
                break;
            }
            if (count == 1) {
                mask |= (1 << j);
            }
        }
        if (isValid && temp == 1) {
            validMasks[num] = mask;
        } else {
            validMasks[num] = -1; // Invalid number
        }
    }
    
    // DP array to count subsets
    int dp[1 << primeCount];
    for (int i = 0; i < (1 << primeCount); i++) {
        dp[i] = 0;
    }
    dp[0] = 1; // Empty subset
    
    // Process each number from 2 to 30
    for (int num = 2; num <= 30; num++) {
        if (freq[num] == 0 || validMasks[num] == -1) continue;
        int currMask = validMasks[num];
        
        // Update DP array in reverse order
        for (int mask = (1 << primeCount) - 1; mask >= 0; mask--) {
            if ((mask & currMask) == 0) {
                int newMask = mask | currMask;
                dp[newMask] = (dp[newMask] + (long long)dp[mask] * freq[num]) % MOD;
            }
        }
        if (freq[1] > 0) {
            // Each occurrence of 1 can double the subsets
            for (int i = 0; i < freq[1]; i++) {
                for (int mask = (1 << primeCount) - 1; mask >= 0; mask--) {
                    dp[mask] = (dp[mask] * 2) % MOD;
                }
            }
        }
    }
    // Sum all non-empty subsets
    int result = 0;
    for (int mask = 1; mask < (1 << primeCount); mask++) {
        result = (result + dp[mask]) % MOD;
    }               
    return result;
}
