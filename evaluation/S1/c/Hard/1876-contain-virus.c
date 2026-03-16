// Source: https://leetcode.com/problems/contain-virus/   |   Difficulty: Hard
//
// Problem Description:
// A virus is spreading rapidly, and your task is to quarantine the infected area by installing walls.
//
// The world is modeled as an m x n binary grid isInfected, where isInfected[i][j] == 0 represents uninfected cells, and isInfected[i][j] == 1 represents cells contaminated with the virus. A wall (and only one wall) can be installed between any two 4-directionally adjacent cells, on the shared boundary.
//
// Every night, the virus spreads to all neighboring cells in all four directions unless blocked by a wall. Resources are limited. Each day, you can install walls around only one region (i.e., the affected area (continuous block of infected cells) that threatens the most uninfected cells the following night). There will never be a tie.
//
// Return the number of walls used to quarantine all the infected regions. If the world will become fully infected, return the number of walls used.
//
// Example:
// Input: isInfected = [[0,1,0,0,0,0,0,1],[0,1,0,0,0,0,0,1],[0,0,0,0,0,0,0,1],[0,0,0,0,0,0,0,0]]
// Output: 10
// Explanation: There are 2 contaminated regions.
// On the first day, add 5 walls to quarantine the viral region on the left. The board after the virus spreads is:
//
// On the second day, add 5 walls to quarantine the viral region on the right. The virus is fully contained.
//
// Constraints:
// m == isInfected.length
// 	n == isInfected[i].length
// 	1 <= m, n <= 50
// 	isInfected[i][j] is either 0 or 1.
// 	There is always a contiguous viral region throughout the described process that will infect strictly more uncontaminated squares in the next round.
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
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int containVirus(int** isInfected, int isInfectedSize, int* isInfectedColSize) {
    int m = isInfectedSize;
    int n = isInfectedColSize[0];
    int totalWalls = 0;

    // Directions for 4-directional movement
    int directions[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};

    while (1) {
        // Step 1: Identify all infected regions and their threat levels
        int regionCount = 0;
        int regionIds[m][n];
        memset(regionIds, -1, sizeof(regionIds));
        int threats[m*n];
        int wallsNeeded[m*n];
        memset(threats, 0, sizeof(threats));
        memset(wallsNeeded, 0, sizeof(wallsNeeded));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (isInfected[i][j] == 1 && regionIds[i][j] == -1) {
                    // BFS to explore the region
                    int queue[m*n][2];
                    int front = 0, back = 0;
                    queue[back][0] = i; queue[back][1] = j; back++;
                    regionIds[i][j] = regionCount;

                    while (front < back) {
                        int x = queue[front][0];
                        int y = queue[front][1];
                        front++;

                        for (int d = 0; d < 4; d++) {
                            int nx = x + directions[d][0];
                            int ny = y + directions[d][1];
                            if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                                if (isInfected[nx][ny] == 0) {
                                    threats[regionCount]++;
                                    wallsNeeded[regionCount]++;
                                } else if (isInfected[nx][ny] == 1 && regionIds[nx][ny] == -1) {
                                    regionIds[nx][ny] = regionCount;
                                    queue[back][0] = nx; queue[back][1] = ny; back++;
                                }
                            }
                        }
                    }
                    regionCount++;
                }
            }
        }

        if (regionCount == 0) break; // No more infected regions

        // Step 2: Find the region with the maximum threat
        int maxThreat = 0;
        int targetRegion = -1;
        for (int r = 0; r < regionCount; r++) {
            if (threats[r] > maxThreat) {
                maxThreat = threats[r];
                targetRegion = r;
            }
        }
        if (maxThreat == 0) break; // No more threats
        totalWalls += wallsNeeded[targetRegion];
        // Step 3: Quarantine the target region
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (regionIds[i][j] == targetRegion) {
                    isInfected[i][j] = -1; // Mark as quarantined
                }
            }
        }
        // Step 4: Spread the virus from other regions
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (isInfected[i][j] == 1 && regionIds[i][j] != targetRegion) {
                    for (int d = 0; d < 4; d++) {
                        int nx = i + directions[d][0];
                        int ny = j + directions[d][1];
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && isInfected[nx][ny] == 0) {
                            isInfected[nx][ny] = 1; // Infect the cell
                        }
                    }
                }
            }
        }

}
    return totalWalls;
}