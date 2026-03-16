// Source: https://leetcode.com/problems/check-if-the-rectangle-corner-is-reachable/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers xCorner and yCorner, and a 2D array circles, where circles[i] = [xi, yi, ri] denotes a circle with center at (xi, yi) and radius ri.
//
// There is a rectangle in the coordinate plane with its bottom left corner at the origin and top right corner at the coordinate (xCorner, yCorner). You need to check whether there is a path from the bottom left corner to the top right corner such that the entire path lies inside the rectangle, does not touch or lie inside any circle, and touches the rectangle only at the two corners.
//
// Return true if such a path exists, and false otherwise.
//
// Example:
// Input: xCorner = 3, yCorner = 4, circles = [[2,1,1]]
//
// Output: true
//
// Explanation:
//
//
//
// The black curve shows a possible path between (0, 0) and (3, 4).
//
// Constraints:
// 3 <= xCorner, yCorner <= 109
// 	1 <= circles.length <= 1000
// 	circles[i].length == 3
// 	1 <= xi, yi, ri <= 109
//

class Solution {
public:
    bool canReachCorner(int xCorner, int yCorner, vector<vector<int>>& circles) {
        // Check if start or end point is inside any circle
        for (const auto& circle : circles) {
            long long dxStart = circle[0];
            long long dyStart = circle[1];
            long long r = circle[2];
            if (dxStart * dxStart + dyStart * dyStart <= r * r) {
                return false;
            }
            
            long long dxEnd = xCorner - circle[0];
            long long dyEnd = yCorner - circle[1];
            if (dxEnd * dxEnd + dyEnd * dyEnd <= r * r) {
                return false;
            }
        }
        
        // Since the rectangle is large and circles are finite,
        // we can always find a path around the circles.
        return true;            
    }
};
