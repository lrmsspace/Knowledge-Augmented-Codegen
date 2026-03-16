// Source: https://leetcode.com/problems/network-delay-time/   |   Difficulty: Medium
//
// Problem Description:
// You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi), where ui is the source node, vi is the target node, and wi is the time it takes for a signal to travel from source to target.
//
// We will send a signal from a given node k. Return the minimum time it takes for all the n nodes to receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.
//
// Example:
// Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
// Output: 2
//
// Constraints:
// 1 <= k <= n <= 100
// 	1 <= times.length <= 6000
// 	times[i].length == 3
// 	1 <= ui, vi <= n
// 	ui != vi
// 	0 <= wi <= 100
// 	All the pairs (ui, vi) are unique. (i.e., no multiple edges.)
//

/**
 * @param {number[][]} times
 * @param {number} n
 * @param {number} k
 * @return {number}
 */
var networkDelayTime = function(times, n, k) {
    const graph = Array.from({ length: n + 1 }, () => []);
    for (const [u, v, w] of times) {
        graph[u].push([v, w]);
    }

    const dist = new Array(n + 1).fill(Infinity);
    dist[k] = 0;

    const visited = new Array(n + 1).fill(false);

    for (let i = 0; i < n; i++) {
        let u = -1;
        for (let j = 1; j <= n; j++) {
            if (!visited[j] && (u === -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        visited[u] = true;

        for (const [v, w] of graph[u]) {
            dist[v] = Math.min(dist[v], dist[u] + w);
        }
    }

    let ans = 0;
    for (let i = 1; i <= n; i++) {
        if (dist[i] === Infinity) {
            return -1;
        }
        ans = Math.max(ans, dist[i]);
    }

    return ans;
};