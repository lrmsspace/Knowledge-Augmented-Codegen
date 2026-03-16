// Source: https://leetcode.com/problems/minimum-cost-to-split-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// Split the array into some number of non-empty subarrays. The cost of a split is the sum of the importance value of each subarray in the split.
//
// Let trimmed(subarray) be the version of the subarray where all numbers which appear only once are removed.
//
//
// 	For example, trimmed([3,1,2,4,3,4]) = [3,4,3,4].
//
//
// The importance value of a subarray is k + trimmed(subarray).length.
//
//
// 	For example, if a subarray is [1,2,3,3,3,4,4], then trimmed([1,2,3,3,3,4,4]) = [3,3,3,4,4].The importance value of this subarray will be k + 5.
//
//
// Return the minimum possible cost of a split of nums.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,1,2,1,3,3], k = 2
// Output: 8
// Explanation: We split nums to have two subarrays: [1,2], [1,2,1,3,3].
// The importance value of [1,2] is 2 + (0) = 2.
// The importance value of [1,2,1,3,3] is 2 + (2 + 2) = 6.
// The cost of the split is 2 + 6 = 8. It can be shown that this is the minimum possible cost among all the possible splits.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	0 <= nums[i] < nums.length
// 	1 <= k <= 109
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
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - MEX (minimal excluded) of a sequence (tree, binary-search)
//   • When to use: Use when you need to efficiently find the MEX of a sequence after multiple point updates, where the sequence elements are non-negative integers.
//   • Idea: This approach uses a segment tree or similar data structure to maintain counts of elements, allowing efficient O(log N) updates and O(log N) queries for the minimal excluded number (MEX). The core idea is to find the smallest non-negative integer not present in the sequence.
//   • Invariants: Each node in the segment tree correctly stores the count of distinct numbers within its represented range.; The MEX query always explores the leftmost child first if its range is not 'full' (i.e., missing elements).
//   • Tips: Build the tree over the range of possible non-negative integer values, typically up to N or a maximum constraint.; Each tree node should store the count of distinct numbers present within its represented range.
//   • Pitfalls: Forgetting to handle numbers larger than the maximum range covered by the segment tree.; Incorrectly updating counts for elements, leading to stale or erroneous MEX values.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minCost(int[] nums, int k) {
        int n = nums.length;
        int[] dp = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i - 1] + k;
            Map<Integer, Integer> freq = new HashMap<>();
            for (int j = i - 1; j >= 0; j--) {
                freq.put(nums[j], freq.getOrDefault(nums[j], 0) + 1);
                int importance = k;
                for (int count : freq.values()) {
                    if (count > 1) {
                        importance += count;
                    }
                }
                dp[i] = Math.min(dp[i], dp[j] + importance);
            }
        }
        return dp[n];           
    }
}
