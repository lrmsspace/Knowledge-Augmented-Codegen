// Source: https://leetcode.com/problems/number-of-restricted-paths-from-first-to-last-node/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected weighted connected graph. You are given a positive integer n which denotes that the graph has n nodes labeled from 1 to n, and an array edges where each edges[i] = [ui, vi, weighti] denotes that there is an edge between nodes ui and vi with weight equal to weighti.
//
// A path from node start to node end is a sequence of nodes [z0, z1, z2, ..., zk] such that z0 = start and zk = end and there is an edge between zi and zi+1 where 0 <= i <= k-1.
//
// The distance of a path is the sum of the weights on the edges of the path. Let distanceToLastNode(x) denote the shortest distance of a path between node n and node x. A restricted path is a path that also satisfies that distanceToLastNode(zi) > distanceToLastNode(zi+1) where 0 <= i <= k-1.
//
// Return the number of restricted paths from node 1 to node n. Since that number may be too large, return it modulo 109 + 7.
//
// Example:
// Input: n = 5, edges = [[1,2,3],[1,3,3],[2,3,1],[1,4,2],[5,2,2],[3,5,1],[5,4,10]]
// Output: 3
// Explanation: Each circle contains the node number in black and its distanceToLastNode value in blue. The three restricted paths are:
// 1) 1 --> 2 --> 5
// 2) 1 --> 2 --> 3 --> 5
// 3) 1 --> 3 --> 5
//
// Constraints:
// 1 <= n <= 2 * 104
// 	n - 1 <= edges.length <= 4 * 104
// 	edges[i].length == 3
// 	1 <= ui, vi <= n
// 	ui != vi
// 	1 <= weighti <= 105
// 	There is at most one edge between any two nodes.
// 	There is at least one path between any two nodes.
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number}
 */
var countRestrictedPaths = function(n, edges) {
    const MOD = 1e9 + 7;
    const graph = Array.from({ length: n + 1 }, () => []);
    for (const [u, v, weight] of edges) {
        graph[u].push([v, weight]);
        graph[v].push([u, weight]);
    }
    const distances = Array(n + 1).fill(Infinity);
    distances[n] = 0;
    const minHeap = new MinPriorityQueue({ priority: x => x[1] });
    minHeap.enqueue([n, 0]);
    while (!minHeap.isEmpty()) {
        const [node, dist] = minHeap.dequeue().element;
        if (dist > distances[node]) continue;
        for (const [neighbor, weight] of graph[node]) {
            const newDist = dist + weight;
            if (newDist < distances[neighbor]) {
                distances[neighbor] = newDist;
                minHeap.enqueue([neighbor, newDist]);
            }   
        }
    }
    const memo = Array(n + 1).fill(-1);
    function dfs(node) {
        if (node === n) return 1;
        if (memo[node] !== -1) return memo[node];
        let count = 0;
        for (const [neighbor] of graph[node]) {
            if (distances[node] > distances[neighbor]) {
                count = (count + dfs(neighbor)) % MOD;
            }
        }
        memo[node] = count;
        return count;
    }
    return dfs(1);  
};
