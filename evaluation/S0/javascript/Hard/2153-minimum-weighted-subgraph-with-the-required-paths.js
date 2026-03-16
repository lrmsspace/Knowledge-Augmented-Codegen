// Source: https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n denoting the number of nodes of a weighted directed graph. The nodes are numbered from 0 to n - 1.
//
// You are also given a 2D integer array edges where edges[i] = [fromi, toi, weighti] denotes that there exists a directed edge from fromi to toi with weight weighti.
//
// Lastly, you are given three distinct integers src1, src2, and dest denoting three distinct nodes of the graph.
//
// Return the minimum weight of a subgraph of the graph such that it is possible to reach dest from both src1 and src2 via a set of edges of this subgraph. In case such a subgraph does not exist, return -1.
//
// A subgraph is a graph whose vertices and edges are subsets of the original graph. The weight of a subgraph is the sum of weights of its constituent edges.
//
// Example:
// Input: n = 6, edges = [[0,2,2],[0,5,6],[1,0,3],[1,4,5],[2,1,1],[2,3,3],[2,3,4],[3,4,2],[4,5,1]], src1 = 0, src2 = 1, dest = 5
// Output: 9
// Explanation:
// The above figure represents the input graph.
// The blue edges represent one of the subgraphs that yield the optimal answer.
// Note that the subgraph [[1,0,3],[0,5,6]] also yields the optimal answer. It is not possible to get a subgraph with less weight satisfying all the constraints.
//
// Constraints:
// 3 <= n <= 105
// 	0 <= edges.length <= 105
// 	edges[i].length == 3
// 	0 <= fromi, toi, src1, src2, dest <= n - 1
// 	fromi != toi
// 	src1, src2, and dest are pairwise distinct.
// 	1 <= weight[i] <= 105
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number} src1
 * @param {number} src2
 * @param {number} dest
 * @return {number}
 */
var minimumWeight = function(n, edges, src1, src2, dest) {
    const graph = new Map();        
    const reverseGraph = new Map();
    for (const [from, to, weight] of edges) {
        if (!graph.has(from)) {
            graph.set(from, []);
        }
        graph.get(from).push([to, weight]);
        if (!reverseGraph.has(to)) {
            reverseGraph.set(to, []);
        }
        reverseGraph.get(to).push([from, weight]);
    } 
    const dijkstra = (start, graph) => {
        const distances = new Array(n).fill(Infinity);
        distances[start] = 0;
        const minHeap = [[0, start]];
        while (minHeap.length > 0) {
            const [currentDistance, node] = minHeap.shift();
            if (currentDistance > distances[node]) {
                continue;
            }
            if (graph.has(node)) {
                for (const [neighbor, weight] of graph.get(node)) {
                    const distance = currentDistance + weight;
                    if (distance < distances[neighbor]) {
                        distances[neighbor] = distance;
                        minHeap.push([distance, neighbor]);
                    }
                }
            }
        }
        return distances;
    }
    const distFromSrc1 = dijkstra(src1, graph);
    const distFromSrc2 = dijkstra(src2, graph);
    const distToDest = dijkstra(dest, reverseGraph);
    let minWeight = Infinity;
    for (let i = 0; i < n; i++) {
        if (distFromSrc1[i] !== Infinity && distFromSrc2[i] !== Infinity && distToDest[i] !== Infinity) {
            minWeight = Math.min(minWeight, distFromSrc1[i] + distFromSrc2[i] + distToDest[i]);
        }
    }
    return minWeight === Infinity ? -1 : minWeight;
};
