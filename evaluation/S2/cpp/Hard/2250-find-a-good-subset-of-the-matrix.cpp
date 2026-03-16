// Source: https://leetcode.com/problems/find-a-good-subset-of-the-matrix/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed m x n binary matrix grid.
//
// Let us call a non-empty subset of rows good if the sum of each column of the subset is at most half of the length of the subset.
//
// More formally, if the length of the chosen subset of rows is k, then the sum of each column should be at most floor(k / 2).
//
// Return an integer array that contains row indices of a good subset sorted in ascending order.
//
// If there are multiple good subsets, you can return any of them. If there are no good subsets, return an empty array.
//
// A subset of rows of the matrix grid is any matrix that can be obtained by deleting some (possibly none or all) rows from grid.
//
// Example:
// Input: grid = [[0,1,1,0],[0,0,0,1],[1,1,1,1]]
// Output: [0,1]
// Explanation: We can choose the 0th and 1st rows to create a good subset of rows.
// The length of the chosen subset is 2.
// - The sum of the 0th column is 0 + 0 = 0, which is at most half of the length of the subset.
// - The sum of the 1st column is 1 + 0 = 1, which is at most half of the length of the subset.
// - The sum of the 2nd column is 1 + 0 = 1, which is at most half of the length of the subset.
// - The sum of the 3rd column is 0 + 1 = 1, which is at most half of the length of the subset.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m <= 104
// 	1 <= n <= 5
// 	grid[i][j] is either 0 or 1.
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
//   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
//   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
//   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
//   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
//   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
// - Minimum spanning tree - Prim's algorithm (graph, heap, array, mst-prim, greedy, heap-select)
//   • When to use: Use Prim's algorithm to find a minimum spanning tree in a connected, weighted graph. It is efficient for both dense graphs (O(V^2)) and sparse graphs (O(E log V)) depending on the implementation.
//   • Idea: Prim's algorithm is a greedy algorithm that builds an MST by iteratively adding the cheapest edge connecting a vertex in the growing tree to a vertex outside the tree. It has a time complexity of O(V^2) for dense graphs using an adjacency matrix or O(E log V) for sparse graphs using a priority queue.
//   • Invariants: All selected vertices and edges form a connected component of the final MST.; For any unselected vertex `v`, `min_e[v]` stores the minimum weight of an edge connecting `v` to the currently selected component.
//   • Tips: For dense graphs, an O(V^2) implementation using an an adjacency matrix and simple array scans is efficient.; For sparse graphs, use a priority queue (min-heap) with an adjacency list to achieve O(E log V) complexity.
//   • Pitfalls: Incorrectly updating the `min_e` array or priority queue entries can lead to an incorrect MST or performance issues.; Forgetting to mark vertices as 'selected' can lead to cycles or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> goodSubsetofBinaryMatrix(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> count(1 << n, 0);
        for (int i = 0; i < m; ++i) {
            int mask = 0;
            for (int j = 0; j < n; ++j) {
                mask |= grid[i][j] << j;
            }
            count[mask]++;
        }
        for (int i = 0; i < (1 << n); ++i) {
            if (count[i] > 0 && count[(1 << n) - 1 - i] > 0) {
                return {i, (1 << n) - 1 - i};
            }
        }
        for (int i = 0; i < (1 << n); ++i) {
            if (count[i] > 1 && (i & (i - 1)) == 0) {
                return {i, i};
            }
        }
        return {};          
    }
};
