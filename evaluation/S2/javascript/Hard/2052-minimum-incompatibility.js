// Source: https://leetcode.com/problems/minimum-incompatibility/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums​​​ and an integer k. You are asked to distribute this array into k subsets of equal size such that there are no two equal elements in the same subset.
//
// A subset's incompatibility is the difference between the maximum and minimum elements in that array.
//
// Return the minimum possible sum of incompatibilities of the k subsets after distributing the array optimally, or return -1 if it is not possible.
//
// A subset is a group integers that appear in the array with no particular order.
//
// Example:
// Input: nums = [1,2,1,4], k = 2
// Output: 4
// Explanation: The optimal distribution of subsets is [1,2] and [1,4].
// The incompatibility is (2-1) + (4-1) = 4.
// Note that [1,1] and [2,4] would result in a smaller sum, but the first subset contains 2 equal elements.
//
// Constraints:
// 1 <= k <= nums.length <= 16
// 	nums.length is divisible by k
// 	1 <= nums[i] <= nums.length
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - bucket-sort (array, bucket-sort)
//   • When to use: When the input elements are uniformly distributed across a specific range, allowing for efficient partitioning and sorting.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket, then concatenates them. It achieves O(N+K) average time complexity, where N is elements and K is buckets, assuming uniform distribution.
//   • Invariants: All elements from the input are initially present in the unsorted collection.; After distribution, each element resides in exactly one bucket, corresponding to its value range.
//   • Tips: Choose the number of buckets carefully based on data range and distribution.; Use an efficient sorting algorithm for individual buckets (e.g., insertion sort for small buckets).
//   • Pitfalls: Poor performance with non-uniform data distribution, leading to elements clustering in few buckets.; Requires knowing the range of input values beforehand to define bucket boundaries.
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
 * @return {number}
 */
var minimumIncompatibility = function(nums, k) {    
    const n = nums.length;
    const subsetSize = n / k;
    const maxMask = 1 << n;
    const incompatibility = new Array(maxMask).fill(Infinity);
    incompatibility[0] = 0;

    for (let mask = 0; mask < maxMask; mask++) {
        if (incompatibility[mask] === Infinity) continue;
        const count = mask.toString(2).split('1').length - 1;
        if (count % subsetSize === 0) {
            const used = new Set();
            let minVal = Infinity, maxVal = -Infinity;
            for (let i = 0; i < n; i++) {
                if ((mask & (1 << i)) === 0) {
                    if (used.has(nums[i])) {
                        minVal = maxVal = -1;
                        break;
                    }
                    used.add(nums[i]);
                    minVal = Math.min(minVal, nums[i]);
                    maxVal = Math.max(maxVal, nums[i]);
                }
            }
            if (minVal !== -1) {
                const newMask = mask | [...used].reduce((acc, val) => acc | (1 << nums.indexOf(val)), 0);
                incompatibility[newMask] = Math.min(incompatibility[newMask], incompatibility[mask] + maxVal - minVal);
            }
        }
    }
    return incompatibility[maxMask - 1] === Infinity ? -1 : incompatibility[maxMask - 1];
};