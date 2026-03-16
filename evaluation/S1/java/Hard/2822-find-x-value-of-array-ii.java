// Source: https://leetcode.com/problems/find-x-value-of-array-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums and a positive integer k. You are also given a 2D array queries, where queries[i] = [indexi, valuei, starti, xi].
//
// You are allowed to perform an operation once on nums, where you can remove any suffix from nums such that nums remains non-empty.
//
// The x-value of nums for a given x is defined as the number of ways to perform this operation so that the product of the remaining elements leaves a remainder of x modulo k.
//
// For each query in queries you need to determine the x-value of nums for xi after performing the following actions:
//
//
// 	Update nums[indexi] to valuei. Only this step persists for the rest of the queries.
// 	Remove the prefix nums[0..(starti - 1)] (where nums[0..(-1)] will be used to represent the empty prefix).
//
//
// Return an array result of size queries.length where result[i] is the answer for the ith query.
//
// A prefix of an array is a subarray that starts from the beginning of the array and extends to any point within it.
//
// A suffix of an array is a subarray that starts at any point within the array and extends to the end of the array.
//
// Note that the prefix and suffix to be chosen for the operation can be empty.
//
// Note that x-value has a different definition in this version.
//
// Example:
// Input: nums = [1,2,3,4,5], k = 3, queries = [[2,2,0,2],[3,3,3,0],[0,1,0,1]]
//
// Output: [2,2,2]
//
// Explanation:
//
//
// 	For query 0, nums becomes [1, 2, 2, 4, 5], and the empty prefix must be removed. The possible operations are:
//
// 	
// 		Remove the suffix [2, 4, 5]. nums becomes [1, 2].
// 		Remove the empty suffix. nums becomes [1, 2, 2, 4, 5] with a product 80, which gives remainder 2 when divided by 3.
// 	
// 	
// 	For query 1, nums becomes [1, 2, 2, 3, 5], and the prefix [1, 2, 2] must be removed. The possible operations are:
// 	
// 		Remove the empty suffix. nums becomes [3, 5].
// 		Remove the suffix [5]. nums becomes [3].
// 	
// 	
// 	For query 2, nums becomes [1, 2, 2, 3, 5], and the empty prefix must be removed. The possible operations are:
// 	
// 		Remove the suffix [2, 2, 3, 5]. nums becomes [1].
// 		Remove the suffix [3, 5]. nums becomes [1, 2, 2].
//
// Constraints:
// 1 <= nums[i] <= 109
// 	1 <= nums.length <= 105
// 	1 <= k <= 5
// 	1 <= queries.length <= 2 * 104
// 	queries[i] == [indexi, valuei, starti, xi]
// 	0 <= indexi <= nums.length - 1
// 	1 <= valuei <= 109
// 	0 <= starti <= nums.length - 1
// 	0 <= xi <= k - 1
//
// Helpful references (internal KB):
// - Segment Tree (tree, array, segment-tree, recursion, divide-and-conquer)
//   • When to use: Use for efficient range queries and updates on an array. It handles aggregated information over dynamic intervals.
//   • Idea: A segment tree is a tree data structure used for storing information about intervals or segments. It allows answering range queries and range updates in logarithmic time, making it efficient for dynamic array problems.
//   • Invariants: Each node represents a contiguous segment of the original array.; The value stored in a parent node is an aggregation of its children's values.
//   • Tips: Build the tree recursively, dividing the array into halves.; Each node stores an aggregate value for its corresponding segment.
//   • Pitfalls: Incorrectly handling array indexing (0-based vs 1-based).; Off-by-one errors in segment boundaries during queries/updates.
// - MEX (minimal excluded) of a sequence (tree, binary-search)
//   • When to use: Use when you need to efficiently find the MEX of a sequence after multiple point updates, where the sequence elements are non-negative integers.
//   • Idea: This approach uses a segment tree or similar data structure to maintain counts of elements, allowing efficient O(log N) updates and O(log N) queries for the minimal excluded number (MEX). The core idea is to find the smallest non-negative integer not present in the sequence.
//   • Invariants: Each node in the segment tree correctly stores the count of distinct numbers within its represented range.; The MEX query always explores the leftmost child first if its range is not 'full' (i.e., missing elements).
//   • Tips: Build the tree over the range of possible non-negative integer values, typically up to N or a maximum constraint.; Each tree node should store the count of distinct numbers present within its represented range.
//   • Pitfalls: Forgetting to handle numbers larger than the maximum range covered by the segment tree.; Incorrectly updating counts for elements, leading to stale or erroneous MEX values.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private int modInverse(int a, int mod) {
        a = a % mod;
        for (int x = 1; x < mod; x++) {
            if ((a * x) % mod == 1) {
                return x;
            }
        }
        return 1; // Should not reach here for valid inputs
    }
    public int[] resultArray(int[] nums, int k, int[][] queries) {
        int n = nums.length;
        int q = queries.length;
        int[] result = new int[q];

        // Precompute prefix products modulo k
        int[] prefixProducts = new int[n + 1];
        prefixProducts[0] = 1;
        for (int i = 0; i < n; i++) {
            prefixProducts[i + 1] = (prefixProducts[i] * (nums[i] % k)) % k;
        }

        for (int i = 0; i < q; i++) {
            int index = queries[i][0];
            int value = queries[i][1];
            int start = queries[i][2];
            int x = queries[i][3];

            // Update nums[index] to value
            int oldValueMod = nums[index] % k;
            int newValueMod = value % k;
            nums[index] = value;

            // Recompute prefix products from index onwards
            for (int j = index; j < n; j++) {
                prefixProducts[j + 1] = (prefixProducts[j] * (nums[j] % k)) % k;
            }

            // Calculate the product of the remaining elements after removing the prefix
            int productModK = prefixProducts[n] * modInverse(prefixProducts[start], k) % k;

            // Count the number of suffixes that give remainder x
            int count = 0;
            for (int j = start; j <= n; j++) {
                if (prefixProducts[j] * modInverse(prefixProducts[start], k) % k == x) {
                    count++;
                }
            }

            result[i] = count;
        }

        return result;          
    }
}
