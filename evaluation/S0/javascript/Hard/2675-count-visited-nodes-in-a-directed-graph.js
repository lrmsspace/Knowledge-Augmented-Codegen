// Source: https://leetcode.com/problems/count-visited-nodes-in-a-directed-graph/   |   Difficulty: Hard
//
// Problem Description:
// There is a directed graph consisting of n nodes numbered from 0 to n - 1 and n directed edges.
//
// You are given a 0-indexed array edges where edges[i] indicates that there is an edge from node i to node edges[i].
//
// Consider the following process on the graph:
//
//
// 	You start from a node x and keep visiting other nodes through edges until you reach a node that you have already visited before on this same process.
//
//
// Return an array answer where answer[i] is the number of different nodes that you will visit if you perform the process starting from node i.
//
// Example:
// Input: edges = [1,2,0,0]
// Output: [3,3,3,4]
// Explanation: We perform the process starting from each node in the following way:
// - Starting from node 0, we visit the nodes 0 -> 1 -> 2 -> 0. The number of different nodes we visit is 3.
// - Starting from node 1, we visit the nodes 1 -> 2 -> 0 -> 1. The number of different nodes we visit is 3.
// - Starting from node 2, we visit the nodes 2 -> 0 -> 1 -> 2. The number of different nodes we visit is 3.
// - Starting from node 3, we visit the nodes 3 -> 0 -> 1 -> 2 -> 0. The number of different nodes we visit is 4.
//
// Constraints:
// n == edges.length
// 	2 <= n <= 105
// 	0 <= edges[i] <= n - 1
// 	edges[i] != i
//

/**
 * @param {number[]} edges
 * @return {number[]}
 */
var countVisitedNodes = function(edges) {
    const n = edges.length;
    const answer = Array(n).fill(0);
    const visited = Array(n).fill(false);
    const dfs = (node) => {
        if (visited[node]) {
            return 0;
        }
        visited[node] = true;
        return 1 + dfs(edges[node]);
    }
    for (let i = 0; i < n; i++) {
        if (!visited[i]) {
            const count = dfs(i);
            let j = i;
            while (answer[j] === 0) {
                answer[j] = count;
                j = edges[j];
            }
        }
    }
    return answer;
};
