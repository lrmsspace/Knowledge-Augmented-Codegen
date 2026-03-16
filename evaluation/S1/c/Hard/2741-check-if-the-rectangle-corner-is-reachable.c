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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool canReachCorner(int xCorner, int yCorner, int** circles, int circlesSize, int* circlesColSize) {
    typedef struct DSU {
        int *parent;
        int *rank;
        int size;
    } DSU;

    DSU* dsuCreate(int n) {
        DSU* dsu = (DSU*)malloc(sizeof(DSU));
        dsu->parent = (int*)malloc(n * sizeof(int));
        dsu->rank = (int*)calloc(n, sizeof(int));
        dsu->size = n;
        for (int i = 0; i < n; i++) {
            dsu->parent[i] = i;
        }
        return dsu;
    }

    int dsuFind(DSU* dsu, int x) {
        if (dsu->parent[x] != x) {
            dsu->parent[x] = dsuFind(dsu, dsu->parent[x]);
        }
        return dsu->parent[x];
    }

    void dsuUnion(DSU* dsu, int x, int y) {
        int rootX = dsuFind(dsu, x);
        int rootY = dsuFind(dsu, y);
        if (rootX != rootY) {
            if (dsu->rank[rootX] > dsu->rank[rootY]) {
                dsu->parent[rootY] = rootX;
            } else if (dsu->rank[rootX] < dsu->rank[rootY]) {
                dsu->parent[rootX] = rootY;
            } else {
                dsu->parent[rootY] = rootX;
                dsu->rank[rootX]++;
            }
        }
    }

    void dsuFree(DSU* dsu) {
        free(dsu->parent);
        free(dsu->rank);
        free(dsu);
    }

    int n = circlesSize;
    DSU* dsu = dsuCreate(n + 2); // extra two for corners

    for (int i = 0; i < n; i++) {
        int x1 = circles[i][0];
        int y1 = circles[i][1];
        int r1 = circles[i][2];

        // Check if circle touches bottom-left corner
        if ((long long)x1 * x1 + (long long)y1 * y1 <= (long long)r1 * r1) {
            dsuUnion(dsu, i, n); // connect to bottom-left corner
        }

        // Check if circle touches top-right corner
        if ((long long)(x1 - xCorner) * (x1 - xCorner) + (long long)(y1 - yCorner) * (y1 - yCorner) <= (long long)r1 * r1) {
            dsuUnion(dsu, i, n + 1); // connect to top-right corner
        }

        // Check for circle-circle intersections
        for (int j = i + 1; j < n; j++) {
            int x2 = circles[j][0];
            int y2 = circles[j][1];
            int r2 = circles[j][2];

            long long dx = x2 - x1;
            long long dy = y2 - y1;
            long long distSq = dx * dx + dy * dy;
            long long rSum = r1 + r2;
            long long rDiff = r1 > r2 ? r1 - r2 : r2 - r1;

            if (distSq <= (long long)rSum * rSum && distSq >= (long long)rDiff * rDiff) {
                dsuUnion(dsu, i, j);
            }
        }
    }
    bool canReach = dsuFind(dsu, n) != dsuFind(dsu, n + 1);
    dsuFree(dsu);
    return canReach;
}
