// Source: https://leetcode.com/problems/maximum-area-rectangle-with-point-constraints-ii/   |   Difficulty: Hard
//
// Problem Description:
// There are n points on an infinite plane. You are given two integer arrays xCoord and yCoord where (xCoord[i], yCoord[i]) represents the coordinates of the ith point.
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
// Input: xCoord = [1,1,3,3], yCoord = [1,3,1,3]
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
// 1 <= xCoord.length == yCoord.length <= 2 * 105
// 	0 <= xCoord[i], yCoord[i] <= 8 * 107
// 	All the given points are unique.
//

class Solution {
public:
    long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
        int n = xCoord.size();
        unordered_map<int, set<int>> xMap, yMap;
        
        for (int i = 0; i < n; i++) {
            xMap[xCoord[i]].insert(yCoord[i]);
            yMap[yCoord[i]].insert(xCoord[i]);
        }
        
        long long maxArea = -1;
        
        for (int i = 0; i < n; i++) {
            int x1 = xCoord[i];
            int y1 = yCoord[i];
            
            // Check all possible pairs of points sharing the same x-coordinate
            for (int y2 : xMap[x1]) {
                if (y2 == y1) continue;
                
                // For each pair, check all possible pairs of points sharing the same y-coordinate
                for (int x2 : yMap[y1]) {
                    if (x2 == x1) continue;
                    
                    // Check if the fourth corner exists
                    if (xMap.count(x2) && xMap[x2].count(y2)) {
                        long long area = abs((long long)(x2 - x1) * (y2 - y1));
                        maxArea = max(maxArea, area);
                    }
                }
            }
        }
        
        return maxArea;         
    }
};
