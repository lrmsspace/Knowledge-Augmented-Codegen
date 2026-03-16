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

class Solution {
public:
    int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount) {
        const int introvertBase = 120;
        const int extrovertBase = 40;
        const int introvertNeighborEffect = -30;
        const int extrovertNeighborEffect = 20;
        
        int totalStates = pow(3, n);
        vector<vector<int>> stateInfo(totalStates, vector<int>(4, 0)); // [introverts, extroverts, happiness, neighborEffect]
        
        for (int state = 0; state < totalStates; state++) {
            int tempState = state;
            int introverts = 0, extroverts = 0, happiness = 0, neighborEffect = 0;
            for (int col = 0; col < n; col++) {
                int cellType = tempState % 3;
                tempState /= 3;
                if (cellType == 1) { // Introvert
                    introverts++;
                    happiness += introvertBase;
                    neighborEffect += introvertNeighborEffect;
                } else if (cellType == 2) { // Extrovert
                    extroverts++;
                    happiness += extrovertBase;
                    neighborEffect += extrovertNeighborEffect;
                }
            }
            stateInfo[state] = {introverts, extroverts, happiness, neighborEffect};
        }
        
        vector<vector<vector<vector<int>>>> dp(m + 1, vector<vector<vector<int>>>(n + 1, vector<vector<int>>(introvertsCount + 1, vector<int>(extrovertsCount + 1, INT_MIN))));
        dp[0][0][introvertsCount][extrovertsCount] = 0;
        
        for (int row = 0; row < m; row++) {
            for (int col = 0; col < n; col++) {
                for (int iCount = 0; iCount <= introvertsCount; iCount++) {
                    for (int eCount = 0; eCount <= extrovertsCount; eCount++) {
                        if (dp[row][col][iCount][eCount] == INT_MIN) continue;
                        for (int newState = 0; newState < totalStates; newState++) {
                            int ni = stateInfo[newState][0];
                            int ne = stateInfo[newState][1];
                            if (ni > iCount || ne > eCount) continue;
                            
                            int happinessGain = stateInfo[newState][2];
                            int neighborEffect = stateInfo[newState][3];
                            if (col > 0) {
                                int leftCellType = (newState / static_cast<int>(pow(3, n - 1))) % 3;
                                if (leftCellType != 0) {
                                    if (leftCellType == 1) { // Introvert
                                        happinessGain += introvertNeighborEffect;
                                        neighborEffect += introvertNeighborEffect;
                                    } else { // Extrovert
                                        happinessGain += extrovertNeighborEffect;
                                        neighborEffect += extrovertNeighborEffect;
                                    }
                                }
                            }
                            if (row > 0) {
                                int upCellType = (newState % static_cast<int>(pow(3, n))) / static_cast<int>(pow(3, n - 1));
                                if (upCellType != 0) {
                                    if (upCellType == 1) { // Introvert
                                        happinessGain += introvertNeighborEffect;
                                        neighborEffect += introvertNeighborEffect;
                                    } else { // Extrovert
                                        happinessGain += extrovertNeighborEffect;
                                        neighborEffect += extrovertNeighborEffect;
                                    }
                                }
                            }
                            int nextRow = col == n - 1 ? row + 1 : row;
                            int nextCol = col == n - 1 ? 0 : col + 1;
                            dp[nextRow][nextCol][iCount - ni][eCount - ne] = max(dp[nextRow][nextCol][iCount - ni][eCount - ne], dp[row][col][iCount][eCount] + happinessGain + neighborEffect);
                        }
                    }
                }
            }
        }
        int maxHappiness = 0;
        for (int iCount = 0; iCount <= introvertsCount; iCount++) {
            for (int eCount = 0; eCount <= extrovertsCount; eCount++) {
                maxHappiness = max(maxHappiness, dp[m][0][iCount][eCount]);
            }
        }
        return maxHappiness;
    }
};
