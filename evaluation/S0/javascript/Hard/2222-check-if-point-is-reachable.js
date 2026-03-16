// Source: https://leetcode.com/problems/check-if-point-is-reachable/   |   Difficulty: Hard
//
// Problem Description:
// There exists an infinitely large grid. You are currently at point (1, 1), and you need to reach the point (targetX, targetY) using a finite number of steps.
//
// In one step, you can move from point (x, y) to any one of the following points:
//
//
// 	(x, y - x)
// 	(x - y, y)
// 	(2 * x, y)
// 	(x, 2 * y)
//
//
// Given two integers targetX and targetY representing the X-coordinate and Y-coordinate of your final position, return true if you can reach the point from (1, 1) using some number of steps, and false otherwise.
//
// Example:
// Input: targetX = 6, targetY = 9
// Output: false
// Explanation: It is impossible to reach (6,9) from (1,1) using any sequence of moves, so false is returned.
//
// Constraints:
// 1 <= targetX, targetY <= 109
//

/**
 * @param {number} targetX
 * @param {number} targetY
 * @return {boolean}
 */
var isReachable = function(targetX, targetY) {
    while (targetX > 1 && targetY > 1) {
        if (targetX > targetY) {
            if (targetX % 2 === 0) {
                targetX /= 2;
            }
            else {
                targetX -= targetY;
            }
        }   
        else {
            if (targetY % 2 === 0) {
                targetY /= 2;
            }
            else {
                targetY -= targetX;
            }
        }
    }
    return targetX === 1 && targetY === 1;
};
