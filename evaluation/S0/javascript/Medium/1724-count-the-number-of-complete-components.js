// Source: https://leetcode.com/problems/count-the-number-of-complete-components/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n. There is an undirected graph with n vertices, numbered from 0 to n - 1. You are given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting vertices ai and bi.
//
// Return the number of complete connected components of the graph.
//
// A connected component is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.
//
// A connected component is said to be complete if there exists an edge between every pair of its vertices.
//
// Example:
// Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
// Output: 3
// Explanation: From the picture above, one can see that all of the components of this graph are complete.
//
// Constraints:
// 1 <= n <= 50
// 	0 <= edges.length <= n * (n - 1) / 2
// 	edges[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	There are no repeated edges.
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number}
 */
var countCompleteComponents = function(n, edges) {
    const adjList = Array.from({ length: n }, () => []);
    for (const [u, v] of edges) {
        adjList[u].push(v);
        adjList[v].push(u);
    }
    const visited = new Array(n).fill(false);
    let completeComponents = 0;
    const dfs = (node, component) => {
        visited[node] = true;
        component.nodes.push(node);
        component.edgeCount += adjList[node].length;
        for (const neighbor of adjList[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, component);
            }
        }
    };
    for (let i = 0; i < n; i++) {
        if (!visited[i]) {
            const component = { nodes: [], edgeCount: 0 };
            dfs(i, component);
            const nodeCount = component.nodes.length;
            const expectedEdges = nodeCount * (nodeCount - 1);
            if (component.edgeCount === expectedEdges) {
                completeComponents++;
            }
        }
    }
    return completeComponents;
        
};
