// Source: https://leetcode.com/problems/circle-and-rectangle-overlapping/   |   Difficulty: Medium
//
// Problem Description:
// You are given a circle represented as (radius, xCenter, yCenter) and an axis-aligned rectangle represented as (x1, y1, x2, y2), where (x1, y1) are the coordinates of the bottom-left corner, and (x2, y2) are the coordinates of the top-right corner of the rectangle.
//
// Return true if the circle and rectangle are overlapped otherwise return false. In other words, check if there is any point (xi, yi) that belongs to the circle and the rectangle at the same time.
//
// Example:
// Input: radius = 1, xCenter = 0, yCenter = 0, x1 = 1, y1 = -1, x2 = 3, y2 = 1
// Output: true
// Explanation: Circle and rectangle share the point (1,0).
//
// Constraints:
// 1 <= radius <= 2000
// 	-104 <= xCenter, yCenter <= 104
// 	-104 <= x1 < x2 <= 104
// 	-104 <= y1 < y2 <= 104
//

bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
    // Find the closest point on the rectangle to the circle's center
    int closestX = (xCenter < x1) ? x1 : (xCenter > x2) ? x2 : xCenter;
    int closestY = (yCenter < y1) ? y1 : (yCenter > y2) ? y2 : yCenter;

    // Calculate the distance between the circle's center and this closest point
    int deltaX = xCenter - closestX;
    int deltaY = yCenter - closestY;

    // Check if the distance is less than or equal to the radius
    return (deltaX * deltaX + deltaY * deltaY) <= (radius * radius);        
}
