// Source: https://leetcode.com/problems/find-the-power-of-k-size-subarrays-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums of length n and a positive integer k.
//
// The power of an array is defined as:
//
//
// 	Its maximum element if all of its elements are consecutive and sorted in ascending order.
// 	-1 otherwise.
//
//
// You need to find the power of all subarrays of nums of size k.
//
// Return an integer array results of size n - k + 1, where results[i] is the power of nums[i..(i + k - 1)].
//
// Example:
// Input: nums = [1,2,3,4,3,2,5], k = 3
//
// Output: [3,4,-1,-1,-1]
//
// Explanation:
//
// There are 5 subarrays of nums of size 3:
//
//
// 	[1, 2, 3] with the maximum element 3.
// 	[2, 3, 4] with the maximum element 4.
// 	[3, 4, 3] whose elements are not consecutive.
// 	[4, 3, 2] whose elements are not sorted.
// 	[3, 2, 5] whose elements are not consecutive.
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	1 <= nums[i] <= 106
// 	1 <= k <= n
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
//   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
//   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
//   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
//   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
//   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// -  
// Kth order statistic in O(N) (array, quickselect, randomized)
//   • When to use: When you need to efficiently find the Kth smallest or largest element in an unsorted array. It is ideal when a full sort is unnecessary and average linear time performance is acceptable.
//   • Idea: Quickselect is a selection algorithm that finds the Kth smallest element in an unsorted list by repeatedly partitioning the array around a pivot. It achieves an average time complexity of O(N) and a worst-case complexity of O(N^2).
//   • Invariants: All elements in the left partition are less than or equal to the pivot element.; All elements in the right partition are greater than or equal to the pivot element.
//   • Tips: Shuffle the input array or choose a random pivot to achieve average O(N) performance.; The algorithm modifies the input array in place, so a copy might be needed if the original must be preserved.
//   • Pitfalls: A consistently bad pivot choice (e.g., always smallest/largest) leads to O(N^2) worst-case time.; Not suitable if the relative order of other elements needs to be preserved (it's not a stable algorithm).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number[]}
 */
var resultsArray = function(nums, k) {
    const n = nums.length;
    const results = new Array(n - k + 1).fill(-1);

    for (let i = 0; i <= n - k; i++) {
        const subarray = nums.slice(i, i + k);
        const sortedSubarray = [...subarray].sort((a, b) => a - b);
        let isConsecutive = true;

        for (let j = 1; j < k; j++) {
            if (sortedSubarray[j] !== sortedSubarray[j - 1] + 1) {
                isConsecutive = false;
                break;
            }
        }

        if (isConsecutive) {
            results[i] = sortedSubarray[k - 1];
        }
    }

    return results;
};
