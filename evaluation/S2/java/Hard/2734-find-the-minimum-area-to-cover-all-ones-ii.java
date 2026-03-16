// Source: https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D binary array grid. You need to find 3 non-overlapping rectangles having non-zero areas with horizontal and vertical sides such that all the 1's in grid lie inside these rectangles.
//
// Return the minimum possible sum of the area of these rectangles.
//
// Note that the rectangles are allowed to touch.
//
// Example:
// Input: grid = [[1,0,1],[1,1,1]]
//
// Output: 5
//
// Explanation:
//
//
//
//
// 	The 1's at (0, 0) and (1, 0) are covered by a rectangle of area 2.
// 	The 1's at (0, 2) and (1, 2) are covered by a rectangle of area 2.
// 	The 1 at (1, 1) is covered by a rectangle of area 1.
//
// Constraints:
// 1 <= grid.length, grid[i].length <= 30
// 	grid[i][j] is either 0 or 1.
// 	The input is generated such that there are at least three 1's in grid.
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Manhattan Distance (geometry, number, coordinate-compress)
//   • When to use: Use when calculating distance between two points on a grid where movement is restricted to horizontal and vertical directions. It is also useful for problems involving maximizing or minimizing sums of absolute coordinate differences, often transformable to Chebyshev distance.
//   • Idea: Manhattan distance measures the sum of absolute differences of Cartesian coordinates between two points. It can be transformed into a Chebyshev distance problem by rotating coordinates, enabling efficient O(N) max/min distance calculations.
//   • Invariants: For any two points P1=(x1, y1) and P2=(x2, y2), the Manhattan distance is always non-negative.; The transformed points P1'=(x1+y1, y1-x1) and P2'=(x2+y2, y2-x2) satisfy Chebyshev(P1', P2') == Manhattan(P1, P2).
//   • Tips: Consider transforming to Chebyshev distance for max/min distance problems.; The transformation involves rotating coordinates: (x, y) -> (x+y, y-x).
//   • Pitfalls: Confusing with Euclidean distance, which allows diagonal movement.; Incorrectly applying coordinate transformation (e.g., wrong signs).
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minimumSum(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int[][] left = new int[m][n], right = new int[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    left[i][j] = (j > 0 ? left[i][j - 1] : 0) + 1;
                }
            }
            for (int j = n - 1; j >= 0; j--) {
                if (grid[i][j] == 1) {
                    right[i][j] = (j < n - 1 ? right[i][j + 1] : 0) + 1;
                }
            }
        }

        int ans = Integer.MAX_VALUE;
        for (int c1 = 0; c1 < n - 2; c1++) {
            for (int c2 = c1 + 1; c2 < n - 1; c2++) {
                for (int c3 = c2 + 1; c3 < n; c3++) {
                    int area = Math.max(left[0][c1], Math.max(left[0][c2], left[0][c3]));
                    for (int r = 0; r < m; r++) {
                        area += Math.max(right[r][c1], Math.max(right[r][c2], right[r][c3]));
                    }
                    ans = Math.min(ans, area);
                }
            }
        }
        return ans;         
    }
}
