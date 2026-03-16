// Source: https://leetcode.com/problems/find-number-of-coins-to-place-in-tree-nodes/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree with n nodes labeled from 0 to n - 1, and rooted at node 0. You are given a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// You are also given a 0-indexed integer array cost of length n, where cost[i] is the cost assigned to the ith node.
//
// You need to place some coins on every node of the tree. The number of coins to be placed at node i can be calculated as:
//
//
// 	If size of the subtree of node i is less than 3, place 1 coin.
// 	Otherwise, place an amount of coins equal to the maximum product of cost values assigned to 3 distinct nodes in the subtree of node i. If this product is negative, place 0 coins.
//
//
// Return an array coin of size n such that coin[i] is the number of coins placed at node i.
//
// Example:
// Input: edges = [[0,1],[0,2],[0,3],[0,4],[0,5]], cost = [1,2,3,4,5,6]
// Output: [120,1,1,1,1,1]
// Explanation: For node 0 place 6 * 5 * 4 = 120 coins. All other nodes are leaves with subtree of size 1, place 1 coin on each of them.
//
// Constraints:
// 2 <= n <= 2 * 104
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	cost.length == n
// 	1 <= |cost[i]| <= 104
// 	The input is generated such that edges represents a valid tree.
//

/**
 * @param {number[][]} edges
 * @param {number[]} cost
 * @return {number[]}
 */
var placedCoins = function(edges, cost) {
    const n = cost.length;
    const graph = Array.from({ length: n }, () => []);
    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }
    const result = new Array(n).fill(0);

    function dfs(node, parent) {
        let subtreeNodes = [node];
        for (const neighbor of graph[node]) {
            if (neighbor !== parent) {
                subtreeNodes = subtreeNodes.concat(dfs(neighbor, node));
            }
        }
        if (subtreeNodes.length < 3) {
            result[node] = 1;
        } else {
            let maxProduct = 0;
            for (let i = 0; i < subtreeNodes.length; i++) {
                for (let j = i + 1; j < subtreeNodes.length; j++) {
                    for (let k = j + 1; k < subtreeNodes.length; k++) {
                        const product = cost[subtreeNodes[i]] * cost[subtreeNodes[j]] * cost[subtreeNodes[k]];
                        maxProduct = Math.max(maxProduct, product);
                    }
                }
            }
            result[node] = maxProduct > 0 ? maxProduct : 0;
        }
        return subtreeNodes;
    }

    dfs(0, -1);
    return result;
};
