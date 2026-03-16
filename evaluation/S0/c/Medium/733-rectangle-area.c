// Source: https://leetcode.com/problems/rectangle-area/   |   Difficulty: Medium
//
// Problem Description:
// Given the coordinates of two rectilinear rectangles in a 2D plane, return the total area covered by the two rectangles.
//
// The first rectangle is defined by its bottom-left corner (ax1, ay1) and its top-right corner (ax2, ay2).
//
// The second rectangle is defined by its bottom-left corner (bx1, by1) and its top-right corner (bx2, by2).
//
// Example:
// Input: ax1 = -3, ay1 = 0, ax2 = 3, ay2 = 4, bx1 = 0, by1 = -1, bx2 = 9, by2 = 2
// Output: 45
//
// Constraints:
// -104 <= ax1 <= ax2 <= 104
// 	-104 <= ay1 <= ay2 <= 104
// 	-104 <= bx1 <= bx2 <= 104
// 	-104 <= by1 <= by2 <= 104
//

int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
    int areaA = (ax2 - ax1) * (ay2 - ay1);
    int areaB = (bx2 - bx1) * (by2 - by1);

    int overlapWidth = fmax(0, fmin(ax2, bx2) - fmax(ax1, bx1));
    int overlapHeight = fmax(0, fmin(ay2, by2) - fmax(ay1, by1));
    int overlapArea = overlapWidth * overlapHeight;

    return areaA + areaB - overlapArea;     
}
