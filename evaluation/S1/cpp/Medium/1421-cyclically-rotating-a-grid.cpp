// Source: https://leetcode.com/problems/cyclically-rotating-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix grid​​​, where m and n are both even integers, and an integer k.
//
// The matrix is composed of several layers, which is shown in the below image, where each color is its own layer:
//
//
//
// A cyclic rotation of the matrix is done by cyclically rotating each layer in the matrix. To cyclically rotate a layer once, each element in the layer will take the place of the adjacent element in the counter-clockwise direction. An example rotation is shown below:
//
// Return the matrix after applying k cyclic rotations to it.
//
// Example:
// Input: grid = [[40,10],[30,20]], k = 1
// Output: [[10,20],[40,30]]
// Explanation: The figures above represent the grid at every state.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 50
// 	Both m and n are even integers.
// 	1 <= grid[i][j] <= 5000
// 	1 <= k <= 109
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Finding the rank of a matrix (matrix, simulation, enumeration)
//   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
//   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
//   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
//   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
//   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {

public:

    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {

        
        int m = grid.size();
        int n = grid[0].size();
        int layers = min(m, n) / 2;
        vector<vector<int>> res = grid;

        for (int layer = 0; layer < layers; ++layer) {
            int top = layer;
            int bottom = m - layer - 1;
            int left = layer;
            int right = n - layer - 1;

            // Extract the elements of the current layer
            vector<int> elements;
            for (int j = left; j <= right; ++j) elements.push_back(grid[top][j]);
            for (int i = top + 1; i <= bottom; ++i) elements.push_back(grid[i][right]);
            for (int j = right - 1; j >= left; --j) elements.push_back(grid[bottom][j]);
            for (int i = bottom - 1; i > top; --i) elements.push_back(grid[i][left]);

            int len = elements.size();
            int rot = k % len;

            // Rotate the elements
            vector<int> rotated(len);
            for (int i = 0; i < len; ++i) {
                rotated[(i + rot) % len] = elements[i];
            }

            // Place rotated elements back into the result grid
            int idx = 0;
            for (int j = left; j <= right; ++j) res[top][j] = rotated[idx++];
            for (int i = top + 1; i <= bottom; ++i) res[i][right] = rotated[idx++];
            for (int j = right - 1; j >= left; --j) res[bottom][j] = rotated[idx++];
            for (int i = bottom - 1; i > top; --i) res[i][left] = rotated[idx++];
        }

        return res;
    }

};
