// Source: https://leetcode.com/problems/minimize-manhattan-distances/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array points representing integer coordinates of some points on a 2D plane, where points[i] = [xi, yi].
//
// The distance between two points is defined as their Manhattan distance.
//
// Return the minimum possible value for maximum distance between any two points by removing exactly one point.
//
// Example:
// Input: points = [[3,10],[5,15],[10,2],[4,4]]
//
// Output: 12
//
// Explanation:
//
// The maximum distance after removing each point is the following:
//
//
// 	After removing the 0th point the maximum distance is between points (5, 15) and (10, 2), which is |5 - 10| + |15 - 2| = 18.
// 	After removing the 1st point the maximum distance is between points (3, 10) and (10, 2), which is |3 - 10| + |10 - 2| = 15.
// 	After removing the 2nd point the maximum distance is between points (5, 15) and (4, 4), which is |5 - 4| + |15 - 4| = 12.
// 	After removing the 3rd point the maximum distance is between points (5, 15) and (10, 2), which is |5 - 10| + |15 - 2| = 18.
//
//
// 12 is the minimum possible maximum distance between any two points after removing exactly one point.
//
// Constraints:
// 3 <= points.length <= 105
// 	points[i].length == 2
// 	1 <= points[i][0], points[i][1] <= 108
//

class Solution {
public:
    int minimumDistance(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 3) return 0;
        
        // Precompute the distances
        vector<vector<int>> dist(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                dist[i][j] = abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
                dist[j][i] = dist[i][j];
            }
        }
        
        int result = INT_MAX;
        
        // Try removing each point
        for (int removeIdx = 0; removeIdx < n; removeIdx++) {
            int maxDist = 0;
            for (int i = 0; i < n; i++) {
                if (i == removeIdx) continue;
                for (int j = i + 1; j < n; j++) {
                    if (j == removeIdx) continue;
                    maxDist = max(maxDist, dist[i][j]);
                }
            }
            result = min(result, maxDist);
        }
        
        return result;          
    }
};
