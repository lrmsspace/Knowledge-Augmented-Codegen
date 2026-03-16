// Source: https://leetcode.com/problems/smallest-subarrays-with-maximum-bitwise-or/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums of length n, consisting of non-negative integers. For each index i from 0 to n - 1, you must determine the size of the minimum sized non-empty subarray of nums starting at i (inclusive) that has the maximum possible bitwise OR.
//
//
// 	In other words, let Bij be the bitwise OR of the subarray nums[i...j]. You need to find the smallest subarray starting at i, such that bitwise OR of this subarray is equal to max(Bik) where i <= k <= n - 1.
//
//
// The bitwise OR of an array is the bitwise OR of all the numbers in it.
//
// Return an integer array answer of size n where answer[i] is the length of the minimum sized subarray starting at i with maximum bitwise OR.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,0,2,1,3]
// Output: [3,3,2,2,1]
// Explanation:
// The maximum possible bitwise OR starting at any index is 3. 
// - Starting at index 0, the shortest subarray that yields it is [1,0,2].
// - Starting at index 1, the shortest subarray that yields the maximum bitwise OR is [0,2,1].
// - Starting at index 2, the shortest subarray that yields the maximum bitwise OR is [2,1].
// - Starting at index 3, the shortest subarray that yields the maximum bitwise OR is [1,3].
// - Starting at index 4, the shortest subarray that yields the maximum bitwise OR is [3].
// Therefore, we return [3,3,2,2,1].
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	0 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
//   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
//   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
//   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
// - Fenwick Tree (array, bit-fenwick, prefix-sum)
//   • When to use: Use when frequent point updates and range sum queries are needed on an array. It offers logarithmic time complexity for both operations, making it more efficient than a simple prefix sum array for dynamic data.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently calculates prefix sums and updates individual elements in an array. Both operations typically run in O(log N) time.
//   • Invariants: Each node `tree[i]` stores the sum of a specific range of elements ending at index `i`.; The length of the range summed by `tree[i]` is determined by `i & (-i)` (lowbit operation).
//   • Tips: Understand the lowbit operation and its role in navigating the tree structure.; Use 1-based indexing for simpler implementation of lowbit calculations.
//   • Pitfalls: Forgetting 1-based indexing can lead to off-by-one errors and incorrect results.; Incorrectly implementing the lowbit calculation or update/query logic.
// - Fenwick Tree (array, bit-fenwick, prefix-sum)
//   • When to use: When you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It is ideal for scenarios requiring both fast query and update operations on an array.
//   • Idea: A Fenwick tree, or Binary Indexed Tree (BIT), is an array-based data structure that efficiently calculates prefix sums and updates individual elements in an array. It supports both point updates and prefix sum queries in O(log N) time complexity.
//   • Invariants: Each `T[i]` stores the sum of a specific range `[g(i), i]` from the original array.; The `sum(idx)` function correctly aggregates values from `A[0]` to `A[idx]`.
//   • Tips: Understand the bit manipulation (`i & -i`) for navigating parent/child relationships.; Consistently choose and apply either 0-based or 1-based indexing throughout the implementation.
//   • Pitfalls: Incorrectly handling 0-based versus 1-based indexing can lead to off-by-one errors.; Forgetting to initialize the tree or performing updates incorrectly will yield wrong results.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] smallestSubarrays(int[] nums) {
        int n = nums.length;
        int[] answer = new int[n];
        int[] lastSeen = new int[30]; // To track the last seen index of each bit

        for (int i = n - 1; i >= 0; i--) {
            // Update the last seen index for each bit in nums[i]
            for (int bit = 0; bit < 30; bit++) {
                if ((nums[i] & (1 << bit)) != 0) {
                    lastSeen[bit] = i;
                }
            }

            // Calculate the maximum index we need to reach to get the maximum OR
            int maxIndex = i;
            for (int bit = 0; bit < 30; bit++) {
                if (lastSeen[bit] > maxIndex) {
                    maxIndex = lastSeen[bit];
                }
            }

            // The length of the subarray is the distance from i to maxIndex
            answer[i] = maxIndex - i + 1;
        }

        return answer;          
    }
}
