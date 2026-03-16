// Source: https://leetcode.com/problems/dungeon-game/   |   Difficulty: Hard
//
// Problem Description:
// The demons had captured the princess and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of m x n rooms laid out in a 2D grid. Our valiant knight was initially positioned in the top-left room and must fight his way through dungeon to rescue the princess.
//
// The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.
//
// Some of the rooms are guarded by demons (represented by negative integers), so the knight loses health upon entering these rooms; other rooms are either empty (represented as 0) or contain magic orbs that increase the knight's health (represented by positive integers).
//
// To reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.
//
// Return the knight's minimum initial health so that he can rescue the princess.
//
// Note that any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.
//
// Example:
// Input: dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
// Output: 7
// Explanation: The initial health of the knight must be at least 7 if he follows the optimal path: RIGHT-> RIGHT -> DOWN -> DOWN.
//
// Constraints:
// m == dungeon.length
// 	n == dungeon[i].length
// 	1 <= m, n <= 200
// 	-1000 <= dungeon[i][j] <= 1000
//

/**
 * @param {number[][]} dungeon
 * @return {number}
 */
var calculateMinimumHP = function(dungeon) {
    


    let m = dungeon.length;
    let n = dungeon[0].length;
    let dp = new Array(m).fill(0).map(() => new Array(n).fill(0));
    dp[m - 1][n - 1] = Math.max(1, 1 - dungeon[m - 1][n - 1]);

    for (let i = m - 2; i >= 0; i--) {
        dp[i][n - 1] = Math.max(1, dp[i + 1][n - 1] - dungeon[i][n - 1]);
    }
    for (let j = n - 2; j >= 0; j--) {
        dp[m - 1][j] = Math.max(1, dp[m - 1][j + 1] - dungeon[m - 1][j]);
    }
    for (let i = m - 2; i >= 0; i--) {
        for (let j = n - 2; j >= 0; j--) {
            let down = Math.max(1, dp[i + 1][j] - dungeon[i][j]);
            let right = Math.max(1, dp[i][j + 1] - dungeon[i][j]);
            dp[i][j] = Math.min(down, right);
        }
    }
    return dp[0][0];
    
};
