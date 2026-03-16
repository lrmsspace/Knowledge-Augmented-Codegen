// Source: https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/   |   Difficulty: Hard
//
// Problem Description:
// Alice and Bob have an undirected graph of n nodes and three types of edges:
//
//
// 	Type 1: Can be traversed by Alice only.
// 	Type 2: Can be traversed by Bob only.
// 	Type 3: Can be traversed by both Alice and Bob.
//
//
// Given an array edges where edges[i] = [typei, ui, vi] represents a bidirectional edge of type typei between nodes ui and vi, find the maximum number of edges you can remove so that after removing the edges, the graph can still be fully traversed by both Alice and Bob. The graph is fully traversed by Alice and Bob if starting from any node, they can reach all other nodes.
//
// Return the maximum number of edges you can remove, or return -1 if Alice and Bob cannot fully traverse the graph.
//
// Example:
// Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
// Output: 2
// Explanation: If we remove the 2 edges [1,1,2] and [1,1,3]. The graph will still be fully traversable by Alice and Bob. Removing any additional edge will not make it so. So the maximum number of edges we can remove is 2.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= edges.length <= min(105, 3 * n * (n - 1) / 2)
// 	edges[i].length == 3
// 	1 <= typei <= 3
// 	1 <= ui < vi <= n
// 	All tuples (typei, ui, vi) are distinct.
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number}
 */
var maxNumEdgesToRemove = function(n, edges) {
    const parentAlice = Array.from({ length: n + 1 }, (_, i) => i);
    const parentBob = Array.from({ length: n + 1 }, (_, i) => i);

    const find = (parent, x) => {
        if (parent[x] !== x) {
            parent[x] = find(parent, parent[x]);
        }
        return parent[x];
    }
    const union = (parent, x, y) => {
        const rootX = find(parent, x);
        const rootY = find(parent, y);
        if (rootX !== rootY) {
            parent[rootY] = rootX;
            return true;
        }
        return false;
    }
    let edgesUsed = 0;

    for (const [type, u, v] of edges) {
        if (type === 3) {
            if (union(parentAlice, u, v) | union(parentBob, u, v)) {
                edgesUsed++;
            }
        }
    }
    for (const [type, u, v] of edges) {
        if (type === 1) {
            if (union(parentAlice, u, v)) {
                edgesUsed++;
            }
        } else if (type === 2) {
            if (union(parentBob, u, v)) {
                edgesUsed++;
            }
        }
    }
    const rootAlice = find(parentAlice, 1);
    const rootBob = find(parentBob, 1);
    for (let i = 2; i <= n; i++) {
        if (find(parentAlice, i) !== rootAlice || find(parentBob, i) !== rootBob) {
            return -1;
        }
    }
    return edges.length - edgesUsed;    
};
