// Source: https://leetcode.com/problems/strange-printer-ii/   |   Difficulty: Hard
//
// Problem Description:
// There is a strange printer with the following two special requirements:
//
//
// 	On each turn, the printer will print a solid rectangular pattern of a single color on the grid. This will cover up the existing colors in the rectangle.
// 	Once the printer has used a color for the above operation, the same color cannot be used again.
//
//
// You are given a m x n matrix targetGrid, where targetGrid[row][col] is the color in the position (row, col) of the grid.
//
// Return true if it is possible to print the matrix targetGrid, otherwise, return false.
//
// Example:
// Input: targetGrid = [[1,1,1,1],[1,2,2,1],[1,2,2,1],[1,1,1,1]]
// Output: true
//
// Constraints:
// m == targetGrid.length
// 	n == targetGrid[i].length
// 	1 <= m, n <= 60
// 	1 <= targetGrid[row][col] <= 60
//
// Helpful references (internal KB):
// - Finding intersection of two segments (geometry, array, enumeration, two-pointers)
//   • When to use: Use this to determine if two line segments intersect and, if so, find the intersection point or the overlapping segment. It is useful for collision detection and computational geometry problems.
//   • Idea: This algorithm determines the intersection of two line segments by first handling parallel or collinear cases, then calculating the intersection point if lines are not parallel. It typically involves O(1) time complexity for a fixed number of segments.
//   • Invariants: Before checking for intersection, both segments are valid (non-degenerate or single points).; For non-parallel lines, the intersection point of their infinite extensions is uniquely determined.
//   • Tips: Handle general line intersection using parametric equations or cross products.; Project segments onto X and Y axes to check for overlap in collinear cases.
//   • Pitfalls: Incorrectly handling edge cases like segments sharing an endpoint or being single points.; Failing to distinguish between parallel and collinear segments.
// - Finding the equation of a line for a segment (geometry, number, enumeration)
//   • When to use: Use when the problem asks to count or list all possible combinations, permutations, or arrangements of elements. It's suitable when a brute-force check of all possibilities is feasible.
//   • Idea: Enumeration systematically generates and examines all possible solutions to a problem. This approach guarantees finding the correct answer if one exists, typically with exponential time complexity O(k^N) or O(N!).
//   • Invariants: At each step, the current partial solution is valid according to problem constraints.; All previously explored partial solutions have been processed or discarded.
//   • Tips: Clearly define the search space and the properties of valid solutions.; Use recursion or iterative loops to explore all branches of the solution space.
//   • Pitfalls: Overlooking edge cases or constraints that limit the search space.; Generating duplicate solutions if not handled carefully.
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
    bool isPrintable(vector<vector<int>>& targetGrid) {
        int m = targetGrid.size();
        int n = targetGrid[0].size();
        vector<vector<int>> colorBounds(61, vector<int>(4, -1));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int color = targetGrid[i][j];
                if (colorBounds[color][0] == -1) {
                    colorBounds[color][0] = i;
                    colorBounds[color][1] = i;
                    colorBounds[color][2] = j;
                    colorBounds[color][3] = j;
                } else {
                    colorBounds[color][0] = min(colorBounds[color][0], i);
                    colorBounds[color][1] = max(colorBounds[color][1], i);
                    colorBounds[color][2] = min(colorBounds[color][2], j);
                    colorBounds[color][3] = max(colorBounds[color][3], j);
                }
            }
        }
        vector<bool> printed(61, false);
        for (int _ = 0; _ < 60; ++_) {
            bool foundColorToPrint = false;
            for (int color = 1; color <= 60; ++color) {
                if (printed[color]) continue;
                int r1 = colorBounds[color][0];
                int r2 = colorBounds[color][1];
                int c1 = colorBounds[color][2];
                int c2 = colorBounds[color][3];
                if (r1 == -1) continue; 
                bool canPrintThisColor = true;
                for (int i = r1; i <= r2 && canPrintThisColor; ++i) {
                    for (int j = c1; j <= c2 && canPrintThisColor; ++j) {
                        if (targetGrid[i][j] != color && !printed[targetGrid[i][j]]) {
                            canPrintThisColor = false;
                        }
                    }
                }
                if (canPrintThisColor) {
                    printed[color] = true;
                    foundColorToPrint = true;
                }
            }
            if (!foundColorToPrint) break; 
        }
        return all_of(printed.begin(), printed.end(), [](bool p){ return p; });
    }
};
