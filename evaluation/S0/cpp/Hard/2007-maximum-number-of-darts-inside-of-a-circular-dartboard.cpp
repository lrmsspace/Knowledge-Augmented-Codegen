// Source: https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/   |   Difficulty: Hard
//
// Problem Description:
// Alice is throwing n darts on a very large wall. You are given an array darts where darts[i] = [xi, yi] is the position of the ith dart that Alice threw on the wall.
//
// Bob knows the positions of the n darts on the wall. He wants to place a dartboard of radius r on the wall so that the maximum number of darts that Alice throws lie on the dartboard.
//
// Given the integer r, return the maximum number of darts that can lie on the dartboard.
//
// Example:
// Input: darts = [[-2,0],[2,0],[0,2],[0,-2]], r = 2
// Output: 4
// Explanation: Circle dartboard with center in (0,0) and radius = 2 contain all points.
//
// Constraints:
// 1 <= darts.length <= 100
// 	darts[i].length == 2
// 	-104 <= xi, yi <= 104
// 	All the darts are unique
// 	1 <= r <= 5000
//

class Solution {
public:
    int numPoints(vector<vector<int>>& darts, int r) {
        int n = darts.size();
        int maxCount = 1;
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                vector<pair<double, double>> centers = getCircleCenters(darts[i], darts[j], r);
                
                for (auto& center : centers) {
                    int count = 0;
                    for (int k = 0; k < n; k++) {
                        if (isInsideCircle(center, darts[k], r)) {
                            count++;
                        }
                    }
                    maxCount = max(maxCount, count);
                }
            }
        }
        
        return maxCount;            
    }
};
