// Source: https://leetcode.com/problems/count-the-number-of-square-free-subsets/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer 0-indexed array nums.
//
// A subset of the array nums is square-free if the product of its elements is a square-free integer.
//
// A square-free integer is an integer that is divisible by no square number other than 1.
//
// Return the number of square-free non-empty subsets of the array nums. Since the answer may be too large, return it modulo 109 + 7.
//
// A non-empty subset of nums is an array that can be obtained by deleting some (possibly none but not all) elements from nums. Two subsets are different if and only if the chosen indices to delete are different.
//
// Example:
// Input: nums = [3,4,4,5]
// Output: 3
// Explanation: There are 3 square-free subsets in this example:
// - The subset consisting of the 0th element [3]. The product of its elements is 3, which is a square-free integer.
// - The subset consisting of the 3rd element [5]. The product of its elements is 5, which is a square-free integer.
// - The subset consisting of 0th and 3rd elements [3,5]. The product of its elements is 15, which is a square-free integer.
// It can be proven that there are no more than 3 square-free subsets in the given array.
//
// Constraints:
// 1 <= nums.length <= 1000
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
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int squareFreeSubsets(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        const int MAX_NUM = 30;
        const int PRIME_COUNT = 10;
        const int primes[PRIME_COUNT] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

        // Precompute the bitmask for each number indicating which primes divide it
        int numMask[MAX_NUM + 1] = {0};
        for (int num = 2; num <= MAX_NUM; ++num) {
            int mask = 0;
            int temp = num;
            bool isSquareFree = true;
            for (int i = 0; i < PRIME_COUNT; ++i) {
                int prime = primes[i];
                int count = 0;
                while (temp % prime == 0) {
                    temp /= prime;
                    count++;
                }
                if (count > 1) {
                    isSquareFree = false;
                    break;
                }
                if (count == 1) {
                    mask |= (1 << i);
                }
            }
            if (isSquareFree) {
                numMask[num] = mask;
            } else {
                numMask[num] = -1; // Mark non-square-free numbers
            }
        }

        // DP array to count subsets
        int dp[1 << PRIME_COUNT] = {0};
        dp[0] = 1; // Empty subset

        for (int num : nums) {
            int mask = numMask[num];
            if (mask == -1) continue; // Skip non-square-free numbers

            // Update dp array in reverse to avoid overwriting
            for (int submask = (1 << PRIME_COUNT) - 1; submask >= 0; --submask) {
                if ((submask & mask) == 0) { // No common prime factors
                    dp[submask | mask] = (dp[submask | mask] + dp[submask]) % MOD;
                }
            }
        }

        // Sum all non-empty subsets
        int result = 0;
        for (int i = 1; i < (1 << PRIME_COUNT); ++i) {
            result = (result + dp[i]) % MOD;
        }

        return result;          
    }
};
