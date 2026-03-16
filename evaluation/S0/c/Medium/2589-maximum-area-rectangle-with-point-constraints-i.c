// Source: https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array points where points[i] = [xi, yi] represents the coordinates of a point on an infinite plane.
//
// Your task is to find the maximum area of a rectangle that:
//
//
// 	Can be formed using four of these points as its corners.
// 	Does not contain any other point inside or on its border.
// 	Has its edges parallel to the axes.
//
//
// Return the maximum area that you can obtain or -1 if no such rectangle is possible.
//
// Example:
// Input: points = [[1,1],[1,3],[3,1],[3,3]]
//
// Output: 4
//
// Explanation:
//
//
//
// We can make a rectangle with these 4 points as corners and there is no other point that lies inside or on the border. Hence, the maximum possible area would be 4.
//
// Constraints:
// 1 <= points.length <= 10
// 	points[i].length == 2
// 	0 <= xi, yi <= 100
// 	All the given points are unique.
//

int maxRectangleArea(int** points, int pointsSize, int* pointsColSize) {
    int maxArea = -1;
    for (int i = 0; i < pointsSize; i++) {
        for (int j = 0; j < pointsSize; j++) {
            for (int k = 0; k < pointsSize; k++) {
                for (int l = 0; l < pointsSize; l++) {
                    if (i != j && i != k && i != l && j != k && j != l && k != l) {
                        int x1 = points[i][0], y1 = points[i][1];
                        int x2 = points[j][0], y2 = points[j][1];
                        int x3 = points[k][0], y3 = points[k][1];
                        int x4 = points[l][0], y4 = points[l][1];

                        if ((x1 == x2 && y1 == y3 && x3 == x4 && y2 == y4) ||
                            (x1 == x3 && y1 == y2 && x2 == x4 && y3 == y4) ||
                            (x1 == x4 && y1 == y2 && x2 == x3 && y4 == y3)) {

                            int area = abs((x2 - x1) * (y3 - y1));
                            int valid = 1;

                            for (int m = 0; m < pointsSize; m++) {
                                if (m != i && m != j && m != k && m != l) {
                                    int xm = points[m][0], ym = points[m][1];
                                    if (xm >= fmin(x1, x2) && xm <= fmax(x1, x2) &&
                                        ym >= fmin(y1, y3) && ym <= fmax(y1, y3)) {
                                        valid = 0;
                                        break;
                                    }
                                }
                            }

                            if (valid && area > maxArea) {
                                maxArea = area;
                            }
                        }
                    }
                }
            }
        }
    }
    return maxArea;     
}
