// Source: https://leetcode.com/problems/flower-planting-with-no-adjacent/   |   Difficulty: Medium
//
// Problem Description:
// You have n gardens, labeled from 1 to n, and an array paths where paths[i] = [xi, yi] describes a bidirectional path between garden xi to garden yi. In each garden, you want to plant one of 4 types of flowers.
//
// All gardens have at most 3 paths coming into or leaving it.
//
// Your task is to choose a flower type for each garden such that, for any two gardens connected by a path, they have different types of flowers.
//
// Return any such a choice as an array answer, where answer[i] is the type of flower planted in the (i+1)th garden. The flower types are denoted 1, 2, 3, or 4. It is guaranteed an answer exists.
//
// Example:
// Input: n = 3, paths = [[1,2],[2,3],[3,1]]
// Output: [1,2,3]
// Explanation:
// Gardens 1 and 2 have different types.
// Gardens 2 and 3 have different types.
// Gardens 3 and 1 have different types.
// Hence, [1,2,3] is a valid answer. Other valid answers include [1,2,4], [1,4,2], and [3,2,1].
//
// Constraints:
// 1 <= n <= 104
// 	0 <= paths.length <= 2 * 104
// 	paths[i].length == 2
// 	1 <= xi, yi <= n
// 	xi != yi
// 	Every garden has at most 3 paths coming into or leaving it.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} n
 * @param {number[][]} paths
 * @return {number[]}
 */
var gardenNoAdj = function(n, paths) {
    const graph = new Array(n).fill(0).map(() => []);
    for (const [x, y] of paths) {
        graph[x - 1].push(y - 1);
        graph[y - 1].push(x - 1);
    }
    const result = new Array(n).fill(0);
    for (let i = 0; i < n; i++) {
        const used = new Set();
        for (const neighbor of graph[i]) {
            if (result[neighbor] !== 0) {
                used.add(result[neighbor]);
            }
        }
        for (let color = 1; color <= 4; color++) {
            if (!used.has(color)) {
                result[i] = color;
                break;
            }
        }
    }
    return result;
};
