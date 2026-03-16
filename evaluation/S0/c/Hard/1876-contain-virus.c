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

int containVirus(int** isInfected, int isInfectedSize, int* isInfectedColSize) {
    int m = isInfectedSize;
    int n = isInfectedColSize[0];
    int totalWalls = 0;

    while (1) {
        int regionCount = 0;
        int regions[2500][2500]; // Store infected cells for each region
        int frontiers[2500][2500]; // Store frontier cells for each region
        int wallsNeeded[2500]; // Walls needed for each region
        memset(wallsNeeded, 0, sizeof(wallsNeeded));
        memset(regions, 0, sizeof(regions));
        memset(frontiers, 0, sizeof(frontiers));

        int visited[50][50];
        memset(visited, 0, sizeof(visited));

        // Identify regions and their frontiers
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (isInfected[i][j] == 1 && !visited[i][j]) {
                    regionCount++;
                    int stack[2500][2];
                    int top = -1;
                    stack[++top][0] = i;
                    stack[top][1] = j;
                    visited[i][j] = 1;

                    while (top >= 0) {
                        int x = stack[top][0];
                        int y = stack[top][1];
                        top--;
                        regions[regionCount - 1][x * n + y] = 1;

                        int directions[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
                        for (int d = 0; d < 4; d++) {
                            int nx = x + directions[d][0];
                            int ny = y + directions[d][1];
                            if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                                if (isInfected[nx][ny] == 1 && !visited[nx][ny]) {
                                    visited[nx][ny] = 1;
                                    stack[++top][0] = nx;
                                    stack[top][1] = ny;
                                } else if (isInfected[nx][ny] == 0) {
                                    frontiers[regionCount - 1][nx * n + ny] = 1;
                                    wallsNeeded[regionCount - 1]++;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (regionCount == 0) break; // No more infected regions
        // Find the region with the maximum frontier
        int maxFrontierIdx = 0;
        int maxFrontierSize = 0;
        for (int r = 0; r < regionCount; r++) {
            int frontierSize = 0;
            for (int i = 0; i < m * n; i++) {
                if (frontiers[r][i]) frontierSize++;
            }
            if (frontierSize > maxFrontierSize) {
                maxFrontierSize = frontierSize;
                maxFrontierIdx = r;
            }
        }
        // Build walls for the selected region
        totalWalls += wallsNeeded[maxFrontierIdx];
        for (int i = 0; i < m * n; i++) {
            if (regions[maxFrontierIdx][i]) {
                int x = i / n;
                int y = i % n;
                isInfected[x][y] = -1; // Mark as quarantined
            }
        }
        // Spread the virus for other regions
        for (int r = 0; r < regionCount; r++) {
            if (r == maxFrontierIdx) continue;
            for (int i = 0; i < m * n; i++) {
                if (frontiers[r][i]) {
                    int x = i / n;
                    int y = i % n;
                    isInfected[x][y] = 1; // Infect the cell
                }
            }
        }
    }
    return totalWalls;
}
