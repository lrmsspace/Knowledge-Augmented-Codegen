// Source: https://leetcode.com/problems/check-if-it-is-a-straight-line/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array coordinates, coordinates[i] = [x, y], where [x, y] represents the coordinate of a point. Check if these points make a straight line in the XY plane.
//
// Example:
// Input: coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
// Output: true
//
// Constraints:
// 2 <= coordinates.length <= 1000
// 	coordinates[i].length == 2
// 	-10^4 <= coordinates[i][0], coordinates[i][1] <= 10^4
// 	coordinates contains no duplicate point.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean checkStraightLine(int[][] coordinates) {
        int n = coordinates.length;
        if (n <= 2) {
            return true; // Any two points are always collinear
        }

        // Calculate the slope of the line formed by the first two points
        int x0 = coordinates[0][0];
        int y0 = coordinates[0][1];
        int x1 = coordinates[1][0];
        int y1 = coordinates[1][1];

        // To avoid division by zero, we will use cross multiplication to compare slopes
        for (int i = 2; i < n; i++) {
            int x2 = coordinates[i][0];
            int y2 = coordinates[i][1];

            // Check if the slope between (x0, y0) and (x1, y1) is the same as the slope between (x0, y0) and (x2, y2)
            if ((y1 - y0) * (x2 - x0) != (y2 - y0) * (x1 - x0)) {
                return false; // If slopes are different, points are not collinear
            }
        }

        return true; // All points are collinear            
    }
}
