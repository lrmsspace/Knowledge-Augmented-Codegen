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

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 2) return n;
        
        int maxPointsOnLine = 1;
        
        for (int i = 0; i < n; i++) {
            unordered_map<string, int> slopeCount;
            int duplicatePoints = 0;
            int currentMax = 0;
            
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];
                
                if (dx == 0 && dy == 0) {
                    duplicatePoints++;
                    continue;
                }
                
                int gcdVal = gcd(dx, dy);
                if (gcdVal != 0) {
                    dx /= gcdVal;
                    dy /= gcdVal;
                }
                
                string slopeKey = to_string(dy) + "/" + to_string(dx);
                slopeCount[slopeKey]++;
                currentMax = max(currentMax, slopeCount[slopeKey]);
            }
            
            maxPointsOnLine = max(maxPointsOnLine, currentMax + duplicatePoints + 1);
        }
        
        return maxPointsOnLine;         
    }
};
