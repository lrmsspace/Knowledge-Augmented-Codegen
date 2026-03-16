// Source: https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected graph (the "original graph") with n nodes labeled from 0 to n - 1. You decide to subdivide each edge in the graph into a chain of nodes, with the number of new nodes varying between each edge.
//
// The graph is given as a 2D array of edges where edges[i] = [ui, vi, cnti] indicates that there is an edge between nodes ui and vi in the original graph, and cnti is the total number of new nodes that you will subdivide the edge into. Note that cnti == 0 means you will not subdivide the edge.
//
// To subdivide the edge [ui, vi], replace it with (cnti + 1) new edges and cnti new nodes. The new nodes are x1, x2, ..., xcnti, and the new edges are [ui, x1], [x1, x2], [x2, x3], ..., [xcnti-1, xcnti], [xcnti, vi].
//
// In this new graph, you want to know how many nodes are reachable from the node 0, where a node is reachable if the distance is maxMoves or less.
//
// Given the original graph and maxMoves, return the number of nodes that are reachable from node 0 in the new graph.
//
// Example:
// Input: edges = [[0,1,10],[0,2,1],[1,2,2]], maxMoves = 6, n = 3
// Output: 13
// Explanation: The edge subdivisions are shown in the image above.
// The nodes that are reachable are highlighted in yellow.
//
// Constraints:
// 0 <= edges.length <= min(n * (n - 1) / 2, 104)
// 	edges[i].length == 3
// 	0 <= ui < vi < n
// 	There are no multiple edges in the graph.
// 	0 <= cnti <= 104
// 	0 <= maxMoves <= 109
// 	1 <= n <= 3000
//

/**
 * @param {number[][]} edges
 * @param {number} maxMoves
 * @param {number} n
 * @return {number}
 */
var reachableNodes = function(edges, maxMoves, n) {
    const graph = Array.from({ length: n }, () => []);
    for (const [u, v, cnt] of edges) {
        graph[u].push([v, cnt]);
        graph[v].push([u, cnt]);
    }
    const minHeap = [[0, 0]]; // [distance, node]
    const visited = new Map();
    let reachableCount = 0;

    while (minHeap.length > 0) {
        const [dist, node] = minHeap.shift();
        if (visited.has(node)) continue;
        visited.set(node, dist);
        reachableCount++;
        for (const [neighbor, cnt] of graph[node]) {    
            const newDist = dist + cnt + 1;
            if (newDist <= maxMoves && !visited.has(neighbor)) {
                minHeap.push([newDist, neighbor]);
                minHeap.sort((a, b) => a[0] - b[0]); // Sort by distance
            }
        }
    }
    for (const [u, v, cnt] of edges) {
        const distU = visited.get(u) || 0;
        const distV = visited.get(v) || 0;
        reachableCount += Math.min(cnt, Math.max(0, maxMoves - distU)) + Math.min(cnt, Math.max(0, maxMoves - distV));
    }
    return reachableCount;  
};
