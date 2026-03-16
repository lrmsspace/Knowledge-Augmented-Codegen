// Source: https://leetcode.com/problems/cherry-pickup/   |   Difficulty: Hard
//
// Problem Description:
// You are given an n x n grid representing a field of cherries, each cell is one of three possible integers.
//
//
// 	0 means the cell is empty, so you can pass through,
// 	1 means the cell contains a cherry that you can pick up and pass through, or
// 	-1 means the cell contains a thorn that blocks your way.
//
//
// Return the maximum number of cherries you can collect by following the rules below:
//
//
// 	Starting at the position (0, 0) and reaching (n - 1, n - 1) by moving right or down through valid path cells (cells with value 0 or 1).
// 	After reaching (n - 1, n - 1), returning to (0, 0) by moving left or up through valid path cells.
// 	When passing through a path cell containing a cherry, you pick it up, and the cell becomes an empty cell 0.
// 	If there is no valid path between (0, 0) and (n - 1, n - 1), then no cherries can be collected.
//
// Example:
// Input: grid = [[0,1,-1],[1,0,-1],[1,1,1]]
// Output: 5
// Explanation: The player started at (0, 0) and went down, down, right right to reach (2, 2).
// 4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
// Then, the player went left, up, up, left to return home, picking up one more cherry.
// The total number of cherries picked up is 5, and this is the maximum possible.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 50
// 	grid[i][j] is -1, 0, or 1.
// 	grid[0][0] != -1
// 	grid[n - 1][n - 1] != -1
//

class Solution {
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, -1)));
        dp[0][0][0] = grid[0][0];
        
        for (int r1 = 0; r1 < n; r1++) {
            for (int c1 = 0; c1 < n; c1++) {
                for (int r2 = 0; r2 < n; r2++) {
                    int c2 = r1 + c1 - r2;
                    if (c2 < 0 || c2 >= n || grid[r1][c1] == -1 || grid[r2][c2] == -1) {
                        continue;
                    }
                    
                    int val = grid[r1][c1];
                    if (r1 != r2 || c1 != c2) {
                        val += grid[r2][c2];
                    }
                    
                    int bestPrev = -1;
                    for (int dr1 = -1; dr1 <= 0; dr1++) {
                        for (int dr2 = -1; dr2 <= 0; dr2++) {
                            int prevR1 = r1 + dr1;
                            int prevC1 = c1 - (dr1 == -1 ? 0 : 1);
                            int prevR2 = r2 + dr2;
                            int prevC2 = c2 - (dr2 == -1 ? 0 : 1);
                            
                            if (prevR1 >= 0 && prevC1 >= 0 && prevR2 >= 0 && prevC2 >= 0 && dp[prevR1][prevC1][prevR2] != -1) {
                                bestPrev = max(bestPrev, dp[prevR1][prevC1][prevR2]);
                            }
                        }
                    }
                    
                    if (bestPrev != -1) {
                        dp[r1][c1][r2] = bestPrev + val;
                    }
                }
            }
        }
        
        return max(0, dp[n-1][n-1][n-1]);           
    }
};
