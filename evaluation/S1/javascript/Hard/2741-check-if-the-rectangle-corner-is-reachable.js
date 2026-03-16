// Source: https://leetcode.com/problems/check-if-the-rectangle-corner-is-reachable/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers xCorner and yCorner, and a 2D array circles, where circles[i] = [xi, yi, ri] denotes a circle with center at (xi, yi) and radius ri.
//
// There is a rectangle in the coordinate plane with its bottom left corner at the origin and top right corner at the coordinate (xCorner, yCorner). You need to check whether there is a path from the bottom left corner to the top right corner such that the entire path lies inside the rectangle, does not touch or lie inside any circle, and touches the rectangle only at the two corners.
//
// Return true if such a path exists, and false otherwise.
//
// Example:
// Input: xCorner = 3, yCorner = 4, circles = [[2,1,1]]
//
// Output: true
//
// Explanation:
//
//
//
// The black curve shows a possible path between (0, 0) and (3, 4).
//
// Constraints:
// 3 <= xCorner, yCorner <= 109
// 	1 <= circles.length <= 1000
// 	circles[i].length == 3
// 	1 <= xi, yi, ri <= 109
//
// Helpful references (internal KB):
// - Disjoint Set Union (ds, tree, array, union-find)
//   • When to use: Use when you need to maintain a collection of disjoint sets and efficiently perform union operations to merge sets or find the representative of an element's set.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. With path compression and union by rank/size, these operations achieve nearly constant amortized time complexity, O(alpha(N)).
//   • Invariants: Each element `v` is either a root (parent[v] == v) or has a parent pointer to another element in its set.; The `find_set` operation, after path compression, ensures that all nodes on the path from `v` to its root directly point to the root.
//   • Tips: Implement path compression in `find_set` for optimal performance.; Use union by rank or union by size to keep trees flat and balanced.
//   • Pitfalls: Forgetting path compression or union by rank/size leads to O(N) worst-case operations.; Incorrectly merging sets by only updating one root without considering the other's rank/size.
// - Circle-Circle Intersection (geometry, number, simulation, enumeration)
//   • When to use: Use this algorithm to find the common points where two circles intersect on a 2D plane, handling cases from no intersection to infinite points.
//   • Idea: This algorithm determines the intersection points of two circles by algebraically transforming their equations into a system involving one circle and one line. It typically achieves O(1) time complexity for finding the intersection points.
//   • Invariants: The relative positions and radii of the circles remain unchanged after coordinate translation.; The derived linear equation represents the radical axis of the two circles.
//   • Tips: Translate one circle to the origin to simplify the equations.; Subtract the two circle equations to derive a linear equation (the radical axis).
//   • Pitfalls: Numerical instability due to floating-point arithmetic, especially for tangent cases.; Forgetting to translate the resulting intersection points back to the original coordinate system.
// - Search for connected components in a graph (graph, dfs, bfs, enumeration)
//   • When to use: Use when you need to partition an undirected graph into maximal connected subgraphs where every node is reachable from every other node within its subgraph.
//   • Idea: This algorithm identifies all connected components in an undirected graph by iteratively performing graph traversals (DFS or BFS) from unvisited nodes. It has a time complexity of O(V + E) for adjacency list representation.
//   • Invariants: All nodes visited so far belong to an identified connected component.; Any node currently being visited is part of the current connected component being explored.
//   • Tips: Maintain a visited array or set to track processed nodes.; Iterate through all nodes, starting a new traversal if a node is unvisited.
//   • Pitfalls: Failing to iterate through all nodes to find all components in a disconnected graph.; Not correctly marking nodes as visited during traversal, leading to infinite loops or re-processing.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} xCorner
 * @param {number} yCorner
 * @param {number[][]} circles
 * @return {boolean}
 */
var canReachCorner = function(xCorner, yCorner, circles) {
    const n = circles.length;
    const graph = Array.from({ length: n }, () => []);
    let startComponent = -1;
    let endComponent = -1;

    for (let i = 0; i < n; i++) {
        const [xi, yi, ri] = circles[i];
        if (isInCircle(0, 0, xi, yi, ri)) {
            startComponent = i;
        }
        if (isInCircle(xCorner, yCorner, xi, yi, ri)) {
            endComponent = i;
        }
        for (let j = i + 1; j < n; j++) {
            const [xj, yj, rj] = circles[j];
            if (areCirclesIntersecting(xi, yi, ri, xj, yj, rj)) {
                graph[i].push(j);
                graph[j].push(i);
            }
        }
    }

    if (startComponent === -1 || endComponent === -1) {
        return true;
    }

    const visited = new Array(n).fill(false);
    const queue = [startComponent];
    visited[startComponent] = true;

    while (queue.length > 0) {
        const current = queue.shift();
        if (current === endComponent) {
            return false;
        }
        for (const neighbor of graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue.push(neighbor);
            }
        }
    }

    return true;

    function isInCircle(x, y, cx, cy, r) {
        return (x - cx) ** 2 + (y - cy) ** 2 < r ** 2;
    }

    function areCirclesIntersecting(x1, y1, r1, x2, y2, r2) {
        const distanceSquared = (x1 - x2) ** 2 + (y1 - y2) ** 2;
        const radiusSumSquared = (r1 + r2) ** 2;
        const radiusDiffSquared = Math.abs(r1 - r2) ** 2;
        return distanceSquared < radiusSumSquared && distanceSquared > radiusDiffSquared;
    }
};
