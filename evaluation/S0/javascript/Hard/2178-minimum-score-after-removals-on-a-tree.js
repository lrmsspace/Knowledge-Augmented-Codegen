// Source: https://leetcode.com/problems/minimum-score-after-removals-on-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.
//
// You are given a 0-indexed integer array nums of length n where nums[i] represents the value of the ith node. You are also given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// Remove two distinct edges of the tree to form three connected components. For a pair of removed edges, the following steps are defined:
//
//
// 	Get the XOR of all the values of the nodes for each of the three components respectively.
// 	The difference between the largest XOR value and the smallest XOR value is the score of the pair.
//
//
//
// 	For example, say the three components have the node values: [4,5,7], [1,9], and [3,3,3]. The three XOR values are 4 ^ 5 ^ 7 = 6, 1 ^ 9 = 8, and 3 ^ 3 ^ 3 = 3. The largest XOR value is 8 and the smallest XOR value is 3. The score is then 8 - 3 = 5.
//
//
// Return the minimum score of any possible pair of edge removals on the given tree.
//
// Example:
// Input: nums = [1,5,5,4,11], edges = [[0,1],[1,2],[1,3],[3,4]]
// Output: 9
// Explanation: The diagram above shows a way to make a pair of removals.
// - The 1st component has nodes [1,3,4] with values [5,4,11]. Its XOR value is 5 ^ 4 ^ 11 = 10.
// - The 2nd component has node [0] with value [1]. Its XOR value is 1 = 1.
// - The 3rd component has node [2] with value [5]. Its XOR value is 5 = 5.
// The score is the difference between the largest and smallest XOR value which is 10 - 1 = 9.
// It can be shown that no other pair of removals will obtain a smaller score than 9.
//
// Constraints:
// n == nums.length
// 	3 <= n <= 1000
// 	1 <= nums[i] <= 108
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	edges represents a valid tree.
//

/**
 * @param {number[]} nums
 * @param {number[][]} edges
 * @return {number}
 */
var minimumScore = function(nums, edges) {
    const n = nums.length;
    const graph = Array.from({ length: n }, () => []);
    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }
    const subtreeXOR = new Array(n).fill(0);
    const dfs = (node, parent) => {
        subtreeXOR[node] = nums[node];
        for (const neighbor of graph[node]) {
            if (neighbor !== parent) {
                dfs(neighbor, node);
                subtreeXOR[node] ^= subtreeXOR[neighbor];
            }
        }
    };
    dfs(0, -1);
    let minScore = Infinity;
    for (let i = 0; i < n; i++) {
        for (const neighbor of graph[i]) {
            if (neighbor > i) {
                const xor1 = subtreeXOR[neighbor];
                const xor2 = subtreeXOR[0] ^ xor1;
                const xor3 = 0; // The third component is empty
                const maxXOR = Math.max(xor1, xor2, xor3);
                const minXOR = Math.min(xor1, xor2, xor3);
                minScore = Math.min(minScore, maxXOR - minXOR);
            }
        }
    }
    return minScore;
};
