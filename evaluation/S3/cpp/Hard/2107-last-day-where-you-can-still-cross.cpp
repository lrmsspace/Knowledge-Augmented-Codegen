// Source: https://leetcode.com/problems/last-day-where-you-can-still-cross/   |   Difficulty: Hard
//
// Problem Description:
// There is a 1-based binary matrix where 0 represents land and 1 represents water. You are given integers row and col representing the number of rows and columns in the matrix, respectively.
//
// Initially on day 0, the entire matrix is land. However, each day a new cell becomes flooded with water. You are given a 1-based 2D array cells, where cells[i] = [ri, ci] represents that on the ith day, the cell on the rith row and cith column (1-based coordinates) will be covered with water (i.e., changed to 1).
//
// You want to find the last day that it is possible to walk from the top to the bottom by only walking on land cells. You can start from any cell in the top row and end at any cell in the bottom row. You can only travel in the four cardinal directions (left, right, up, and down).
//
// Return the last day where it is possible to walk from the top to the bottom by only walking on land cells.
//
// Example:
// Input: row = 2, col = 2, cells = [[1,1],[2,1],[1,2],[2,2]]
// Output: 2
// Explanation: The above image depicts how the matrix changes each day starting from day 0.
// The last day where it is possible to cross from top to bottom is on day 2.
//
// Constraints:
// 2 <= row, col <= 2 * 104
// 	4 <= row * col <= 2 * 104
// 	cells.length == row * col
// 	1 <= ri <= row
// 	1 <= ci <= col
// 	All the values of cells are unique.
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
//   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
//   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
//   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
//   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
//   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        typedef struct {
            int u;
            int parent;
            int edgeWeightFromParent;
            int edgeIter;
            int phase;
            int depth;
            int value;
            int prevLastDepth;
            int prevWindowStart;
        } Frame;

        int n = row * col;
        int m = (n - 1) * 2;
        vector<int> head(n, -1);
        vector<int> to(m);
        vector<int> w(m);
        vector<int> next(m);
        vector<int> dist(n);
        vector<Frame> stack(n);
        vector<int> lastDepth(50001, -1);
        vector<int> result(2);
        int idx = 0;
        int top = 0;
        int pathLen = 0;
        int windowStart = 0;
        long long bestLen = -1;
        int bestNodes = 0;

        for (int i = 0; i < n - 1; ++i) {
            int u = (cells[i][0] - 1) * col + (cells[i][1] - 1);
            int v = (cells[i + 1][0] - 1) * col + (cells[i + 1][1] - 1);
            int edgeLen = 1;

            to[idx] = v;
            w[idx] = edgeLen;
            next[idx] = head[u];
            head[u] = idx++;
            to[idx] = u;
            w[idx] = edgeLen;
            next[idx] = head[v];
            head[v] = idx++;
        }

        stack[top].u = 0;
        stack[top].parent = -1;
        stack[top].edgeWeightFromParent = 0;
        stack[top].edgeIter = -1;
        stack[top].phase = 0;
        stack[top].depth = 0;
        stack[top].value = 0;
        stack[top].prevLastDepth = -1;
        stack[top].prevWindowStart = 0;
        ++top;

        while (top > 0) {
            Frame* cur = &stack[top - 1];

            if (cur->phase == 0) {
                cur->phase = 1;

                if (cur->parent == -1) {
                    lastDepth[cur->depth] = idx;
                }
            } else if (cur->phase == 1) {
                int u = cur->u;
                int edgeIter = cur->edgeIter;
                int edgeWeightFromParent = cur->edgeWeightFromParent;

                while (edgeIter != -1) {
                    int v = to[edgeIter];
                    if (v != cur->parent) {
                        stack[top].u = v;
                        stack[top].parent = u;
                        stack[top].edgeWeightFromParent = w[edgeIter];
                        stack[top].edgeIter = head[v];
                        stack[top].phase = 0;
                        stack[top].depth = cur->depth + 1;
                        stack[top].value = cur->value + w[edgeIter];
                        stack[top].prevLastDepth = lastDepth[cur->depth];
                        stack[top].prevWindowStart = windowStart;
                        ++top;
                    }
                    edgeIter = next[edgeIter];
                }

                if (cur->parent != -1) {
                    lastDepth[cur->depth] = idx;
                }
            }
        }
        return bestNodes;
    }
};
