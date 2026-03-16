// Source: https://leetcode.com/problems/modify-graph-edge-weights/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected weighted connected graph containing n nodes labeled from 0 to n - 1, and an integer array edges where edges[i] = [ai, bi, wi] indicates that there is an edge between nodes ai and bi with weight wi.
//
// Some edges have a weight of -1 (wi = -1), while others have a positive weight (wi > 0).
//
// Your task is to modify all edges with a weight of -1 by assigning them positive integer values in the range [1, 2 * 109] so that the shortest distance between the nodes source and destination becomes equal to an integer target. If there are multiple modifications that make the shortest distance between source and destination equal to target, any of them will be considered correct.
//
// Return an array containing all edges (even unmodified ones) in any order if it is possible to make the shortest distance from source to destination equal to target, or an empty array if it's impossible.
//
// Note: You are not allowed to modify the weights of edges with initial positive weights.
//
// Example:
// Input: n = 5, edges = [[4,1,-1],[2,0,-1],[0,3,-1],[4,3,-1]], source = 0, destination = 1, target = 5
// Output: [[4,1,1],[2,0,1],[0,3,3],[4,3,1]]
// Explanation: The graph above shows a possible modification to the edges, making the distance from 0 to 1 equal to 5.
//
// Constraints:
// 1 <= n <= 100
// 	1 <= edges.length <= n * (n - 1) / 2
// 	edges[i].length == 3
// 	0 <= ai, bi < n
// 	wi = -1 or 1 <= wi <= 107
// 	ai != bi
// 	0 <= source, destination < n
// 	source != destination
// 	1 <= target <= 109
// 	The graph is connected, and there are no self-loops or repeated edges
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number} source
 * @param {number} destination
 * @param {number} target
 * @return {number[][]}
 */
var modifiedGraphEdges = function(n, edges, source, destination, target) {
    const graph = Array.from({ length: n }, () => []);
    for (const [u, v, w] of edges) {
        graph[u].push([v, w]);
        graph[v].push([u, w]);
    }
    const dijkstra = (start) => {
        const dist = new Array(n).fill(Infinity);
        dist[start] = 0;
        const pq = [[0, start]];
        while (pq.length > 0) {
            const [d, node] = pq.shift();
            if (d > dist[node]) continue;
            for (const [neighbor, weight] of graph[node]) {
                const newDist = d + (weight === -1 ? 1 : weight);
                if (newDist < dist[neighbor]) {
                    dist[neighbor] = newDist;
                    pq.push([newDist, neighbor]);
                }
            }
        }
        return dist;
    }
    const distFromSource = dijkstra(source);
    const distFromDestination = dijkstra(destination);
    if (distFromSource[destination] > target) return [];
    for (const [u, v, w] of edges) {
        if (w === -1) {
            const newWeight = target - distFromSource[u] - distFromDestination[v];
            if (newWeight > 0) {
                graph[u] = graph[u].map(([neighbor, weight]) => neighbor === v ? [neighbor, newWeight] : [neighbor, weight]);
                graph[v] = graph[v].map(([neighbor, weight]) => neighbor === u ? [neighbor, newWeight] : [neighbor, weight]);
            }
        }
    }
    const finalDistFromSource = dijkstra(source);
    if (finalDistFromSource[destination] !== target) return [];
    return edges.map(([u, v, w]) => {
        if (w === -1) {
            const newWeight = target - distFromSource[u] - distFromDestination[v];
            return [u, v, newWeight > 0 ? newWeight : 1];
        }
        return [u, v, w];
    }
    );
        
};
