// Source: https://leetcode.com/problems/divide-nodes-into-the-maximum-number-of-groups/   |   Difficulty: Hard
//
// Problem Description:
// You are given a positive integer n representing the number of nodes in an undirected graph. The nodes are labeled from 1 to n.
//
// You are also given a 2D integer array edges, where edges[i] = [ai, bi] indicates that there is a bidirectional edge between nodes ai and bi. Notice that the given graph may be disconnected.
//
// Divide the nodes of the graph into m groups (1-indexed) such that:
//
//
// 	Each node in the graph belongs to exactly one group.
// 	For every pair of nodes in the graph that are connected by an edge [ai, bi], if ai belongs to the group with index x, and bi belongs to the group with index y, then |y - x| = 1.
//
//
// Return the maximum number of groups (i.e., maximum m) into which you can divide the nodes. Return -1 if it is impossible to group the nodes with the given conditions.
//
// Example:
// Input: n = 6, edges = [[1,2],[1,4],[1,5],[2,6],[2,3],[4,6]]
// Output: 4
// Explanation: As shown in the image we:
// - Add node 5 to the first group.
// - Add node 1 to the second group.
// - Add nodes 2 and 4 to the third group.
// - Add nodes 3 and 6 to the fourth group.
// We can see that every edge is satisfied.
// It can be shown that that if we create a fifth group and move any node from the third or fourth group to it, at least on of the edges will not be satisfied.
//
// Constraints:
// 1 <= n <= 500
// 	1 <= edges.length <= 104
// 	edges[i].length == 2
// 	1 <= ai, bi <= n
// 	ai != bi
// 	There is at most one edge between any pair of vertices.
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number}
 */
var magnificentSets = function(n, edges) {
    const graph = Array.from({ length: n + 1 }, () => []);
    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }
    const visited = new Array(n + 1).fill(false);
    const bfs = (start) => {
        const queue = [start];
        const level = new Array(n + 1).fill(0);
        visited[start] = true;
        let maxLevel = 0;
        while (queue.length > 0) {
            const node = queue.shift();
            for (const neighbor of graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    level[neighbor] = level[node] + 1;
                    maxLevel = Math.max(maxLevel, level[neighbor]);
                    queue.push(neighbor);
                } else if (Math.abs(level[neighbor] - level[node]) !== 1) {
                    return -1; 
                }
            }
        }   
        return maxLevel + 1;
    }
    let result = 0;
    for (let i = 1; i <= n; i++) {
        if (!visited[i]) {
            const groups = bfs(i);
            if (groups === -1) {
                return -1;
            }
            result += groups;
        }
    }
    return result;
};
