// Source: https://leetcode.com/problems/maximum-sum-with-exactly-k-elements/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer k. Your task is to perform the following operation exactly k times in order to maximize your score:
//
//
// 	Select an element m from nums.
// 	Remove the selected element m from the array.
// 	Add a new element with a value of m + 1 to the array.
// 	Increase your score by m.
//
//
// Return the maximum score you can achieve after performing the operation exactly k times.
//
// Example:
// Input: nums = [1,2,3,4,5], k = 3
// Output: 18
// Explanation: We need to choose exactly 3 elements from nums to maximize the sum.
// For the first iteration, we choose 5. Then sum is 5 and nums = [1,2,3,4,6]
// For the second iteration, we choose 6. Then sum is 5 + 6 and nums = [1,2,3,4,7]
// For the third iteration, we choose 7. Then sum is 5 + 6 + 7 = 18 and nums = [1,2,3,4,8]
// So, we will return 18.
// It can be proven, that 18 is the maximum answer that we can achieve.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
// 	1 <= k <= 100
//
//
//  
// .spoilerbutton {display:block; border:dashed; padding: 0px 0px; margin:10px 0px; font-size:150%; font-weight: bold; color:#000000; background-color:cyan; outline:0; 
// }
// .spoiler {overflow:hidden;}
// .spoiler > div {-webkit-transition: all 0s ease;-moz-transition: margin 0s ease;-o-transition: all 0s ease;transition: margin 0s ease;}
// .spoilerbutton[value="Show Message"] + .spoiler > div {margin-top:-500%;}
// .spoilerbutton[value="Hide Message"] + .spoiler {padding:5px;}
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Knapsack Problem (array, knapsack, dp-1d, dp-2d)
//   • When to use: Use when selecting items, each with a weight and value, to maximize total value within a limited capacity, where each item can be chosen multiple times. It is suitable for problems exhibiting optimal substructure and overlapping subproblems.
//   • Idea: The Knapsack Problem involves selecting items to maximize total value within a fixed capacity. The complete knapsack variant, where items can be taken multiple times, is typically solved using dynamic programming in O(nW) time and O(W) space.
//   • Invariants: For 2D DP `f[i][j]`, it represents the maximum value obtainable using only the first `i` items with a total weight not exceeding `j`.; For 1D DP `dp[j]`, after processing item `i`, it stores the maximum value obtainable with a total weight not exceeding `j`, considering all items up to `i`.
//   • Tips: For the complete knapsack, iterate capacity `j` forwards (from `w_i` to `W`) when using 1D DP to allow multiple selections of the current item.; The 1D DP array `dp[j]` stores the maximum value achievable for exactly capacity `j`.
//   • Pitfalls: Confusing 0-1 knapsack with complete knapsack, especially in the 1D DP iteration direction for capacity.; Incorrectly initializing the DP array, leading to incorrect base cases or propagation.
// - Sqrt Tree (array, tree, divide-and-conquer, recursion, prefix-sum)
//   • When to use: When performing associative range queries on an array, especially when O(1) query time is critical and O(N log log N) preprocessing is acceptable.
//   • Idea: The Sqrt Tree is a data structure that answers associative range queries on an array in O(1) time after O(N log log N) preprocessing. It achieves this by recursively applying sqrt decomposition, precomputing block-wise prefix/suffix operations and inter-block results.
//   • Invariants: The `prefixOp` array for any block `k` stores the associative sum from the block's start to each element within it.; The `suffixOp` array for any block `k` stores the associative sum from each element within it to the block's end.
//   • Tips: Ensure the operation is strictly associative for correctness.; Carefully handle block boundaries and partial blocks during query processing.
//   • Pitfalls: Using non-associative operations will yield incorrect results.; High memory usage for the 'between' array if not optimized or if N is very large.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maximizeSum(vector<int>& nums, int k) {
        int maxNum = *max_element(nums.begin(), nums.end());
        int sum = 0;

        for (int i = 0; i < k; ++i) {
            sum += maxNum + i;
        }

        return sum;         
    }
};
