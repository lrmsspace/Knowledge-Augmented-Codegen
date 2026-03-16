// Source: https://leetcode.com/problems/next-greater-element-iv/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array of non-negative integers nums. For each integer in nums, you must find its respective second greater integer.
//
// The second greater integer of nums[i] is nums[j] such that:
//
//
// 	j > i
// 	nums[j] > nums[i]
// 	There exists exactly one index k such that nums[k] > nums[i] and i < k < j.
//
//
// If there is no such nums[j], the second greater integer is considered to be -1.
//
//
// 	For example, in the array [1, 2, 4, 3], the second greater integer of 1 is 4, 2 is 3, and that of 3 and 4 is -1.
//
//
// Return an integer array answer, where answer[i] is the second greater integer of nums[i].
//
// Example:
// Input: nums = [2,4,0,9,6]
// Output: [9,6,6,-1,-1]
// Explanation:
// 0th index: 4 is the first integer greater than 2, and 9 is the second integer greater than 2, to the right of 2.
// 1st index: 9 is the first, and 6 is the second integer greater than 4, to the right of 4.
// 2nd index: 9 is the first, and 6 is the second integer greater than 0, to the right of 0.
// 3rd index: There is no integer greater than 9 to its right, so the second greater integer is considered to be -1.
// 4th index: There is no integer greater than 6 to its right, so the second greater integer is considered to be -1.
// Thus, we return [9,6,6,-1,-1].
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d, segment-tree, coordinate-compress)
//   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order, preserving their original relative order.
//   • Idea: This algorithm finds the longest subsequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search or a segment tree.
//   • Invariants: The 'tails' array (or DP array) is always sorted in increasing order.; For any index 'i', 'tails[i]' stores the smallest possible ending element of an increasing subsequence of length 'i+1'.
//   • Tips: The O(N log N) approach maintains an array where dp[i] stores the smallest ending element of an increasing subsequence of length i+1.; Binary search is used to find the correct position for the current element in the dp array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates for strictly increasing versus non-decreasing requirements.
// - Second Best Minimum Spanning Tree (graph, array, mst-kruskal, enumeration)
//   • When to use: Use when you need to find a spanning tree with the second smallest total edge weight, often for redundancy or alternative network path planning. It's applicable in scenarios requiring fault tolerance beyond a single optimal solution.
//   • Idea: This algorithm finds a spanning tree with the second minimum total edge weight in a connected, undirected graph. It involves finding the primary MST, then modifying it by replacing one MST edge with a non-MST edge.
//   • Invariants: The primary MST is always a valid spanning tree with minimum total weight.; Adding any non-MST edge (u,v) to the MST creates exactly one cycle.
//   • Tips: First, compute the primary Minimum Spanning Tree (MST) using an algorithm like Kruskal's or Prim's.; For each edge not in the MST, adding it to the MST creates a unique cycle. Find the maximum weight edge on this cycle.
//   • Pitfalls: Naively recomputing an entire MST for each removed edge is inefficient (O(V * E log E)).; Incorrectly identifying the maximum weight edge on the cycle formed by adding a non-MST edge.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number[]}
 */
var secondGreaterElement = function(nums) {
    const n = nums.length;
    const result = new Array(n).fill(-1);
    const stack1 = [];
    const stack2 = [];
    
    for (let i = 0; i < n; i++) {
        while (stack2.length && nums[stack2[stack2.length - 1]] < nums[i]) {
            result[stack2.pop()] = nums[i];
        }
        const temp = [];
        while (stack1.length && nums[stack1[stack1.length - 1]] < nums[i]) {
            temp.push(stack1.pop());
        }
        while (temp.length) {
            stack2.push(temp.pop());
        }
        stack1.push(i);
    }
    
    return result;
};
