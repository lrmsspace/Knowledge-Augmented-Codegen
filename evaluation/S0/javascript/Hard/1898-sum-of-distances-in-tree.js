// Source: https://leetcode.com/problems/sum-of-distances-in-tree/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.
//
// You are given the integer n and the array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// Return an array answer of length n where answer[i] is the sum of the distances between the ith node in the tree and all other nodes.
//
// Example:
// Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
// Output: [8,12,6,10,10,10]
// Explanation: The tree is shown above.
// We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
// equals 1 + 1 + 2 + 2 + 2 = 8.
// Hence, answer[0] = 8, and so on.
//
// Constraints:
// 1 <= n <= 3 * 104
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	The given input represents a valid tree.
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number[]}
 */
var sumOfDistancesInTree = function(n, edges) {
    const graph = new Array(n).fill(0).map(() => []);
    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }
    const res = new Array(n).fill(0);
    const count = new Array(n).fill(1);

    const dfs = (node, parent) => {
        for (const neighbor of graph[node]) {
            if (neighbor === parent) continue;
            dfs(neighbor, node);
            count[node] += count[neighbor];
            res[node] += res[neighbor] + count[neighbor];
        }
    };

    const dfs2 = (node, parent) => {
        for (const neighbor of graph[node]) {
            if (neighbor === parent) continue;
            res[neighbor] = res[node] - count[neighbor] + (n - count[neighbor]);
            dfs2(neighbor, node);
        }
    };

    dfs(0, -1);
    dfs2(0, -1);

    return res;
};
