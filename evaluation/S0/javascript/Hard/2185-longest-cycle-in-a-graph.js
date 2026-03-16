// Source: https://leetcode.com/problems/longest-cycle-in-a-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given a directed graph of n nodes numbered from 0 to n - 1, where each node has at most one outgoing edge.
//
// The graph is represented with a given 0-indexed array edges of size n, indicating that there is a directed edge from node i to node edges[i]. If there is no outgoing edge from node i, then edges[i] == -1.
//
// Return the length of the longest cycle in the graph. If no cycle exists, return -1.
//
// A cycle is a path that starts and ends at the same node.
//
// Example:
// Input: edges = [3,3,4,2,3]
// Output: 3
// Explanation: The longest cycle in the graph is the cycle: 2 -> 4 -> 3 -> 2.
// The length of this cycle is 3, so 3 is returned.
//
// Constraints:
// n == edges.length
// 	2 <= n <= 105
// 	-1 <= edges[i] < n
// 	edges[i] != i
//

/**
 * @param {number[]} edges
 * @return {number}
 */
var longestCycle = function(edges) {
    const n = edges.length;
    const visited = new Array(n).fill(false);
    const inStack = new Array(n).fill(false);
    let longest = -1;
    const dfs = (node, depth) => {
        visited[node] = true;
        inStack[node] = true;
        const next = edges[node];
        if (next !== -1) {
            if (!visited[next]) {
                dfs(next, depth + 1);
            } else if (inStack[next]) {
                longest = Math.max(longest, depth - visited.indexOf(next) + 1);
            }
        }        inStack[node] = false;
    }
    for (let i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, 0);
        }
    }
    return longest; 
};
