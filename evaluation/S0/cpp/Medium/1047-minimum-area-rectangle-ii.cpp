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
public:
    double minAreaFreeRect(vector<vector<int>>& points) {
        int n = points.size();
        double minArea = DBL_MAX;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j == i) continue;
                for (int k = 0; k < n; ++k) {
                    if (k == i || k == j) continue;

                    // Check if angle at point i is 90 degrees
                    int dx1 = points[j][0] - points[i][0];
                    int dy1 = points[j][1] - points[i][1];
                    int dx2 = points[k][0] - points[i][0];
                    int dy2 = points[k][1] - points[i][1];
                    if (dx1 * dx2 + dy1 * dy2 != 0) continue;

                    // Calculate the fourth point
                    int x4 = points[j][0] + dx2;
                    int y4 = points[j][1] + dy2;

                    // Check if the fourth point exists
                    if (find(points.begin(), points.end(), vector<int>{x4, y4}) != points.end()) {
                        double area = sqrt(dx1 * dx1 + dy1 * dy1) * sqrt(dx2 * dx2 + dy2 * dy2);
                        minArea = min(minArea, area);
                    }
                }
            }
        }
        return minArea == DBL_MAX ? 0 : minArea;            
    }
};
