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

int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount) {
    int totalCells = m * n;
    int stateSize = 1;
    for (int i = 0; i < n; i++) stateSize *= 3; /* 0: empty, 1: introvert, 2: extrovert */

    int dp[totalCells + 1][introvertsCount + 1][extrovertsCount + 1][stateSize];
    memset(dp, -1, sizeof(dp));
    dp[0][0][0][0] = 0;

    int getNeighborEffect(int curr, int neighbor) {
        if (neighbor == 0) return 0;
        if (curr == 1) return (neighbor == 1) ? -60 : -10; /* introvert */
        return (neighbor == 1) ? -10 : 40; /* extrovert */
    }

    for (int cell = 0; cell < totalCells; cell++) {
        int row = cell / n;
        int col = cell % n;
        for (int intro = 0; intro <= introvertsCount; intro++) {
            for (int extro = 0; extro <= extrovertsCount; extro++) {
                for (int state = 0; state < stateSize; state++) {
                    if (dp[cell][intro][extro][state] == -1) continue;

                    int up = (row > 0) ? (state / (int)pow(3, n - 1)) % 3 : 0;
                    int left = (col > 0) ? (state / (int)pow(3, n - 2)) % 3 : 0;

                    /* Option 1: Leave cell empty */
                    int newState = (state * 3) % stateSize;
                    if (dp[cell + 1][intro][extro][newState] < dp[cell][intro][extro][state]) {
                        dp[cell + 1][intro][extro][newState] = dp[cell][intro][extro][state];
                    }

                    /* Option 2: Place introvert */
                    if (intro < introvertsCount) {
                        int happiness = 120 + getNeighborEffect(1, up) + getNeighborEffect(1, left);
                        newState = ((state * 3) % stateSize) + 1;
                        if (dp[cell + 1][intro + 1][extro][newState] < dp[cell][intro][extro][state] + happiness) {
                            dp[cell + 1][intro + 1][extro][newState] = dp[cell][intro][extro][state] + happiness;
                        }
                    }
                    /* Option 3: Place extrovert */
                    if (extro < extrovertsCount) {
                        int happiness = 40 + getNeighborEffect(2, up) + getNeighborEffect(2, left);
                        newState = ((state * 3) % stateSize) + 2;
                        if (dp[cell + 1][intro][extro + 1][newState] < dp[cell][intro][extro][state] + happiness) {
                            dp[cell + 1][intro][extro + 1][newState] = dp[cell][intro][extro][state] + happiness;
                        }
                    }
                }
            }
        }
    }
    int result = 0;
    for (int state = 0; state < stateSize; ++state) {
        if (dp[totalCells][introvertsCount][extrovertsCount][state] > result) {
            result = dp[totalCells][introvertsCount][extrovertsCount][state];
        }
    }
    return result;
}
