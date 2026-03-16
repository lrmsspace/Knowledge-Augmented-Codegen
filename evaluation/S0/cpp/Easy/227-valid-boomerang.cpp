// Source: https://leetcode.com/problems/valid-boomerang/   |   Difficulty: Easy
//
// Problem Description:
// Given an array points where points[i] = [xi, yi] represents a point on the X-Y plane, return true if these points are a boomerang.
//
// A boomerang is a set of three points that are all distinct and not in a straight line.
//
// Example:
// Input: points = [[1,1],[2,3],[3,2]]
// Output: true
//
// Constraints:
// points.length == 3
// 	points[i].length == 2
// 	0 <= xi, yi <= 100
//

class Solution {
public:
    bool isBoomerang(vector<vector<int>>& points) {
        int x1 = points[0][0], y1 = points[0][1];
        int x2 = points[1][0], y2 = points[1][1];
        int x3 = points[2][0], y3 = points[2][1];

        // Check for distinct points
        if ((x1 == x2 && y1 == y2) || (x1 == x3 && y1 == y3) || (x2 == x3 && y2 == y3)) {
            return false;
        }

        // Check for collinearity using the area of triangle method
        return (y2 - y1) * (x3 - x2) != (y3 - y2) * (x2 - x1);          
    }
};
