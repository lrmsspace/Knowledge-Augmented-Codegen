// Source: https://leetcode.com/problems/majority-element/   |   Difficulty: Easy
//
// Problem Description:
// Given an array nums of size n, return the majority element.
//
// The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.
//
// Example:
// Input: nums = [3,2,3]
// Output: 3
//
// Constraints:
// n == nums.length
// 	1 <= n <= 5 * 104
// 	-109 <= nums[i] <= 109
//
//
//  
// Follow-up: Could you solve the problem in linear time and in O(1) space?
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// -  
// Kth order statistic in O(N) (array, quickselect, randomized)
//   • When to use: When you need to efficiently find the Kth smallest or largest element in an unsorted array. It is ideal when a full sort is unnecessary and average linear time performance is acceptable.
//   • Idea: Quickselect is a selection algorithm that finds the Kth smallest element in an unsorted list by repeatedly partitioning the array around a pivot. It achieves an average time complexity of O(N) and a worst-case complexity of O(N^2).
//   • Invariants: All elements in the left partition are less than or equal to the pivot element.; All elements in the right partition are greater than or equal to the pivot element.
//   • Tips: Shuffle the input array or choose a random pivot to achieve average O(N) performance.; The algorithm modifies the input array in place, so a copy might be needed if the original must be preserved.
//   • Pitfalls: A consistently bad pivot choice (e.g., always smallest/largest) leads to O(N^2) worst-case time.; Not suitable if the relative order of other elements needs to be preserved (it's not a stable algorithm).
// - Lowest Common Ancestor - Farach-Colton and Bender Algorithm (array, divide-and-conquer, sparse-table, enumeration)
//   • When to use: This algorithm is used to answer Lowest Common Ancestor queries on a tree in O(1) time after O(N) preprocessing. It's particularly efficient for many queries on a static tree.
//   • Idea: This algorithm solves LCA by reducing it to RMQ on an Euler tour. It achieves O(1) query time after O(N) preprocessing by combining a sparse table on block minimums with precomputed RMQ for distinct block types.
//   • Invariants: For any query range [l, r], the minimum is found by considering the suffix of l's block, the prefix of r's block, and the minimum of full blocks in between.; The sparse table correctly stores RMQ for all block minimums in O(1) time.
//   • Tips: Reduce LCA to RMQ using an Euler tour and depth array.; Divide the array into blocks of size K = 0.5 log N.
//   • Pitfalls: Complexity of Euler tour construction for LCA reduction.; Correctly handling edge cases for queries entirely within a block or spanning block boundaries.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var majorityElement = function(nums) {
    let count = 0;
    let candidate = null;
    for (let num of nums) {
        if (count === 0) {
            candidate = num;
        }
        count += (num === candidate) ? 1 : -1;
    }
    return candidate;
};