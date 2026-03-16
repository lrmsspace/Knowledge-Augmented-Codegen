// Source: https://leetcode.com/problems/length-of-the-longest-increasing-path/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D array of integers coordinates of length n and an integer k, where 0 <= k < n.
//
// coordinates[i] = [xi, yi] indicates the point (xi, yi) in a 2D plane.
//
// An increasing path of length m is defined as a list of points (x1, y1), (x2, y2), (x3, y3), ..., (xm, ym) such that:
//
//
// 	xi < xi + 1 and yi < yi + 1 for all i where 1 <= i < m.
// 	(xi, yi) is in the given coordinates for all i where 1 <= i <= m.
//
//
// Return the maximum length of an increasing path that contains coordinates[k].
//
// Example:
// Input: coordinates = [[3,1],[2,2],[4,1],[0,0],[5,3]], k = 1
//
// Output: 3
//
// Explanation:
//
// (0, 0), (2, 2), (5, 3) is the longest increasing path that contains (2, 2).
//
// Constraints:
// 1 <= n == coordinates.length <= 105
// 	coordinates[i].length == 2
// 	0 <= coordinates[i][0], coordinates[i][1] <= 109
// 	All elements in coordinates are distinct.
// 	0 <= k <= n - 1
//

class Solution {
public:
    int maxPathLength(vector<vector<int>>& coordinates, int k) {
        int n = coordinates.size();
        vector<int> xs(n), ys(n);
        for (int i = 0; i < n; i++) {
            xs[i] = coordinates[i][0];
            ys[i] = coordinates[i][1];
        }
        
        // Coordinate compression
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        
        vector<vector<int>> points(xs.size() + 1, vector<int>(ys.size() + 1, 0));
        
        // DP with 2D BIT
        auto bitUpdate = [&](int x, int y, int val) {
            for (int i = x; i < points.size(); i += i & -i) {
                for (int j = y; j < points[0].size(); j += j & -j) {
                    points[i][j] = max(points[i][j], val);
                }
            }
        };
        
        auto bitQuery = [&](int x, int y) {
            int res = 0;
            for (int i = x; i > 0; i -= i & -i) {
                for (int j = y; j > 0; j -= j & -j) {
                    res = max(res, points[i][j]);
                }
            }
            return res;
        };
        
        int result = 0;
        for (int i = 0; i < n; i++) {
            int cx = lower_bound(xs.begin(), xs.end(), coordinates[i][0]) - xs.begin() + 1;
            int cy = lower_bound(ys.begin(), ys.end(), coordinates[i][1]) - ys.begin() + 1;
            
            int currLen = bitQuery(cx - 1, cy - 1) + 1;
            bitUpdate(cx, cy, currLen);
            
            if (i == k) {
                result = currLen;
            }
        }
        
        return result;          
    }
};
