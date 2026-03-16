// Source: https://leetcode.com/problems/path-with-maximum-probability/   |   Difficulty: Medium
//
// Problem Description:
// You are given an undirected weighted graph of n nodes (0-indexed), represented by an edge list where edges[i] = [a, b] is an undirected edge connecting the nodes a and b with a probability of success of traversing that edge succProb[i].
//
// Given two nodes start and end, find the path with the maximum probability of success to go from start to end and return its success probability.
//
// If there is no path from start to end, return 0. Your answer will be accepted if it differs from the correct answer by at most 1e-5.
//
// Example:
// Input: n = 3, edges = [[0,1],[1,2],[0,2]], succProb = [0.5,0.5,0.2], start = 0, end = 2
// Output: 0.25000
// Explanation: There are two paths from start to end, one having a probability of success = 0.2 and the other has 0.5 * 0.5 = 0.25.
//
// Constraints:
// 2 <= n <= 10^4
// 	0 <= start, end < n
// 	start != end
// 	0 <= a, b < n
// 	a != b
// 	0 <= succProb.length == edges.length <= 2*10^4
// 	0 <= succProb[i] <= 1
// 	There is at most one edge between every two nodes.
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @param {number[]} succProb
 * @param {number} start_node
 * @param {number} end_node
 * @return {number}
 */
var maxProbability = function(n, edges, succProb, start_node, end_node) {
    const graph = Array.from({ length: n }, () => []);
    for (let i = 0; i < edges.length; i++) {
        const [a, b] = edges[i];
        const prob = succProb[i];
        graph[a].push([b, prob]);
        graph[b].push([a, prob]);
    }
    const probabilities = Array(n).fill(0);
    probabilities[start_node] = 1;
    const pq = [[start_node, 1]]; // [node, probability]

    while (pq.length > 0) {
        pq.sort((a, b) => b[1] - a[1]);
        const [node, prob] = pq.shift();
        if (node === end_node) return prob;
        if (probabilities[node] > prob) continue;
        for (const [neighbor, edgeProb] of graph[node]) {
            const newProb = prob * edgeProb;
            if (newProb > probabilities[neighbor]) {
                probabilities[neighbor] = newProb;
                pq.push([neighbor, newProb]);
            }
        }
    }
    return 0;
};