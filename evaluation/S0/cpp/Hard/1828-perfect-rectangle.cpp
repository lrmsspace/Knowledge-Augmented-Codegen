// Source: https://leetcode.com/problems/perfect-rectangle/   |   Difficulty: Hard
//
// Problem Description:
// Given an array rectangles where rectangles[i] = [xi, yi, ai, bi] represents an axis-aligned rectangle. The bottom-left point of the rectangle is (xi, yi) and the top-right point of it is (ai, bi).
//
// Return true if all the rectangles together form an exact cover of a rectangular region.
//
// Example:
// Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
// Output: true
// Explanation: All 5 rectangles together form an exact cover of a rectangular region.
//
// Constraints:
// 1 <= rectangles.length <= 2 * 104
// 	rectangles[i].length == 4
// 	-105 <= xi < ai <= 105
// 	-105 <= yi < bi <= 105
//

class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        map<pair<int, int>, int> cornerCount;
        long long areaSum = 0;
        int minX = INT_MAX, minY = INT_MAX;
        int maxX = INT_MIN, maxY = INT_MIN;
        
        for (const auto& rect : rectangles) {
            int x1 = rect[0], y1 = rect[1];
            int x2 = rect[2], y2 = rect[3];
            
            areaSum += (long long)(x2 - x1) * (y2 - y1);
            
            minX = min(minX, x1);
            minY = min(minY, y1);
            maxX = max(maxX, x2);
            maxY = max(maxY, y2);
            
            cornerCount[{x1, y1}]++;
            cornerCount[{x1, y2}]++;
            cornerCount[{x2, y1}]++;
            cornerCount[{x2, y2}]++;
        }
        
        long long expectedArea = (long long)(maxX - minX) * (maxY - minY);
        if (areaSum != expectedArea) return false;
        
        pair<int, int> corners[4] = {
            {minX, minY},
            {minX, maxY},
            {maxX, minY},
            {maxX, maxY}
        };
        
        for (const auto& corner : corners) {
            if (cornerCount[corner] != 1) return false;
            cornerCount.erase(corner);
        }
        
        for (const auto& entry : cornerCount) {
            if (entry.second % 2 != 0) return false;
        }
        
        return true;            
    }
};
