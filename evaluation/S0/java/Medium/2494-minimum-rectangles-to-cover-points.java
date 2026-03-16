// Source: https://leetcode.com/problems/minimum-rectangles-to-cover-points/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array points, where points[i] = [xi, yi]. You are also given an integer w. Your task is to cover all the given points with rectangles.
//
// Each rectangle has its lower end at some point (x1, 0) and its upper end at some point (x2, y2), where x1 <= x2, y2 >= 0, and the condition x2 - x1 <= w must be satisfied for each rectangle.
//
// A point is considered covered by a rectangle if it lies within or on the boundary of the rectangle.
//
// Return an integer denoting the minimum number of rectangles needed so that each point is covered by at least one rectangle.
//
// Note: A point may be covered by more than one rectangle.
//
// Example:
// Input: points = [[2,1],[1,0],[1,4],[1,8],[3,5],[4,6]], w = 1
//
// Output: 2
//
// Explanation: 
//
// The image above shows one possible placement of rectangles to cover the points:
//
//
// 	A rectangle with a lower end at (1, 0) and its upper end at (2, 8)
// 	A rectangle with a lower end at (3, 0) and its upper end at (4, 8)
//
// Constraints:
// 1 <= points.length <= 105
// 	points[i].length == 2
// 	0 <= xi == points[i][0] <= 109
// 	0 <= yi == points[i][1] <= 109
// 	0 <= w <= 109
// 	All pairs (xi, yi) are distinct.
//

class Solution {
    public int minRectanglesToCoverPoints(int[][] points, int w) {
        // Sort points based on x-coordinate
        Arrays.sort(points, (a, b) -> Integer.compare(a[0], b[0]));

        int rectangles = 0;
        int i = 0;
        int n = points.length;

        while (i < n) {
            rectangles++;
            int coverLimit = points[i][0] + w;

            // Move i to the right as long as points are within the current rectangle's width
            while (i < n && points[i][0] <= coverLimit) {
                i++;
            }
        }

        return rectangles;          
    }
}
