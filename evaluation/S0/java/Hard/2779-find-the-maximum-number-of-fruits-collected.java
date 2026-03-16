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
    public int maxCollectedFruits(int[][] fruits) {
        int n = fruits.length;
        int[][] dp = new int[n][n];

        for (int step = 0; step < n; step++) {
            int[][] newDp = new int[n][n];
            for (int[] row : newDp) {
                Arrays.fill(row, -1);
            }

            for (int x1 = 0; x1 <= step; x1++) {
                for (int x2 = 0; x2 <= step; x2++) {
                    int y1 = step - x1;
                    int y2 = step - x2;
                    if (y1 >= n || y2 >= n) continue;

                    int val = fruits[x1][y1];
                    if (x1 != x2 || y1 != y2) {
                        val += fruits[x2][y2];
                    }

                    for (int dx1 = 0; dx1 <= 1; dx1++) {
                        for (int dx2 = 0; dx2 <= 1; dx2++) {
                            int px1 = x1 - dx1;
                            int px2 = x2 - dx2;
                            int py1 = step - 1 - px1;
                            int py2 = step - 1 - px2;
                            if (px1 < 0 || px2 < 0 || py1 < 0 || py2 < 0 || py1 >= n || py2 >= n) {
                                continue;
                            }
                            if (dp[px1][px2] < 0) {
                                continue;
                            }
                            newDp[x1][x2] = Math.max(newDp[x1][x2], dp[px1][px2] + val);
                        }
                    }
                }
            }
            dp = newDp;
        }

        return dp[n - 1][n - 1];            
    }
}
