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
// - Range Minimum Query (array, ds, union-find)
//   • When to use: Use when range minimum queries are needed on an array where elements can be dynamically removed or merged, and Union-Find is employed to manage the active state or connectivity of indices.
//   • Idea: Union-Find can be adapted to assist in range minimum queries, particularly when elements are dynamically removed or merged. It helps maintain connectivity of active elements or segments, allowing efficient traversal to find the minimum among available items, often with near-constant amortized time per Union-Find operation.
//   • Invariants: The `find` operation correctly returns the canonical representative for any element `i`.; Each set in the Union-Find structure maintains a property (e.g., minimum value, next available index) relevant to its merged elements.
//   • Tips: Utilize path compression and union by rank/size for optimal Union-Find performance.; Store relevant properties (e.g., minimum value, next available index) within the representative of each set.
//   • Pitfalls: Union-Find alone does not directly provide range minimums; it typically manages connectivity or availability.; Naive iteration through active elements found by Union-Find can be too slow for large ranges.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
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
        int total = 4 * n * n;
        vector<int> parent(total);
        vector<int> rank(total, 0);
        
        for (int i = 0; i < total; ++i) {
            parent[i] = i;
        }
        
        auto find_set = [&](int v) {
            if (parent[v] != v) {
                parent[v] = find_set(parent[v]);
            }
            return parent[v];
        };
        
        auto union_set = [&](int a, int b) {
            a = find_set(a);
            b = find_set(b);
            if (a != b) {
                if (rank[a] < rank[b]) {
                    parent[a] = b;
                } else if (rank[a] > rank[b]) {
                    parent[b] = a;
                } else {
                    parent[b] = a;
                    rank[a]++;
                }
            }
        };
        
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                int base = 4 * (r * n + c);
                char ch = grid[r][c];
                if (ch == '/') {
                    union_set(base + 0, base + 3);
                    union_set(base + 1, base + 2);
                } else if (ch == '\\') {
                    union_set(base + 0, base + 1);
                    union_set(base + 2, base + 3);
                } else {
                    union_set(base + 0, base + 1);
                    union_set(base + 1, base + 2);
                    union_set(base + 2, base + 3);
                }
                
                // Connect with right cell
                if (c + 1 < n) {
                    int rightBase = 4 * (r * n + (c + 1));
                    union_set(base + 1, rightBase + 3);
                }
                
                // Connect with bottom cell
                if (r + 1 < n) {
                    int bottomBase = 4 * ((r + 1) * n + c);
                    union_set(base + 2, bottomBase + 0);
                }
            }
        }
        
        int regions = 0;
        for (int i = 0; i < total; ++i) {
            if (find_set(i) == i) {
                regions++;
            }
        }
        return regions;   
    }
};
