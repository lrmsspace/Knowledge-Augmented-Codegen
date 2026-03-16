// Source: https://leetcode.com/problems/number-of-different-subsequences-gcds/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums that consists of positive integers.
//
// The GCD of a sequence of numbers is defined as the greatest integer that divides all the numbers in the sequence evenly.
//
//
// 	For example, the GCD of the sequence [4,6,16] is 2.
//
//
// A subsequence of an array is a sequence that can be formed by removing some elements (possibly none) of the array.
//
//
// 	For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].
//
//
// Return the number of different GCDs among all non-empty subsequences of nums.
//
// Example:
// Input: nums = [6,10,3]
// Output: 5
// Explanation: The figure shows all the non-empty subsequences and their GCDs.
// The different GCDs are 6, 10, 3, 2, and 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 2 * 105
//
// Helpful references (internal KB):
// - Euler's totient function
//  (array, number, enumeration)
//   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
//   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
//   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
//   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
//   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Euler's totient function
//  (array, number, sieve, enumeration)
//   • When to use: Use when needing to count positive integers up to a given integer n that are relatively prime to n. It is also useful for problems involving modular arithmetic, group theory, and cryptographic applications.
//   • Idea: Euler's totient function, φ(n), counts the number of positive integers up to a given integer n that are relatively prime to n. It can be computed using prime factorization in O(sqrt(N)) or for a range using a sieve in O(N log log N).
//   • Invariants: For a sieve, phi[i] correctly stores the totient value for i after processing all its prime factors.; When factorizing n, n is continuously reduced by its smallest prime factor until it becomes 1.
//   • Tips: For a single n, find its prime factors and apply the product formula.; For computing φ(n) for all n up to a limit, use a sieve similar to Sieve of Eratosthenes.
//   • Pitfalls: Incorrectly handling repeated prime factors in the formula.; Integer overflow when calculating products for very large n.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countDifferentSubsequenceGCDs(int* nums, int numsSize) {
    int maxNum = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > maxNum) {
            maxNum = nums[i];
        }
    }

    int* count = (int*)calloc(maxNum + 1, sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }

    int result = 0;
    for (int gcd = 1; gcd <= maxNum; gcd++) {
        int currentGCD = 0;
        for (int multiple = gcd; multiple <= maxNum; multiple += gcd) {
            if (count[multiple] > 0) {
                if (currentGCD == 0) {
                    currentGCD = multiple;
                } else {
                    // Compute GCD of currentGCD and multiple
                    int a = currentGCD, b = multiple;
                    while (b != 0) {
                        int temp = b;
                        b = a % b;
                        a = temp;
                    }
                    currentGCD = a;
                }
            }
        }
        if (currentGCD == gcd) {
            result++;
        }
    }

    free(count);
    return result;      
}
