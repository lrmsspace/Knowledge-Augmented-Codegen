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

int maxHeightOfTriangle(int red, int blue) {
    int height = 0;
    int totalBalls = red + blue;
    int ballsNeeded = 1;

    while (totalBalls >= ballsNeeded) {
        height++;
        totalBalls -= ballsNeeded;
        ballsNeeded++;
    }

    return height;      
}
