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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maxHeightOfTriangle(int red, int blue) {
        int height = 0;
        int ballsNeeded = 1; // Number of balls needed for the current row

        while (true) {
            if (height % 2 == 0) { // Even row: use red balls
                if (red >= ballsNeeded) {
                    red -= ballsNeeded;
                } else {
                    break; // Not enough red balls to continue
                }
            } else { // Odd row: use blue balls
                if (blue >= ballsNeeded) {
                    blue -= ballsNeeded;
                } else {
                    break; // Not enough blue balls to continue
                }
            }
            height++;
            ballsNeeded++; // Next row needs one more ball
        }

        return height;          
    }
};
