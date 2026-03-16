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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long maxRectangleArea(vector<int>& xCoord, vector<int>& yCoord) {
        int n = xCoord.size();
        unordered_set<long long> points;
        for (int i = 0; i < n; ++i) {
            points.insert((long long)xCoord[i] * 100000000 + yCoord[i]);
        }

        long long maxArea = -1;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (xCoord[i] != xCoord[j] && yCoord[i] != yCoord[j]) {
                    long long area = abs((long long)(xCoord[j] - xCoord[i]) * (yCoord[j] - yCoord[i]));
                    if (area > maxArea) {
                        if (points.count((long long)xCoord[i] * 100000000 + yCoord[j]) &&
                            points.count((long long)xCoord[j] * 100000000 + yCoord[i])) {
                            maxArea = area;
                        }
                    }
                }
            }
        }

        return maxArea;         
    }
};
