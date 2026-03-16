// Source: https://leetcode.com/problems/make-k-subarray-sums-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array arr and an integer k. The array arr is circular. In other words, the first element of the array is the next element of the last element, and the last element of the array is the previous element of the first element.
//
// You can do the following operation any number of times:
//
//
// 	Pick any element from arr and increase or decrease it by 1.
//
//
// Return the minimum number of operations such that the sum of each subarray of length k is equal.
//
// A subarray is a contiguous part of the array.
//
// Example:
// Input: arr = [1,4,1,3], k = 2
// Output: 1
// Explanation: we can do one operation on index 1 to make its value equal to 3.
// The array after the operation is [1,3,1,3]
// - Subarray starts at index 0 is [1, 3], and its sum is 4 
// - Subarray starts at index 1 is [3, 1], and its sum is 4 
// - Subarray starts at index 2 is [1, 3], and its sum is 4 
// - Subarray starts at index 3 is [3, 1], and its sum is 4
//
// Constraints:
// 1 <= k <= arr.length <= 105
// 	1 <= arr[i] <= 109
//
// Helpful references (internal KB):
// - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
//   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
//   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
//   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
//   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
// - Josephus Problem (number, dp-1d, recursion)
//   • When to use: Used to determine the position of the last remaining person in a circle where every k-th person is eliminated until only one remains. It models sequential removal processes in a circular arrangement.
//   • Idea: The Josephus Problem determines the position of the survivor in a circle of N people, where every K-th person is eliminated. The standard solution uses a recursive relation or dynamic programming, typically achieving O(N) time complexity.
//   • Invariants: The result J(n, k) represents the survivor's original 0-indexed position among n people.; Each recursive step J(n, k) correctly transforms the result from J(n-1, k) based on the k-th elimination.
//   • Tips: Use 0-indexing for a simpler and more elegant recursive formula.; Establish the base case for N=1 (the survivor is always 0 or 1).
//   • Pitfalls: Off-by-one errors when switching between 0-indexing and 1-indexing.; Incorrectly applying the modulo operator, especially with negative results in some languages.
// - Finding a negative cycle in the graph (graph, array, bellman-ford)
//   • When to use: Use when a graph may contain negative edge weights and you need to find the shortest paths from a single source, or specifically to detect and identify negative cycles.
//   • Idea: The Bellman-Ford algorithm computes single-source shortest paths in a weighted graph, even with negative edge weights, and can detect negative cycles. It has a time complexity of O(VE).
//   • Invariants: After k iterations, dist[v] is the shortest path from the source to v using at most k edges.; If no negative cycle is reachable, dist[v] will be the true shortest path distance after V-1 iterations.
//   • Tips: Perform V-1 iterations for shortest path calculation, then one more for cycle detection.; A negative cycle exists if any distance can still be reduced in the V-th iteration.
//   • Pitfalls: Inefficient for graphs with only non-negative weights compared to Dijkstra's.; Does not directly work for undirected graphs with negative edges.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} arr
 * @param {number} k
 * @return {number}
 */
var makeSubKSumEqual = function(arr, k) {
    const n = arr.length;
    const groups = new Array(k).fill(0).map(() => []);
    for (let i = 0; i < n; i++) {
        groups[i % k].push(arr[i]);
    }
    let operations = 0;
    for (const group of groups) {
        group.sort((a, b) => a - b);
        const median = group[Math.floor(group.length / 2)];
        for (const num of group) {
            operations += Math.abs(num - median);
        }
    }
    return operations;
};
