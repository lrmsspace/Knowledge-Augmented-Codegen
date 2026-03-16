// Source: https://leetcode.com/problems/maximum-height-of-a-triangle/   |   Difficulty: Easy
//
// Problem Description:
// You are given two integers red and blue representing the count of red and blue colored balls. You have to arrange these balls to form a triangle such that the 1st row will have 1 ball, the 2nd row will have 2 balls, the 3rd row will have 3 balls, and so on.
//
// All the balls in a particular row should be the same color, and adjacent rows should have different colors.
//
// Return the maximum height of the triangle that can be achieved.
//
// Example:
// Input: red = 2, blue = 4
//
// Output: 3
//
// Explanation:
//
//
//
// The only possible arrangement is shown above.
//
// Constraints:
// 1 <= red, blue <= 100
//

/**
 * @param {number} red
 * @param {number} blue
 * @return {number}
 */
var maxHeightOfTriangle = function(red, blue) {
    let height = 0;
    let ballsNeeded = 1;
    while (red >= 0 && blue >= 0) {
        if (height % 2 === 0) {
            if (red >= ballsNeeded) {
                red -= ballsNeeded;
            } else {
                break;
            }
        } else {
            if (blue >= ballsNeeded) {
                blue -= ballsNeeded;
            } else {
                break;
            }
        }
        height++;
        ballsNeeded++;
    }
    return height;
};