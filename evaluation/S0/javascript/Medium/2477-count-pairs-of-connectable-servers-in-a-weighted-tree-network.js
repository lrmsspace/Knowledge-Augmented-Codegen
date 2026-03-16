// Source: https://leetcode.com/problems/count-pairs-of-connectable-servers-in-a-weighted-tree-network/   |   Difficulty: Medium
//
// Problem Description:
// You are given an unrooted weighted tree with n vertices representing servers numbered from 0 to n - 1, an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional edge between vertices ai and bi of weight weighti. You are also given an integer signalSpeed.
//
// Two servers a and b are connectable through a server c if:
//
//
// 	a < b, a != c and b != c.
// 	The distance from c to a is divisible by signalSpeed.
// 	The distance from c to b is divisible by signalSpeed.
// 	The path from c to b and the path from c to a do not share any edges.
//
//
// Return an integer array count of length n where count[i] is the number of server pairs that are connectable through the server i.
//
// Example:
// Input: edges = [[0,1,1],[1,2,5],[2,3,13],[3,4,9],[4,5,2]], signalSpeed = 1
// Output: [0,4,6,6,4,0]
// Explanation: Since signalSpeed is 1, count[c] is equal to the number of pairs of paths that start at c and do not share any edges.
// In the case of the given path graph, count[c] is equal to the number of servers to the left of c multiplied by the servers to the right of c.
//
// Constraints:
// 2 <= n <= 1000
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= ai, bi < n
// 	edges[i] = [ai, bi, weighti]
// 	1 <= weighti <= 106
// 	1 <= signalSpeed <= 106
// 	The input is generated such that edges represents a valid tree.
//

/**
 * @param {number[][]} edges
 * @param {number} signalSpeed
 * @return {number[]}
 */
var countPairsOfConnectableServers = function(edges, signalSpeed) {
    const n = edges.length + 1;
    const graph = Array.from({ length: n }, () => []);
    for (const [a, b, weight] of edges) {
        graph[a].push([b, weight]);
        graph[b].push([a, weight]);
    }
    const count = new Array(n).fill(0);
    // Further implementation needed here
    return count;
};