// Source: https://leetcode.com/problems/count-partitions-with-even-sum-difference/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums of length n.
//
// A partition is defined as an index i where 0 <= i < n - 1, splitting the array into two non-empty subarrays such that:
//
//
// 	Left subarray contains indices [0, i].
// 	Right subarray contains indices [i + 1, n - 1].
//
//
// Return the number of partitions where the difference between the sum of the left and right subarrays is even.
//
// Example:
// Input: nums = [10,10,3,7,6]
//
// Output: 4
//
// Explanation:
//
// The 4 partitions are:
//
//
// 	[10], [10, 3, 7, 6] with a sum difference of 10 - 26 = -16, which is even.
// 	[10, 10], [3, 7, 6] with a sum difference of 20 - 16 = 4, which is even.
// 	[10, 10, 3], [7, 6] with a sum difference of 23 - 13 = 10, which is even.
// 	[10, 10, 3, 7], [6] with a sum difference of 30 - 6 = 24, which is even.
//
// Constraints:
// 2 <= n == nums.length <= 100
// 	1 <= nums[i] <= 100
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - The Inclusion-Exclusion Principle (number, counting)
//   • When to use: Used for counting elements that satisfy a specific number of conditions (exactly k, at least k) from a larger set of conditions. It is particularly effective when direct counting with overlapping properties is complex.
//   • Idea: The Inclusion-Exclusion Principle is a combinatorial technique to count the size of a union of sets by summing the sizes of individual sets, then adjusting for intersections. For problems involving 'k' conditions, optimized versions can achieve O(2^N * N) complexity, where N is the total number of conditions.
//   • Invariants: The current sum correctly reflects the inclusion-exclusion contribution for all processed subsets of conditions.; Each f(Y) term accurately represents the count of elements satisfying at least all conditions in Y.
//   • Tips: Clearly define the sets and conditions involved in the problem.; Remember the alternating signs for sums of intersections.
//   • Pitfalls: Incorrectly applying the alternating signs in the summation.; Miscalculating the sizes of intersections (f(Y) terms).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countPartitions(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        
        // If total sum is odd, no partitions with even difference
        if (totalSum % 2 != 0) {
            return 0;
        }
        
        int target = totalSum / 2;
        
        // DP array to count subsets with sum equal to target
        vector<int> dp(target + 1, 0);
        dp[0] = 1;  // There's one way to make sum 0 (empty subset)
        
        for (int num : nums) {
            for (int j = target; j >= num; --j) {
                dp[j] = (dp[j] + dp[j - num]) % MOD;
            }
        }
        
        return dp[target];          
    }
};
