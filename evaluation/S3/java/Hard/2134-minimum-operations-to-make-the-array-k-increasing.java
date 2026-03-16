// Source: https://leetcode.com/problems/minimum-operations-to-make-the-array-k-increasing/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array arr consisting of n positive integers, and a positive integer k.
//
// The array arr is called K-increasing if arr[i-k] <= arr[i] holds for every index i, where k <= i <= n-1.
//
//
// 	For example, arr = [4, 1, 5, 2, 6, 2] is K-increasing for k = 2 because:
//
// 	
// 		arr[0] <= arr[2] (4 <= 5)
// 		arr[1] <= arr[3] (1 <= 2)
// 		arr[2] <= arr[4] (5 <= 6)
// 		arr[3] <= arr[5] (2 <= 2)
// 	
// 	
// 	However, the same arr is not K-increasing for k = 1 (because arr[0] > arr[1]) or k = 3 (because arr[0] > arr[3]).
//
//
// In one operation, you can choose an index i and change arr[i] into any positive integer.
//
// Return the minimum number of operations required to make the array K-increasing for the given k.
//
// Example:
// Input: arr = [5,4,3,2,1], k = 1
// Output: 4
// Explanation:
// For k = 1, the resultant array has to be non-decreasing.
// Some of the K-increasing arrays that can be formed are [5,6,7,8,9], [1,1,1,1,1], [2,2,3,4,4]. All of them require 4 operations.
// It is suboptimal to change the array to, for example, [6,7,8,9,10] because it would take 5 operations.
// It can be shown that we cannot make the array K-increasing in less than 4 operations.
//
// Constraints:
// 1 <= arr.length <= 105
// 	1 <= arr[i], k <= arr.length
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Binomial Coefficients (array, enumeration)
//   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
//   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
//   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
//   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
//   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int kIncreasing(int[] arr, int k) {
        int n = arr.length;
        int operations = 0;

        for (int start = 0; start < k; start++) {
            List<Integer> subsequence = new ArrayList<>();
            for (int i = start; i < n; i += k) {
                subsequence.add(arr[i]);
            }
            operations += countOperations(subsequence);
        }

        return operations;          
    }
}
