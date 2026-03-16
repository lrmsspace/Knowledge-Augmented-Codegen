// Source: https://leetcode.com/problems/minimum-increments-for-target-multiples-in-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given two arrays, nums and target.
//
// In a single operation, you may increment any element of nums by 1.
//
// Return the minimum number of operations required so that each element in target has at least one multiple in nums.
//
// Example:
// Input: nums = [1,2,3], target = [4]
//
// Output: 1
//
// Explanation:
//
// The minimum number of operations required to satisfy the condition is 1.
//
//
// 	Increment 3 to 4 with just one operation, making 4 a multiple of itself.
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	1 <= target.length <= 4
// 	target.length <= nums.length
// 	1 <= nums[i], target[i] <= 104
//
// Helpful references (internal KB):
// - Euler's totient function
//  (array, number, enumeration)
//   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
//   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
//   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
//   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
//   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when performing many range queries on a static array where the query operation is idempotent (e.g., min, max, GCD) to achieve O(1) query time after O(N log N) precomputation.
//   • Idea: A data structure that precomputes answers for all possible range queries of power-of-two lengths, allowing O(1) query time for idempotent operations like range minimum/maximum queries. Precomputation takes O(N log N) time and space.
//   • Invariants: The `st[k][i]` entry stores the result of the operation for the range `[i, i + 2^k - 1]`.; All ranges of length `2^k` starting at `i` are correctly computed in `st[k][i]` during precomputation.
//   • Tips: Precompute logarithms for O(1) lookup of `floor(log2(length))` during queries.; Sparse tables are most efficient for idempotent operations (min, max, GCD, OR, AND) due to overlapping segments.
//   • Pitfalls: Not suitable for dynamic arrays or scenarios requiring updates, as modifications invalidate the precomputed table.; High memory usage: requires O(N log N) space, which can be significant for large N.
// - Sqrt Decomposition (array, enumeration, prefix-sum)
//   • When to use: Use when frequent range queries and point/range updates are needed on an array, offering a balanced O(sqrt(N)) time complexity for both operations. It's a good alternative when a segment tree is too complex or overkill.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and updates. It achieves an O(sqrt(N)) time complexity for both query and update operations.
//   • Invariants: Each block maintains an up-to-date aggregate of its elements.; For any query, fully contained blocks are processed using their precomputed aggregates.
//   • Tips: Choose block size carefully, typically sqrt(N) for optimal balance.; Precompute block aggregates (sum, min, max) for efficient queries.
//   • Pitfalls: Incorrectly handling partial blocks or boundary conditions.; Off-by-one errors in block indices or element indices within blocks.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumIncrements(int* nums, int numsSize, int* target, int targetSize) {
    // Step 1: Find the maximum value in nums to determine the range for counting increments.
    int maxNum = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > maxNum) {
            maxNum = nums[i];
        }
    }

    // Step 2: Create a frequency array to count occurrences of each number in nums.
    int freq[10001] = {0}; // Assuming nums[i] <= 10000
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
    }

    // Step 3: Calculate the total increments needed for each target multiple.
    int increments = 0;
    for (int i = 0; i < targetSize; i++) {
        int t = target[i];
        int foundMultiple = 0;

        // Check multiples of t up to maxNum
        for (int multiple = t; multiple <= maxNum; multiple += t) {
            if (freq[multiple] > 0) {
                foundMultiple = 1;
                break;
            }
        }

        // If no multiple is found, we need to increment some number in nums to become a multiple of t
        if (!foundMultiple) {
            increments++;
            // Increment the smallest number in nums that can be incremented to become a multiple of t
            int incrementTarget = t;
            while (incrementTarget <= maxNum) {
                if (freq[incrementTarget] > 0) {
                    break;
                }
                incrementTarget += t;
            }
            if (incrementTarget > maxNum) {
                // If we exceed maxNum, we need to increment the largest number in nums
                increments += (t - (maxNum % t)) % t; // Increment to the next multiple of t
            }
        }
    }

    return increments;      
}
