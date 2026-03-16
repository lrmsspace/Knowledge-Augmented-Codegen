// Source: https://leetcode.com/problems/count-the-number-of-good-partitions/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array nums consisting of positive integers.
//
// A partition of an array into one or more contiguous subarrays is called good if no two subarrays contain the same number.
//
// Return the total number of good partitions of nums.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 8
// Explanation: The 8 possible good partitions are: ([1], [2], [3], [4]), ([1], [2], [3,4]), ([1], [2,3], [4]), ([1], [2,3,4]), ([1,2], [3], [4]), ([1,2], [3,4]), ([1,2,3], [4]), and ([1,2,3,4]).
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Binomial Coefficients (array, number, mod-exp, enumeration)
//   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
//   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
//   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
//   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
//   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
// - String Hashing (string, number, hashing)
//   • When to use: Use when needing to efficiently compare strings or substrings, especially in scenarios involving large texts or numerous comparisons. It's also useful for pattern matching and detecting duplicates in collections of strings.
//   • Idea: String hashing converts a string into a numerical value (hash) to enable fast comparisons and lookups. This technique typically uses polynomial hashing with a base and a modulus, offering O(L) for initial hash computation and O(1) for substring hashes after O(N) precomputation.
//   • Invariants: The hash of a string S of length L is (S[0]*P^(L-1) + S[1]*P^(L-2) + ... + S[L-1]*P^0) % M.; For any substring S[i...j], its hash can be derived from precomputed prefix hashes in O(1) time.
//   • Tips: Use multiple hash functions with different bases and moduli to reduce collision probability.; Choose a large prime modulus (e.g., 10^9 + 7) and a random base for robustness.
//   • Pitfalls: Hash collisions are possible; always verify equality for critical applications or use multiple hashes.; Choosing a small or non-prime modulus significantly increases the risk of collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int numberOfGoodPartitions(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        unordered_set<int> seen;
        long long totalWays = 1; // Start with one way to partition (the whole array)
        long long currentWays = 1; // Ways to partition up to the current position
        int lastDuplicateIndex = -1; // Last index where a duplicate was found

        for (int i = 0; i < n; ++i) {
            if (seen.count(nums[i])) {
                // If we see a duplicate, we need to update the number of ways
                lastDuplicateIndex = i;
                currentWays = totalWays; // Reset current ways to total ways before this duplicate
            }
            seen.insert(nums[i]);
            totalWays = (totalWays + currentWays) % MOD; // Update total ways
        }

        // Subtract 1 to exclude the case where the entire array is one partition
        return (totalWays - 1 + MOD) % MOD;         
    }
};
