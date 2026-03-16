// Source: https://leetcode.com/problems/find-maximum-area-of-a-triangle/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D array coords of size n x 2, representing the coordinates of n points in an infinite Cartesian plane.
//
// Find twice the maximum area of a triangle with its corners at any three elements from coords, such that at least one side of this triangle is parallel to the x-axis or y-axis. Formally, if the maximum area of such a triangle is A, return 2 * A.
//
// If no such triangle exists, return -1.
//
// Note that a triangle cannot have zero area.
//
// Example:
// Input: coords = [[1,1],[1,2],[3,2],[3,3]]
//
// Output: 2
//
// Explanation:
//
//
//
// The triangle shown in the image has a base 1 and height 2. Hence its area is 1/2 * base * height = 1.
//
// Constraints:
// 1 <= n == coords.length <= 105
// 	1 <= coords[i][0], coords[i][1] <= 106
// 	All coords[i] are unique.
//

class Solution {
public:
    long long maxArea(vector<vector<int>>& coords) {
        unordered_map<int, vector<int>> xMap, yMap;
        for (const auto& coord : coords) {
            xMap[coord[0]].push_back(coord[1]);
            yMap[coord[1]].push_back(coord[0]);
        }

        long long maxArea = -1;
        for (const auto& coord : coords) {
            int x = coord[0], y = coord[1];

            const auto& ys = xMap[x];
            for (const auto& y2 : ys) {
                if (y2 == y) continue;
                long long height = abs(y2 - y);

                const auto& xs = yMap[y];
                for (const auto& x2 : xs) {
                    if (x2 == x) continue;
                    long long base = abs(x2 - x);
                    long long area = base * height;
                    maxArea = max(maxArea, area);
                }
            }
        }

        return maxArea;         
    }
};
