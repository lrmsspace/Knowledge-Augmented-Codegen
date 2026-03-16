// Source: https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n. There is an undirected graph with n nodes, numbered from 0 to n - 1. You are given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
//
// Return the number of pairs of different nodes that are unreachable from each other.
//
// Example:
// Input: n = 3, edges = [[0,1],[0,2],[1,2]]
// Output: 0
// Explanation: There are no pairs of nodes that are unreachable from each other. Therefore, we return 0.
//
// Constraints:
// 1 <= n <= 105
// 	0 <= edges.length <= 2 * 105
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	There are no repeated edges.
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number}
 */
var countPairs = function(n, edges) {
    const parent = Array.from({ length: n }, (_, i) => i);
    const size = Array(n).fill(1);

    function find(x) {
        if (parent[x] !== x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    function union(a, b) {
        const rootA = find(a);
        const rootB = find(b);
        if (rootA !== rootB) {
            if (size[rootA] < size[rootB]) {
                parent[rootA] = rootB;
                size[rootB] += size[rootA];
            } else {
                parent[rootB] = rootA;
                size[rootA] += size[rootB];
            }
        }
    }

    for (const [a, b] of edges) {
        union(a, b);
    }

    let result = 0;
    let remaining = n;
    for (let i = 0; i < n; i++) {
        if (parent[i] === i) {
            remaining -= size[i];
            result += size[i] * remaining;
        }
    }

    return result;
};