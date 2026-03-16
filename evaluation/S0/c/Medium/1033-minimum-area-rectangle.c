// Source: https://leetcode.com/problems/minimum-area-rectangle/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of points in the X-Y plane points where points[i] = [xi, yi].
//
// Return the minimum area of a rectangle formed from these points, with sides parallel to the X and Y axes. If there is not any such rectangle, return 0.
//
// Example:
// Input: points = [[1,1],[1,3],[3,1],[3,3],[2,2]]
// Output: 4
//
// Constraints:
// 1 <= points.length <= 500
// 	points[i].length == 2
// 	0 <= xi, yi <= 4 * 104
// 	All the given points are unique.
//

int minAreaRect(int** points, int pointsSize, int* pointsColSize) {
    int minArea = INT_MAX;
    bool pointExists[40001][40001] = { false };

    for (int i = 0; i < pointsSize; i++) {
        pointExists[points[i][0]][points[i][1]] = true;
    }

    for (int i = 0; i < pointsSize; i++) {
        for (int j = i + 1; j < pointsSize; j++) {
            if (points[i][0] != points[j][0] && points[i][1] != points[j][1]) {
                if (pointExists[points[i][0]][points[j][1]] && pointExists[points[j][0]][points[i][1]]) {
                    int area = abs(points[i][0] - points[j][0]) * abs(points[i][1] - points[j][1]);
                    if (area < minArea) {
                        minArea = area;
                    }
                }
            }
        }
    }

    return minArea == INT_MAX ? 0 : minArea;        
}
