// Source: https://leetcode.com/problems/create-sorted-array-through-instructions/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array instructions, you are asked to create a sorted array from the elements in instructions. You start with an empty container nums. For each element from left to right in instructions, insert it into nums. The cost of each insertion is the minimum of the following:
//
//
// 	The number of elements currently in nums that are strictly less than instructions[i].
// 	The number of elements currently in nums that are strictly greater than instructions[i].
//
//
// For example, if inserting element 3 into nums = [1,2,3,5], the cost of insertion is min(2, 1) (elements 1 and 2 are less than 3, element 5 is greater than 3) and nums will become [1,2,3,3,5].
//
// Return the total cost to insert all elements from instructions into nums. Since the answer may be large, return it modulo 109 + 7
//
// Example:
// Input: instructions = [1,5,6,2]
// Output: 1
// Explanation: Begin with nums = [].
// Insert 1 with cost min(0, 0) = 0, now nums = [1].
// Insert 5 with cost min(1, 0) = 0, now nums = [1,5].
// Insert 6 with cost min(2, 0) = 0, now nums = [1,5,6].
// Insert 2 with cost min(1, 2) = 1, now nums = [1,2,5,6].
// The total cost is 0 + 0 + 0 + 1 = 1.
//
// Constraints:
// 1 <= instructions.length <= 105
// 	1 <= instructions[i] <= 105
//
// Helpful references (internal KB):
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
//   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
//   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
//   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
// - Fenwick Tree (array, bit-fenwick, difference-array)
//   • When to use: Use when you need to efficiently calculate prefix sums or range sums on an array that undergoes frequent point updates. It provides logarithmic time complexity for both operations.
//   • Idea: A Fenwick Tree, also known as a Binary Indexed Tree (BIT), is a data structure that can efficiently update individual elements and calculate prefix sums in an array. Both operations are performed in O(log N) time.
//   • Invariants: Each `tree[i]` element stores the sum of a contiguous range of elements from the original array, specifically from `i - (i & -i) + 1` to `i` (inclusive, 1-based).; After any `update(idx, val)` operation, `query(idx)` will reflect the new sum up to `idx`.
//   • Tips: Use 1-based indexing for array elements to simplify bitwise logic; The `idx & -idx` operation is key to navigating the implicit tree structure
//   • Pitfalls: Confusing 0-based and 1-based indexing can lead to incorrect results; Off-by-one errors when calculating range sums (e.g., `query(R) - query(L-1)`)
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
    public int createSortedArray(int[] instructions) {
        int mod = 1_000_000_007;
        int maxVal = 100_000; // Given constraint: 1 <= instructions[i] <= 10^5
        FenwickTree fenwickTree = new FenwickTree(maxVal);
        long cost = 0;

        for (int num : instructions) {
            int lessCount = fenwickTree.query(num - 1); // Count of elements less than num
            int greaterCount = fenwickTree.query(maxVal) - fenwickTree.query(num); // Count of elements greater than num
            cost += Math.min(lessCount, greaterCount);
            cost %= mod; // To prevent overflow
            fenwickTree.update(num, 1); // Insert num into the Fenwick Tree
        }

        return (int) cost;          
    }
}
