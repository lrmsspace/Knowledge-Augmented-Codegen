// Source: https://leetcode.com/problems/make-a-square-with-the-same-color/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 2D matrix grid of size 3 x 3 consisting only of characters 'B' and 'W'. Character 'W' represents the white color, and character 'B' represents the black color.
//
// Your task is to change the color of at most one cell so that the matrix has a 2 x 2 square where all cells are of the same color.
//
// Return true if it is possible to create a 2 x 2 square of the same color, otherwise, return false.
//
//  
// .grid-container {
//   display: grid;
//   grid-template-columns: 30px 30px 30px;
//   padding: 10px;
// }
// .grid-item {
//   background-color: black;
//   border: 1px solid gray;
//   height: 30px;
//   font-size: 30px;
//   text-align: center;
// }
// .grid-item-white {
//   background-color: white;
// }
//
// Example:
// Input: grid = [["B","W","B"],["B","W","W"],["B","W","B"]]
//
// Output: true
//
// Explanation:
//
// It can be done by changing the color of the grid[0][2].
//
// Constraints:
// grid.length == 3
// 	grid[i].length == 3
// 	grid[i][j] is either 'W' or 'B'.
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool canMakeSquare(char** grid, int gridSize, int* gridColSize) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            int black = 0, white = 0;
            for (int x = i; x < i + 2; ++x) {
                for (int y = j; y < j + 2; ++y) {
                    if (grid[x][y] == 'B') {
                        ++black;
                    } else {
                        ++white;
                    }
                }
            }
            if (black >= 3 || white >= 3) {
                return true;
            }
        }
    }
    return false;       
}
