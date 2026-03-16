// Source: https://leetcode.com/problems/largest-triangle-area/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of points on the X-Y plane points where points[i] = [xi, yi], return the area of the largest triangle that can be formed by any three different points. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: points = [[0,0],[0,1],[1,0],[0,2],[2,0]]
// Output: 2.00000
// Explanation: The five points are shown in the above figure. The red triangle is the largest.
//
// Constraints:
// 3 <= points.length <= 50
// 	-50 <= xi, yi <= 50
// 	All the given points are unique.
//

double largestTriangleArea(int** points, int pointsSize, int* pointsColSize) {
    double max_area = 0.0;
    for (int i = 0; i < pointsSize - 2; i++) {
        for (int j = i + 1; j < pointsSize - 1; j++) {
            for (int k = j + 1; k < pointsSize; k++) {
                double area = 0.5 * fabs(
                    points[i][0] * (points[j][1] - points[k][1]) +
                    points[j][0] * (points[k][1] - points[i][1]) +
                    points[k][0] * (points[i][1] - points[j][1])
                );
                if (area > max_area) {
                    max_area = area;
                }
            }
        }
    }
    return max_area;        
}
