// Source: https://leetcode.com/problems/max-points-on-a-line/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of points where points[i] = [xi, yi] represents a point on the X-Y plane, return the maximum number of points that lie on the same straight line.
//
// Example:
// Input: points = [[1,1],[2,2],[3,3]]
// Output: 3
//
// Constraints:
// 1 <= points.length <= 300
// 	points[i].length == 2
// 	-104 <= xi, yi <= 104
// 	All the points are unique.
//

int maxPoints(int** points, int pointsSize, int* pointsColSize) {
    if (pointsSize <= 2) return pointsSize;

    int maxPointsOnLine = 0;
    for (int i = 0; i < pointsSize; ++i) {
        for (int j = i + 1; j < pointsSize; ++j) {
            int count = 2; // points i and j are on the line
            for (int k = 0; k < pointsSize; ++k) {
                if (k != i && k != j) {
                    // Check if point k is on the line formed by points i and j
                    if ((points[j][1] - points[i][1]) * (points[k][0] - points[i][0]) ==
                        (points[k][1] - points[i][1]) * (points[j][0] - points[i][0])) {
                        count++;
                    }
                }
            }
            if (count > maxPointsOnLine) {
                maxPointsOnLine = count;
            }
        }
    }
    return maxPointsOnLine;     
}
