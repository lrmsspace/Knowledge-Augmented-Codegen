// Source: https://leetcode.com/problems/add-edges-to-make-degrees-of-all-nodes-even/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected graph consisting of n nodes numbered from 1 to n. You are given the integer n and a 2D array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi. The graph can be disconnected.
//
// You can add at most two additional edges (possibly none) to this graph so that there are no repeated edges and no self-loops.
//
// Return true if it is possible to make the degree of each node in the graph even, otherwise return false.
//
// The degree of a node is the number of edges connected to it.
//
// Example:
// Input: n = 5, edges = [[1,2],[2,3],[3,4],[4,2],[1,4],[2,5]]
// Output: true
// Explanation: The above diagram shows a valid way of adding an edge.
// Every node in the resulting graph is connected to an even number of edges.
//
// Constraints:
// 3 <= n <= 105
// 	2 <= edges.length <= 105
// 	edges[i].length == 2
// 	1 <= ai, bi <= n
// 	ai != bi
// 	There are no repeated edges.
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {boolean}
 */
var isPossible = function(n, edges) {
    const degree = new Array(n + 1).fill(0);
    for (const [u, v] of edges) {
        degree[u]++;
        degree[v]++;
    }
    const oddNodes = [];
    for (let i = 1; i <= n; i++) {
        if (degree[i] % 2 !== 0) {
            oddNodes.push(i);
        }
    }
    if (oddNodes.length === 0) {
        return true;
    }
    if (oddNodes.length > 4 || oddNodes.length % 2 !== 0) {
        return false;
    }
    if (oddNodes.length === 2) {
        const [a, b] = oddNodes;
        if (!edges.some(([u, v]) => (u === a && v === b) || (u === b && v === a))) {
            return true;
        }
        for (let i = 1; i <= n; i++) {
            if (i !== a && i !== b) {
                if (!edges.some(([u, v]) => (u === a && v === i) || (u === i && v === a)) &&
                    !edges.some(([u, v]) => (u === b && v === i) || (u === i && v === b))) {
                    return true;
                }
            }
        }
        return false;
    }
    if (oddNodes.length === 4) {
        const [a, b, c, d] = oddNodes;
        const pairs = [
            [[a, b], [c, d]],
            [[a, c], [b, d]],
            [[a, d], [b, c]]
        ];
        for (const [[x1, y1], [x2, y2]] of pairs) {
            if (!edges.some(([u, v]) => (u === x1 && v === y1) || (u === y1 && v === x1)) &&
                !edges.some(([u, v]) => (u === x2 && v === y2) || (u === y2 && v === x2))) {
                return true;
            }
        }
        return false;
    }
    return false;
};
