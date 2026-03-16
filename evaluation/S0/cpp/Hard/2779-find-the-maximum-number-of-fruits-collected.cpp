// Source: https://leetcode.com/problems/find-the-maximum-number-of-fruits-collected/   |   Difficulty: Hard
//
// Problem Description:
// There is a game dungeon comprised of n x n rooms arranged in a grid.
//
// You are given a 2D array fruits of size n x n, where fruits[i][j] represents the number of fruits in the room (i, j). Three children will play in the game dungeon, with initial positions at the corner rooms (0, 0), (0, n - 1), and (n - 1, 0).
//
// The children will make exactly n - 1 moves according to the following rules to reach the room (n - 1, n - 1):
//
//
// 	The child starting from (0, 0) must move from their current room (i, j) to one of the rooms (i + 1, j + 1), (i + 1, j), and (i, j + 1) if the target room exists.
// 	The child starting from (0, n - 1) must move from their current room (i, j) to one of the rooms (i + 1, j - 1), (i + 1, j), and (i + 1, j + 1) if the target room exists.
// 	The child starting from (n - 1, 0) must move from their current room (i, j) to one of the rooms (i - 1, j + 1), (i, j + 1), and (i + 1, j + 1) if the target room exists.
//
//
// When a child enters a room, they will collect all the fruits there. If two or more children enter the same room, only one child will collect the fruits, and the room will be emptied after they leave.
//
// Return the maximum number of fruits the children can collect from the dungeon.
//
// Example:
// Input: fruits = [[1,2,3,4],[5,6,8,7],[9,10,11,12],[13,14,15,16]]
//
// Output: 100
//
// Explanation:
//
//
//
// In this example:
//
//
// 	The 1st child (green) moves on the path (0,0) -> (1,1) -> (2,2) -> (3, 3).
// 	The 2nd child (red) moves on the path (0,3) -> (1,2) -> (2,3) -> (3, 3).
// 	The 3rd child (blue) moves on the path (3,0) -> (3,1) -> (3,2) -> (3, 3).
//
//
// In total they collect 1 + 6 + 11 + 16 + 4 + 8 + 12 + 13 + 14 + 15 = 100 fruits.
//
// Constraints:
// 2 <= n == fruits.length == fruits[i].length <= 1000
// 	0 <= fruits[i][j] <= 1000
//

class Solution {
public:
    int maxCollectedFruits(vector<vector<int>>& fruits) {
        int n = fruits.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, 0)));
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    int x1 = i, y1 = j;
                    int x2 = i, y2 = n - 1 - k;
                    int x3 = n - 1 - k, y3 = j;
                    
                    int currFruits = fruits[x1][y1];
                    if (x2 != x1 || y2 != y1) currFruits += fruits[x2][y2];
                    if ((x3 != x1 || y3 != y1) && (x3 != x2 || y3 != y2)) currFruits += fruits[x3][y3];
                    
                    int maxPrev = 0;
                    for (int dx1 = -1; dx1 <= 0; ++dx1) {
                        for (int dx2 = -1; dx2 <= 0; ++dx2) {
                            for (int dx3 = -1; dx3 <= 0; ++dx3) {
                                int px1 = x1 + dx1;
                                int py1 = y1 + (dx1 == 0 ? -1 : 0);
                                int px2 = x2 + dx2;
                                int py2 = y2 + (dx2 == 0 ? (dx2 == -1 ? 1 : -1) : 0);
                                int px3 = x3 + dx3;
                                int py3 = y3 + (dx3 == 0 ? -1 : 0);
                                
                                if (px1 >= 0 && py1 >= 0 && px2 >= 0 && py2 >= 0 && px3 >= 0 && py3 >= 0 &&
                                    px1 < n && py1 < n && px2 < n && py2 < n && px3 < n && py3 < n) {
                                    maxPrev = max(maxPrev, dp[px1][px2][n - 1 - py3]);
                                }
                            }
                        }
                    }
                    dp[x1][x2][n - 1 - y3] = maxPrev + currFruits;
                    
                }
            }
        }
        return dp[n - 1][n - 1][0];
    }
};
