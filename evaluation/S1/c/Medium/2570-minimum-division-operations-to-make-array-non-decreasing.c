// Source: https://leetcode.com/problems/minimum-division-operations-to-make-array-non-decreasing/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
// Any positive divisor of a natural number x that is strictly less than x is called a proper divisor of x. For example, 2 is a proper divisor of 4, while 6 is not a proper divisor of 6.
//
// You are allowed to perform an operation any number of times on nums, where in each operation you select any one element from nums and divide it by its greatest proper divisor.
//
// Return the minimum number of operations required to make the array non-decreasing.
//
// If it is not possible to make the array non-decreasing using any number of operations, return -1.
//
// Example:
// Input: nums = [25,7]
//
// Output: 1
//
// Explanation:
//
// Using a single operation, 25 gets divided by 5 and nums becomes [5, 7].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//
// Helpful references (internal KB):
// - Linear Sieve (array, sieve)
//   • When to use: Use when you need to find the smallest prime factor or full prime factorization for all numbers up to a given limit N in linear time. It's particularly useful for tasks requiring precomputed factorizations.
//   • Idea: The Linear Sieve computes the smallest prime factor for every number up to N, ensuring each composite number is marked exactly once by its smallest prime factor. It achieves this in O(N) time complexity.
//   • Invariants: Every number `i` from 2 to N has its `lp[i]` correctly set to its smallest prime factor.; The `primes` array contains all prime numbers less than or equal to the current iteration `i`.
//   • Tips: Stores the smallest prime factor (lp) for each number.; Efficiently generates all prime numbers up to N.
//   • Pitfalls: Higher memory usage compared to the classic Sieve of Eratosthenes due to storing lp array.; Can be slower in practice than optimized Sieve of Eratosthenes for merely generating primes.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
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

int minOperations(int* nums, int numsSize) {
    // Precompute smallest prime factors using Linear Sieve
    int maxNum = 1000000;
    int lp[maxNum + 1];
    int primes[maxNum / 10]; // Rough estimate of number of primes
    int primeCount = 0;

    for (int i = 2; i <= maxNum; i++) {
        lp[i] = 0;
    }

    for (int i = 2; i <= maxNum; i++) {
        if (lp[i] == 0) {
            lp[i] = i;
            primes[primeCount++] = i;
        }
        for (int j = 0; j < primeCount && primes[j] <= lp[i] && i * primes[j] <= maxNum; j++) {
            lp[i * primes[j]] = primes[j];
        }
    }

    int operations = 0;
    int prev = nums[numsSize - 1];

    for (int i = numsSize - 2; i >= 0; i--) {
        int current = nums[i];
        if (current <= prev) {
            prev = current;
            continue;
        }

        int minOpsForCurrent = -1;
        int tempCurrent = current;
        int opsCount = 0;

        while (tempCurrent > 0) {
            if (tempCurrent <= prev) {
                if (minOpsForCurrent == -1 || opsCount < minOpsForCurrent) {
                    minOpsForCurrent = opsCount;
                }
            }
            if (tempCurrent == 1) break;

            // Divide by greatest proper divisor
            int spf = lp[tempCurrent];
            tempCurrent /= spf;
            opsCount++;
        }

        if (minOpsForCurrent == -1) {
            return -1;
        }

        operations += minOpsForCurrent;
        prev = current;

        // Update prev to the largest value <= prev after operations
        tempCurrent = current;
        opsCount = 0;

        while (tempCurrent > 0) {
            if (tempCurrent <= prev) {
                prev = tempCurrent;
                break;
            }
            if (tempCurrent == 1) break;

            int spf = lp[tempCurrent];
            tempCurrent /= spf;
            opsCount++;
        }
    }

    return operations;      
}
