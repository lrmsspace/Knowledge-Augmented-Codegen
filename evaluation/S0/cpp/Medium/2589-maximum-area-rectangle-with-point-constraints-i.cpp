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

class Solution {
public:
    int maxRectangleArea(vector<vector<int>>& points) {
        int n = points.size();
        unordered_set<string> pointSet;
        for (const auto& p : points) {
            pointSet.insert(to_string(p[0]) + "," + to_string(p[1]));
        }

        int maxArea = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    int x1 = points[i][0], y1 = points[i][1];
                    int x2 = points[j][0], y2 = points[j][1];
                    int x3 = points[k][0], y3 = points[k][1];

                    // Check if they can form a rectangle
                    if (x1 == x2 && y1 == y3) {
                        // Calculate the fourth point
                        int x4 = x3, y4 = y2;
                        if (pointSet.count(to_string(x4) + "," + to_string(y4))) {
                            int area = abs((x2 - x1) * (y3 - y1));
                            maxArea = max(maxArea, area);
                        }
                    } else if (x1 == x3 && y1 == y2) {
                        int x4 = x2, y4 = y3;
                        if (pointSet.count(to_string(x4) + "," + to_string(y4))) {
                            int area = abs((x3 - x1) * (y2 - y1));
                            maxArea = max(maxArea, area);
                        }
                    } else if (x2 == x3 && y2 == y1) {
                        int x4 = x1, y4 = y3;
                        if (pointSet.count(to_string(x4) + "," + to_string(y4))) {
                            int area = abs((x3 - x2) * (y1 - y2));
                            maxArea = max(maxArea, area);
                        }
                    }
                }
            }
        }

        return maxArea;         
    }
};
