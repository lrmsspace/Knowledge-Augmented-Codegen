// Source: https://leetcode.com/problems/regions-cut-by-slashes/   |   Difficulty: Medium
//
// Problem Description:
// An n x n grid is composed of 1 x 1 squares where each 1 x 1 square consists of a '/', '\', or blank space ' '. These characters divide the square into contiguous regions.
//
// Given the grid grid represented as a string array, return the number of regions.
//
// Note that backslash characters are escaped, so a '\' is represented as '\\'.
//
// Example:
// Input: grid = [" /","/ "]
// Output: 2
//
// Constraints:
// n == grid.length == grid[i].length
// 	1 <= n <= 30
// 	grid[i][j] is either '/', '\', or ' '.
//
// Helpful references (internal KB):
// - Disjoint Set Union (ds, tree, array, union-find)
//   • When to use: Use when you need to maintain a collection of disjoint sets and efficiently perform union operations to merge sets or find the representative of an element's set.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. With path compression and union by rank/size, these operations achieve nearly constant amortized time complexity, O(alpha(N)).
//   • Invariants: Each element `v` is either a root (parent[v] == v) or has a parent pointer to another element in its set.; The `find_set` operation, after path compression, ensures that all nodes on the path from `v` to its root directly point to the root.
//   • Tips: Implement path compression in `find_set` for optimal performance.; Use union by rank or union by size to keep trees flat and balanced.
//   • Pitfalls: Forgetting path compression or union by rank/size leads to O(N) worst-case operations.; Incorrectly merging sets by only updating one root without considering the other's rank/size.
// - Disjoint Set Union (ds, linked-list, union-find, dfs)
//   • When to use: Use when you need to maintain a collection of disjoint sets and perform union operations to merge sets or find the representative of an element's set efficiently. It's suitable for problems involving dynamic connectivity or grouping elements.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. It achieves nearly constant time complexity for these operations with path compression and union by rank/size optimizations.
//   • Invariants: Every element `i` belongs to exactly one set, represented by `find(i)`.; If `parent[i] == i`, then `i` is the representative (root) of its set.
//   • Tips: Implement path compression in `find` for optimal performance.; Use union by size or rank to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size can degrade performance to O(N).; Failing to correctly update auxiliary data stored at representatives during a union operation.
// - Disjoint Set Union (ds, tree, array, union-find)
//   • When to use: Use when you need to efficiently manage a collection of disjoint sets, supporting operations to merge sets and determine if two elements belong to the same set.
//   • Idea: Disjoint Set Union (DSU) is a data structure that maintains a collection of disjoint sets and supports two primary operations: union (merging two sets) and find (determining the representative of an element's set). With path compression and union by rank/size, operations achieve nearly O(1) amortized time complexity.
//   • Invariants: For any element `v`, `parent[v]` is either `v` itself (if `v` is a root) or an ancestor of `v`.; All elements belonging to the same set share a common root representative.
//   • Tips: Apply path compression during `find_set` to optimize future queries.; Utilize union by rank or size to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size results in poor performance.; Failing to correctly identify the root of a set in `find_set`.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int regionsBySlashes(vector<string>& grid) {
        int n = grid.size();
        vector<vector<int>> parent(4 * n * n);
        for (int i = 0; i < 4 * n * n; ++i) {
            parent[i] = {i, 1}; // {parent, size}
        }

        function<int(int)> find_set = [&](int v) {
            if (parent[v][0] != v) {
                parent[v][0] = find_set(parent[v][0]);
            }
            return parent[v][0];
        };

        auto union_set = [&](int a, int b) {
            a = find_set(a);
            b = find_set(b);
            if (a != b) {
                if (parent[a][1] < parent[b][1]) {
                    swap(a, b);
                }
                parent[b][0] = a;
                parent[a][1] += parent[b][1];
            }
        };

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int root = 4 * (i * n + j);
                char c = grid[i][j];
                if (c == ' ') {
                    union_set(root, root + 1);
                    union_set(root + 1, root + 2);
                    union_set(root + 2, root + 3);
                } else if (c == '/') {
                    union_set(root, root + 3);
                    union_set(root + 1, root + 2);
                } else if (c == '\\') {
                    union_set(root, root + 1);
                    union_set(root + 2, root + 3);
                }
                if (i > 0) {
                    union_set(root - 4 * n + 2, root + 0); // top
                }
                if (j > 0) {
                    union_set(root - 4 + 1, root + 1); // left
                }
            }
        }

        int regions = 0;
        for (int i = 0; i < 4 * n * n; ++i) {
            if (parent[i][0] == i) {
                ++regions;
            }
        }
        return regions;         
    }
};
