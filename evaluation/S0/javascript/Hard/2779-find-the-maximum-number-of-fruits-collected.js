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

/**
 * @param {number[][]} fruits
 * @return {number}
 */
var maxCollectedFruits = function(fruits) {
    const n = fruits.length;
    const dp = Array.from({ length: n }, () => Array.from({ length: n }, () => Array(n).fill(0)));
    dp[0][0][n - 1] = fruits[0][0] + fruits[0][n - 1] + (n - 1 === 0 ? 0 : fruits[0][n - 1]);
    for (let step = 1; step < n; step++) {
        const newDp = Array.from({ length: n }, () => Array.from({ length: n }, () => Array(n).fill(0)));
        for (let x1 = 0; x1 < n; x1++) {
            for (let y1 = 0; y1 < n; y1++) {
                for (let x2 = 0; x2 < n; x2++) {
                    const y2 = step - x2;
                    if (y2 < 0 || y2 >= n) continue;
                    let maxFruits = 0;
                    for (let dx1 of [0, 1]) {
                        for (let dx2 of [0, 1]) {
                            const prevX1 = x1 - dx1;
                            const prevY1 = step - 1 - prevX1;
                            const prevX2 = x2 - dx2;
                            const prevY2 = step - 1 - prevX2;
                            if (prevX1 < 0 || prevY1 < 0 || prevX2 < 0 || prevY2 < 0 || prevY1 >= n || prevY2 >= n) continue;
                            maxFruits = Math.max(maxFruits, dp[prevX1][prevY1][prevX2]);
                        }
                    }
                    if (maxFruits === 0) continue;
                    let currentFruits = fruits[x1][y1];
                    if (x2 !== x1 || y2 !== y1) {
                        currentFruits += fruits[x2][y2];
                    }
                    const x3 = n - 1 - (step - (x1 + y1));
                    const y3 = step - x3;
                    if (x3 >= 0 && x3 < n && y3 >= 0 && y3 < n) {
                        if ((x3 !== x1 || y3 !== y1) && (x3 !== x2 || y3 !== y2)) {
                            currentFruits += fruits[x3][y3];
                        }
                    }
                    newDp[x1][y1][x2] = Math.max(newDp[x1][y1][x2], maxFruits + currentFruits);
                }
            }
        }
        for (let x1 = 0; x1 < n; x1++) {
            for (let y1 = 0; y1 < n; y1++) {
                for (let x2 = 0; x2 < n; x2++) {
                    dp[x1][y1][x2] = newDp[x1][y1][x2];
                }
            }
        }
    }
    return dp[n - 1][n - 1][n - 1];
};
