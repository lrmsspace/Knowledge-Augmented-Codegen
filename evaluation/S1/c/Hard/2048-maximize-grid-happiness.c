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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

// Global memo table and parameters for DP
static int g_memo[5][5][7][7][243];
static int g_m, g_n;

// Helper: Get the type of person at position col in a row encoded as mask (base-3)
static int getType(int mask, int col) {
    int power = 1, i;
    for (i = 0; i < col; i++) {
        power *= 3;
    }
    return (mask / power) % 3;
}

// Helper: Set the type of person at position col in a row mask (base-3)
static int setType(int mask, int col, int type) {
    int power = 1, i;
    for (i = 0; i < col; i++) {
        power *= 3;
    }
    return mask + type * power;
}

// Recursive DP: Calculate max happiness from position (row, col) onwards
// mask: current row configuration (base-3 encoding: 0=empty, 1=introvert, 2=extrovert)
// prevMask: previous row configuration (base-3 encoding)
static int dp(int row, int col, int introverts, int extroverts, int mask, int prevMask) {
    if (introverts < 0 || extroverts < 0) return -1000000;
    if (row == g_m) return 0;
    
    if (col == g_n) {
        return dp(row + 1, 0, introverts, extroverts, 0, mask);
    }
    
    if (g_memo[row][col][introverts][extroverts][mask] != -1) {
        return g_memo[row][col][introverts][extroverts][mask];
    }
    
    int result = 0;
    int leftType = col > 0 ? getType(mask, col - 1) : 0;
    int topType = row > 0 ? getType(prevMask, col) : 0;
    
    // Option 1: Don't place anyone
    result = dp(row, col + 1, introverts, extroverts, mask, prevMask);
    
    // Option 2: Place introvert
    if (introverts > 0) {
        int happiness = 120;
        int neighbors = 0;
        if (leftType > 0) neighbors++;
        if (topType > 0) neighbors++;
        happiness -= neighbors * 30;
        int newMask = setType(mask, col, 1);
        int temp = dp(row, col + 1, introverts - 1, extroverts, newMask, prevMask);
        if (temp > -1000000 && happiness + temp > result) {
            result = happiness + temp;
        }
    }
    
    // Option 3: Place extrovert
    if (extroverts > 0) {
        int happiness = 40;
        int neighbors = 0;
        if (leftType > 0) neighbors++;
        if (topType > 0) neighbors++;
        happiness += neighbors * 20;
        int newMask = setType(mask, col, 2);
        int temp = dp(row, col + 1, introverts, extroverts - 1, newMask, prevMask);
        if (temp > -1000000 && happiness + temp > result) {
            result = happiness + temp;
        }
    }
    
    return g_memo[row][col][introverts][extroverts][mask] = result;
}

int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount) {
    int i, j, k, l, p;
    
    // Initialize memoization table
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            for (k = 0; k < 7; k++) {
                for (l = 0; l < 7; l++) {
                    for (p = 0; p < 243; p++) {
                        g_memo[i][j][k][l][p] = -1;
                    }
                }
            }
        }
    }
    
    g_m = m;
    g_n = n;
    
    return dp(0, 0, introvertsCount, extrovertsCount, 0, 0);
}
