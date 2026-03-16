// Source: https://leetcode.com/problems/minimum-area-rectangle-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of points in the X-Y plane points where points[i] = [xi, yi].
//
// Return the minimum area of any rectangle formed from these points, with sides not necessarily parallel to the X and Y axes. If there is not any such rectangle, return 0.
//
// Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: points = [[1,2],[2,1],[1,0],[0,1]]
// Output: 2.00000
// Explanation: The minimum area rectangle occurs at [1,2],[2,1],[1,0],[0,1], with an area of 2.
//
// Constraints:
// 1 <= points.length <= 50
// 	points[i].length == 2
// 	0 <= xi, yi <= 4 * 104
// 	All the given points are unique.
//

class Solution {
    public double minAreaFreeRect(int[][] points) {
        int n = points.length;
        double minArea = Double.MAX_VALUE;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                for (int k = 0; k < n; k++) {
                    if (i == k || j == k) continue;
                    double dotProduct = dot(points[i], points[j], points[k]);
                    if (Math.abs(dotProduct) > 1e-10) continue; // not a right angle
                    double area = distance(points[i], points[j]) * distance(points[i], points[k]);
                    minArea = Math.min(minArea, area);
                }
            }
        }
        return minArea == Double.MAX_VALUE ? 0 : minArea;           
    }
}
