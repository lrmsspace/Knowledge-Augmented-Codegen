// Source: https://leetcode.com/problems/minimum-reverse-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an integer p representing an array arr of length n where all elements are set to 0's, except position p which is set to 1. You are also given an integer array banned containing restricted positions. Perform the following operation on arr:
//
//
// 	Reverse a subarray with size k if the single 1 is not set to a position in banned.
//
//
// Return an integer array answer with n results where the ith result is the minimum number of operations needed to bring the single 1 to position i in arr, or -1 if it is impossible.
//
// Example:
// Input: n = 4, p = 0, banned = [1,2], k = 4
//
// Output: [0,-1,-1,1]
//
// Explanation:
//
//
// 	Initially 1 is placed at position 0 so the number of operations we need for position 0 is 0.
// 	We can never place 1 on the banned positions, so the answer for positions 1 and 2 is -1.
// 	Perform the operation of size 4 to reverse the whole array.
// 	After a single operation 1 is at position 3 so the answer for position 3 is 1.
//
// Constraints:
// 1 <= n <= 105
// 	0 <= p <= n - 1
// 	0 <= banned.length <= n - 1
// 	0 <= banned[i] <= n - 1
// 	1 <= k <= n 
// 	banned[i] != p
// 	all values in banned are unique
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number} p
 * @param {number[]} banned
 * @param {number} k
 * @return {number[]}
 */
var minReverseOperations = function(n, p, banned, k) {
    const answer = new Array(n).fill(-1);
    const bannedSet = new Set(banned);
    const visited = new Set();
    const queue = [[p, 0]]; // [current position, number of operations]

    while (queue.length > 0) {
        const [current, ops] = queue.shift();

        if (answer[current] === -1) {
            answer[current] = ops;
        }

        for (const next of getNextPositions(current, n, k)) {
            if (!bannedSet.has(next) && !visited.has(next)) {
                visited.add(next);
                queue.push([next, ops + 1]);
            }
        }
    }

    return answer;
};
