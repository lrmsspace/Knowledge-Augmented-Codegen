// Source: https://leetcode.com/problems/find-edges-in-shortest-paths/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected weighted graph of n nodes numbered from 0 to n - 1. The graph consists of m edges represented by a 2D array edges, where edges[i] = [ai, bi, wi] indicates that there is an edge between nodes ai and bi with weight wi.
//
// Consider all the shortest paths from node 0 to node n - 1 in the graph. You need to find a boolean array answer where answer[i] is true if the edge edges[i] is part of at least one shortest path. Otherwise, answer[i] is false.
//
// Return the array answer.
//
// Note that the graph may not be connected.
//
// Example:
// Input: n = 6, edges = [[0,1,4],[0,2,1],[1,3,2],[1,4,3],[1,5,1],[2,3,1],[3,5,3],[4,5,2]]
//
// Output: [true,true,true,false,true,true,true,false]
//
// Explanation:
//
// The following are all the shortest paths between nodes 0 and 5:
//
//
// 	The path 0 -> 1 -> 5: The sum of weights is 4 + 1 = 5.
// 	The path 0 -> 2 -> 3 -> 5: The sum of weights is 1 + 1 + 3 = 5.
// 	The path 0 -> 2 -> 3 -> 1 -> 5: The sum of weights is 1 + 1 + 2 + 1 = 5.
//
// Constraints:
// 2 <= n <= 5 * 104
// 	m == edges.length
// 	1 <= m <= min(5 * 104, n * (n - 1) / 2)
// 	0 <= ai, bi < n
// 	ai != bi
// 	1 <= wi <= 105
// 	There are no repeated edges.
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {boolean[]}
 */
var findAnswer = function(n, edges) {
    const graph = new Array(n).fill(0).map(() => []);
    for (const [u, v, w] of edges) {
        graph[u].push([v, w]);
        graph[v].push([u, w]);
    }
    const dist = new Array(n).fill(Infinity);
    dist[0] = 0;
    const pq = [[0, 0]];
    while (pq.length > 0) {
        const [node, d] = pq.shift();
        if (d > dist[node]) continue;
        for (const [neighbor, weight] of graph[node]) {
            const newDist = d + weight;
            if (newDist < dist[neighbor]) {
                dist[neighbor] = newDist;
                pq.push([neighbor, newDist]);
            }
        }
    }
    const answer = new Array(edges.length).fill(false);     
    for (let i = 0; i < edges.length; i++) {
        const [u, v, w] = edges[i];
        if ((dist[u] + w === dist[v]) || (dist[v] + w === dist[u])) {
            answer[i] = true;
        }
    }
    return answer;  
};
