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

class Solution {
public:
    int minAreaRect(vector<vector<int>>& points) {
        unordered_set<long long> pointSet;
        for (const auto& p : points) {
            long long code = ((long long)p[0] << 16) | p[1];
            pointSet.insert(code);
        }

        int minArea = INT_MAX;
        int n = points.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                const auto& p1 = points[i];
                const auto& p2 = points[j];

                // Check if p1 and p2 can be diagonal corners of a rectangle
                if (p1[0] != p2[0] && p1[1] != p2[1]) {
                    long long code1 = ((long long)p1[0] << 16) | p2[1];
                    long long code2 = ((long long)p2[0] << 16) | p1[1];

                    // Check if the other two corners exist
                    if (pointSet.count(code1) && pointSet.count(code2)) {
                        int area = abs(p1[0] - p2[0]) * abs(p1[1] - p2[1]);
                        minArea = min(minArea, area);
                    }
                }
            }
        }

        return minArea == INT_MAX ? 0 : minArea;            
    }
};
