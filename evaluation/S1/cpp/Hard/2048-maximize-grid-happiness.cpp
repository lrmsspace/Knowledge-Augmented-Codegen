// Source: https://leetcode.com/problems/maximize-grid-happiness/   |   Difficulty: Hard
//
// Problem Description:
// You are given four integers, m, n, introvertsCount, and extrovertsCount. You have an m x n grid, and there are two types of people: introverts and extroverts. There are introvertsCount introverts and extrovertsCount extroverts.
//
// You should decide how many people you want to live in the grid and assign each of them one grid cell. Note that you do not have to have all the people living in the grid.
//
// The happiness of each person is calculated as follows:
//
//
// 	Introverts start with 120 happiness and lose 30 happiness for each neighbor (introvert or extrovert).
// 	Extroverts start with 40 happiness and gain 20 happiness for each neighbor (introvert or extrovert).
//
//
// Neighbors live in the directly adjacent cells north, east, south, and west of a person's cell.
//
// The grid happiness is the sum of each person's happiness. Return the maximum possible grid happiness.
//
// Example:
// Input: m = 2, n = 3, introvertsCount = 1, extrovertsCount = 2
// Output: 240
// Explanation: Assume the grid is 1-indexed with coordinates (row, column).
// We can put the introvert in cell (1,1) and put the extroverts in cells (1,3) and (2,3).
// - Introvert at (1,1) happiness: 120 (starting happiness) - (0 * 30) (0 neighbors) = 120
// - Extrovert at (1,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
// - Extrovert at (2,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
// The grid happiness is 120 + 60 + 60 = 240.
// The above figure shows the grid in this example with each person's happiness. The introvert stays in the light green cell while the extroverts live on the light purple cells.
//
// Constraints:
// 1 <= m, n <= 5
// 	0 <= introvertsCount, extrovertsCount <= min(m * n, 6)
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Introduction to Dynamic Programming (array, tree, recursion, dp-1d)
//   • When to use: Use when a problem has overlapping subproblems and optimal substructure, and a natural recursive solution is inefficient due to redundant computations. It's ideal for transforming exponential recursive solutions into polynomial time.
//   • Idea: Top-down dynamic programming, or memoization, optimizes recursive solutions by storing the results of expensive function calls and returning the cached result when the same inputs occur again. This technique typically reduces time complexity from exponential to polynomial, often O(N) or O(N*M).
//   • Invariants: memo[state] contains the computed result for 'state' if memo[state] is not the sentinel value.; If memo[state] is the sentinel value, the result for 'state' has not yet been computed.
//   • Tips: Initialize the memoization table with a sentinel value (e.g., -1, null) to distinguish uncomputed states from valid zero/false results.; Use arrays for lookup tables when the state space is contiguous and small for optimal cache performance.
//   • Pitfalls: Forgetting to initialize the memoization table, leading to incorrect results or infinite loops.; Incorrectly identifying or handling base cases in the recursive function.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount) {
        const int MAX_MASK = pow(3, n);
        vector<int> introvertHappinessChange(MAX_MASK, 0);
        vector<int> extrovertHappinessChange(MAX_MASK, 0);
        vector<int> introvertCountInMask(MAX_MASK, 0);
        vector<int> extrovertCountInMask(MAX_MASK, 0);

        for (int mask = 0; mask < MAX_MASK; ++mask) {
            int introvertHappiness = 0;
            int extrovertHappiness = 0;
            int introvertCount = 0;
            int extrovertCount = 0;
            vector<int> cells(n, 0);
            int tempMask = mask;

            for (int j = 0; j < n; ++j) {
                cells[j] = tempMask % 3;
                tempMask /= 3;
            }

            for (int j = 0; j < n; ++j) {
                if (cells[j] == 1) { // Introvert
                    introvertHappiness += 120;
                    introvertCount++;
                    if (j > 0) {
                        if (cells[j - 1] == 1) {
                            introvertHappiness -= 60;
                        } else if (cells[j - 1] == 2) {
                            introvertHappiness -= 10;
                            extrovertHappiness += 20;
                        }
                    }
                } else if (cells[j] == 2) { // Extrovert
                    extrovertHappiness += 40;
                    extrovertCount++;
                    if (j > 0) {
                        if (cells[j - 1] == 1) {
                            introvertHappiness -= 10;
                            extrovertHappiness += 20;
                        } else if (cells[j - 1] == 2) {
                            extrovertHappiness += 40;
                        }
                    }
                }
            }

            introvertHappinessChange[mask] = introvertHappiness;
            extrovertHappinessChange[mask] = extrovertHappiness;
            introvertCountInMask[mask] = introvertCount;
            extrovertCountInMask[mask] = extrovertCount;
        }

        vector<vector<vector<vector<int>>>> dp(m + 1, vector<vector<vector<int>>>(MAX_MASK, vector<vector<int>>(introvertsCount + 1, vector<int>(extrovertsCount + 1, INT_MIN)));
        dp[0][0][0][0] = 0;
        for (int row = 1; row <= m; ++row) {
            for (int currMask = 0; currMask < MAX_MASK; ++currMask) {
                for (int introvertsUsed = 0; introvertsUsed <= introvertsCount; ++introvertsUsed) {
                    for (int extrovertsUsed = 0; extrovertsUsed <= extrovertsCount; ++extrovertsUsed) {
                        int currIntroverts = introvertCountInMask[currMask];
                        int currExtroverts = extrovertCountInMask[currMask];
                        if (introvertsUsed < currIntroverts || extrovertsUsed < currExtroverts) {
                            continue;
                        }

                        for (int prevMask = 0; prevMask < MAX_MASK; ++prevMask) {
                            int happiness = dp[row - 1][prevMask][introvertsUsed - currIntroverts][extrovertsUsed - currExtroverts];
                            if (happiness == INT_MIN) {
                                continue;
                            }

                            happiness += introvertHappinessChange[currMask] + extrovertHappinessChange[currMask];

                            for (int j = 0; j < n; ++j) {
                                int currCell = (currMask / static_cast<int>(pow(3, j))) % 3;
                                int prevCell = (prevMask / static_cast<int>(pow(3, j))) % 3;

                                if (currCell == 1) { // Introvert
                                    if (prevCell == 1) {
                                        happiness -= 30;
                                    } else if (prevCell == 2) {
                                        happiness -= 10;
                                        happiness += 20;
                                    }
                                } else if (currCell == 2) { // Extrovert
                                    if (prevCell == 1) {
                                        happiness -= 10;
                                        happiness += 20;
                                    } else if (prevCell == 2) {
                                        happiness += 40;
                                    }
                                }
                            }

                            dp[row][currMask][introvertsUsed][extrovertsUsed] = max(dp[row][currMask][introvertsUsed][extrovertsUsed], happiness);
                        }
                    }
                }
            }
        }
        int maxHappiness = 0;
        for (int mask = 0; mask < MAX_MASK; ++mask) {
            maxHappiness = max(maxHappiness, dp[m][mask][introvertsCount][extrovertsCount]);
        }
        return maxHappiness;
    }
};
