// Source: https://leetcode.com/problems/maximum-candies-you-can-get-from-boxes/   |   Difficulty: Hard
//
// Problem Description:
// You have n boxes labeled from 0 to n - 1. You are given four arrays: status, candies, keys, and containedBoxes where:
//
//
// 	status[i] is 1 if the ith box is open and 0 if the ith box is closed,
// 	candies[i] is the number of candies in the ith box,
// 	keys[i] is a list of the labels of the boxes you can open after opening the ith box.
// 	containedBoxes[i] is a list of the boxes you found inside the ith box.
//
//
// You are given an integer array initialBoxes that contains the labels of the boxes you initially have. You can take all the candies in any open box and you can use the keys in it to open new boxes and you also can use the boxes you find in it.
//
// Return the maximum number of candies you can get following the rules above.
//
// Example:
// Input: status = [1,0,1,0], candies = [7,5,4,100], keys = [[],[],[1],[]], containedBoxes = [[1,2],[3],[],[]], initialBoxes = [0]
// Output: 16
// Explanation: You will be initially given box 0. You will find 7 candies in it and boxes 1 and 2.
// Box 1 is closed and you do not have a key for it so you will open box 2. You will find 4 candies and a key to box 1 in box 2.
// In box 1, you will find 5 candies and box 3 but you will not find a key to box 3 so box 3 will remain closed.
// Total number of candies collected = 7 + 4 + 5 = 16 candy.
//
// Constraints:
// n == status.length == candies.length == keys.length == containedBoxes.length
// 	1 <= n <= 1000
// 	status[i] is either 0 or 1.
// 	1 <= candies[i] <= 1000
// 	0 <= keys[i].length <= n
// 	0 <= keys[i][j] < n
// 	All values of keys[i] are unique.
// 	0 <= containedBoxes[i].length <= n
// 	0 <= containedBoxes[i][j] < n
// 	All values of containedBoxes[i] are unique.
// 	Each box is contained in one box at most.
// 	0 <= initialBoxes.length <= n
// 	0 <= initialBoxes[i] < n
//
// Helpful references (internal KB):
// - Breadth-first search (graph, array, bfs, counting)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
//   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
//   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} status
 * @param {number[]} candies
 * @param {number[][]} keys
 * @param {number[][]} containedBoxes
 * @param {number[]} initialBoxes
 * @return {number}
 */
var maxCandies = function(status, candies, keys, containedBoxes, initialBoxes) {
    const n = status.length;
    const visited = new Set();
    const queue = [...initialBoxes];
    let totalCandies = 0;

    while (queue.length) {
        const box = queue.shift();
        if (visited.has(box)) continue;
        visited.add(box);

        if (status[box] === 1) {
            totalCandies += candies[box];
            for (const key of keys[box]) {
                status[key] = 1; // Open the box using the key
            }
            for (const containedBox of containedBoxes[box]) {
                queue.push(containedBox); // Add contained boxes to the queue
            }
        }
    }

    return totalCandies;
};
