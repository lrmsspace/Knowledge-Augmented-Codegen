// Source: https://leetcode.com/problems/rectangle-area-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D array of axis-aligned rectangles. Each rectangle[i] = [xi1, yi1, xi2, yi2] denotes the ith rectangle where (xi1, yi1) are the coordinates of the bottom-left corner, and (xi2, yi2) are the coordinates of the top-right corner.
//
// Calculate the total area covered by all rectangles in the plane. Any area covered by two or more rectangles should only be counted once.
//
// Return the total area. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: rectangles = [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
// Output: 6
// Explanation: A total area of 6 is covered by all three rectangles, as illustrated in the picture.
// From (1,1) to (2,2), the green and red rectangles overlap.
// From (1,0) to (2,3), all three rectangles overlap.
//
// Constraints:
// 1 <= rectangles.length <= 200
// 	rectanges[i].length == 4
// 	0 <= xi1, yi1, xi2, yi2 <= 109
// 	xi1 <= xi2
// 	yi1 <= yi2
// 	All rectangles have non zero area.
//

class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        const int MOD = 1e9 + 7;
        set<int> xSet, ySet;
        for (const auto& rect : rectangles) {
            xSet.insert(rect[0]);
            xSet.insert(rect[2]);
            ySet.insert(rect[1]);
            ySet.insert(rect[3]);
        }
        
        vector<int> xs(xSet.begin(), xSet.end());
        vector<int> ys(ySet.begin(), ySet.end());
        
        vector<vector<bool>> grid(xs.size() - 1, vector<bool>(ys.size() - 1, false));
        
        for (const auto& rect : rectangles) {
            int x1 = lower_bound(xs.begin(), xs.end(), rect[0]) - xs.begin();
            int x2 = lower_bound(xs.begin(), xs.end(), rect[2]) - xs.begin();
            int y1 = lower_bound(ys.begin(), ys.end(), rect[1]) - ys.begin();
            int y2 = lower_bound(ys.begin(), ys.end(), rect[3]) - ys.begin();
            
            for (int i = x1; i < x2; ++i) {
                for (int j = y1; j < y2; ++j) {
                    grid[i][j] = true;
                }
            }
        }
        
        long long area = 0;
        for (int i = 0; i < xs.size() - 1; ++i) {
            for (int j = 0; j < ys.size() - 1; ++j) {
                if (grid[i][j]) {
                    long long width = xs[i + 1] - xs[i];
                    long long height = ys[j + 1] - ys[j];
                    area = (area + width * height) % MOD;
                }
            }
        }
        
        return area;            
    }
};
