// Source: https://leetcode.com/problems/separate-squares-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.
//
// Find the minimum y-coordinate value of a horizontal line such that the total area covered by squares above the line equals the total area covered by squares below the line.
//
// Answers within 10-5 of the actual answer will be accepted.
//
// Note: Squares may overlap. Overlapping areas should be counted only once in this version.
//
// Example:
// Input: squares = [[0,0,1],[2,2,1]]
//
// Output: 1.00000
//
// Explanation:
//
//
//
// Any horizontal line between y = 1 and y = 2 results in an equal split, with 1 square unit above and 1 square unit below. The minimum y-value is 1.
//
// Constraints:
// 1 <= squares.length <= 5 * 104
// 	squares[i] = [xi, yi, li]
// 	squares[i].length == 3
// 	0 <= xi, yi <= 109
// 	1 <= li <= 109
// 	The total area of all the squares will not exceed 1015.
//

class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        using ll = long long;
        ll totalArea = 0;
        for (const auto& square : squares) {
            totalArea += (ll)square[2] * square[2];
        }
        
        double left = 0, right = 1e9;
        for (int iter = 0; iter < 100; ++iter) {
            double mid = left + (right - left) / 2.0;
            ll areaBelow = 0;
            
            // Calculate area below the line y = mid
            vector<pair<int, int>> events; // (x, type)
            for (const auto& square : squares) {
                int x = square[0];
                int y = square[1];
                int l = square[2];
                
                if (y >= mid) continue; // Entire square is above the line
                if (y + l <= mid) { // Entire square is below the line
                    areaBelow += (ll)l * l;
                    continue;
                }
                
                // Partial overlap
                events.emplace_back(x, 1); // Start of square
                events.emplace_back(x + l, -1); // End of square
            }
            
            sort(events.begin(), events.end());
            int active = 0;
            int prevX = 0;
            for (const auto& event : events) {
                int x = event.first;
                int type = event.second;
                
                if (active > 0) {
                    areaBelow += (ll)(x - prevX) * (mid - max(0.0, (double)(squares[0][1])));
                }
                
                active += type;
                prevX = x;
            }
            
            if (areaBelow * 2 < totalArea) {
                left = mid;
            } else {
                right = mid;
            }
        }
        
        return left;
    }
};
