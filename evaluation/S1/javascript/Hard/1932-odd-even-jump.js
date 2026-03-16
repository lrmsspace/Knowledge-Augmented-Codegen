// Source: https://leetcode.com/problems/odd-even-jump/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array arr. From some starting index, you can make a series of jumps. The (1st, 3rd, 5th, ...) jumps in the series are called odd-numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called even-numbered jumps. Note that the jumps are numbered, not the indices.
//
// You may jump forward from index i to index j (with i < j) in the following way:
//
//
// 	During odd-numbered jumps (i.e., jumps 1, 3, 5, ...), you jump to the index j such that arr[i] <= arr[j] and arr[j] is the smallest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
// 	During even-numbered jumps (i.e., jumps 2, 4, 6, ...), you jump to the index j such that arr[i] >= arr[j] and arr[j] is the largest possible value. If there are multiple such indices j, you can only jump to the smallest such index j.
// 	It may be the case that for some index i, there are no legal jumps.
//
//
// A starting index is good if, starting from that index, you can reach the end of the array (index arr.length - 1) by jumping some number of times (possibly 0 or more than once).
//
// Return the number of good starting indices.
//
// Example:
// Input: arr = [10,13,12,14,15]
// Output: 2
// Explanation: 
// From starting index i = 0, we can make our 1st jump to i = 2 (since arr[2] is the smallest among arr[1], arr[2], arr[3], arr[4] that is greater or equal to arr[0]), then we cannot jump any more.
// From starting index i = 1 and i = 2, we can make our 1st jump to i = 3, then we cannot jump any more.
// From starting index i = 3, we can make our 1st jump to i = 4, so we have reached the end.
// From starting index i = 4, we have reached the end already.
// In total, there are 2 different starting indices i = 3 and i = 4, where we can reach the end with some number of
// jumps.
//
// Constraints:
// 1 <= arr.length <= 2 * 104
// 	0 <= arr[i] < 105
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} arr
 * @return {number}
 */
var oddEvenJumps = function(arr) {
    const n = arr.length;
    const nextHigher = new Array(n).fill(-1);
    const nextLower = new Array(n).fill(-1);

    // Create sorted indices for odd jumps (ascending order)
    const sortedIndices = Array.from({ length: n }, (_, i) => i).sort((a, b) => {
        if (arr[a] === arr[b]) return a - b; // Tie-breaker: smaller index first
        return arr[a] - arr[b];
    });

    // Calculate next higher jumps using a monotonic stack
    const stack = [];
    for (const index of sortedIndices) {
        while (stack.length && stack[stack.length - 1] < index) {
            nextHigher[stack.pop()] = index;
        }
        stack.push(index);
    }

    // Create sorted indices for even jumps (descending order)
    const sortedIndicesDesc = Array.from({ length: n }, (_, i) => i).sort((a, b) => {
        if (arr[a] === arr[b]) return a - b; // Tie-breaker: smaller index first
        return arr[b] - arr[a];
    });

    // Calculate next lower jumps using a monotonic stack
    stack.length = 0; // Clear the stack
    for (const index of sortedIndicesDesc) {
        while (stack.length && stack[stack.length - 1] < index) {
            nextLower[stack.pop()] = index;
        }
        stack.push(index);
    }

    const canReachEndOdd = new Array(n).fill(false);
    const canReachEndEven = new Array(n).fill(false);
    canReachEndOdd[n - 1] = true;
    canReachEndEven[n - 1] = true;

    for (let i = n - 2; i >= 0; i--) {
        if (nextHigher[i] !== -1) {
            canReachEndOdd[i] = canReachEndEven[nextHigher[i]];
        }
        if (nextLower[i] !== -1) {
            canReachEndEven[i] = canReachEndOdd[nextLower[i]];
        }
    }

    let countGoodStartingIndices = 0;
    for (let i = 0; i < n; i++) {
        if (canReachEndOdd[i]) countGoodStartingIndices++;
    }

    return countGoodStartingIndices;
};
