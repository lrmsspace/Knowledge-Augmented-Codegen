// Source: https://leetcode.com/problems/number-of-ways-to-reconstruct-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array pairs, where pairs[i] = [xi, yi], and:
//
//
// 	There are no duplicates.
// 	xi < yi
//
//
// Let ways be the number of rooted trees that satisfy the following conditions:
//
//
// 	The tree consists of nodes whose values appeared in pairs.
// 	A pair [xi, yi] exists in pairs if and only if xi is an ancestor of yi or yi is an ancestor of xi.
// 	Note: the tree does not have to be a binary tree.
//
//
// Two ways are considered to be different if there is at least one node that has different parents in both ways.
//
// Return:
//
//
// 	0 if ways == 0
// 	1 if ways == 1
// 	2 if ways > 1
//
//
// A rooted tree is a tree that has a single root node, and all edges are oriented to be outgoing from the root.
//
// An ancestor of a node is any node on the path from the root to that node (excluding the node itself). The root has no ancestors.
//
// Example:
// Input: pairs = [[1,2],[2,3]]
// Output: 1
// Explanation: There is exactly one valid rooted tree, which is shown in the above figure.
//
// Constraints:
// 1 <= pairs.length <= 105
// 	1 <= xi < yi <= 500
// 	The elements in pairs are unique.
//

/**
 * @param {number[][]} pairs
 * @return {number}
 */
var checkWays = function(pairs) {
    const graph = {};
    for (const [u, v] of pairs) {
        if (!graph[u]) graph[u] = new Set();
        if (!graph[v]) graph[v] = new Set();
        graph[u].add(v);
        graph[v].add(u);
    }
    const nodes = Object.keys(graph);
    let root = -1;
    for (const node of nodes) {
        if (graph[node].size === nodes.length - 1) {
            root = node;
            break;
        }
    }
    if (root === -1) return 0;

    let ways = 1;
    for (const node of nodes) {
        if (node == root) continue;
        const neighbors = graph[node];
        let parent = -1;
        let parentDegree = Infinity;
        for (const neighbor of neighbors) {
            if (graph[neighbor].size >= graph[node].size && graph[neighbor].size < parentDegree) {
                parent = neighbor;
                parentDegree = graph[neighbor].size;
            }
        }
        if (parent === -1) return 0;
        for (const neighbor of neighbors) {
            if (neighbor !== parent && !graph[parent].has(neighbor)) {
                return 0;
            }
        }
        if (parentDegree === graph[node].size) {
            ways = 2;
        }
    }
    return ways;
};
