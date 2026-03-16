// Source: https://leetcode.com/problems/maximum-area-of-a-piece-of-cake-after-horizontal-and-vertical-cuts/   |   Difficulty: Medium
//
// Problem Description:
// You are given a rectangular cake of size h x w and two arrays of integers horizontalCuts and verticalCuts where:
//
//
// 	horizontalCuts[i] is the distance from the top of the rectangular cake to the ith horizontal cut and similarly, and
// 	verticalCuts[j] is the distance from the left of the rectangular cake to the jth vertical cut.
//
//
// Return the maximum area of a piece of cake after you cut at each horizontal and vertical position provided in the arrays horizontalCuts and verticalCuts. Since the answer can be a large number, return this modulo 109 + 7.
//
// Example:
// Input: h = 5, w = 4, horizontalCuts = [1,2,4], verticalCuts = [1,3]
// Output: 4 
// Explanation: The figure above represents the given rectangular cake. Red lines are the horizontal and vertical cuts. After you cut the cake, the green piece of cake has the maximum area.
//
// Constraints:
// 2 <= h, w <= 109
// 	1 <= horizontalCuts.length <= min(h - 1, 105)
// 	1 <= verticalCuts.length <= min(w - 1, 105)
// 	1 <= horizontalCuts[i] < h
// 	1 <= verticalCuts[i] < w
// 	All the elements in horizontalCuts are distinct.
// 	All the elements in verticalCuts are distinct.
//

class Solution {
public:
    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        const int MOD = 1e9 + 7;

        sort(horizontalCuts.begin(), horizontalCuts.end());
        sort(verticalCuts.begin(), verticalCuts.end());

        long long maxH = horizontalCuts[0];
        for (int i = 1; i < horizontalCuts.size(); ++i) {
            maxH = max(maxH, (long long)(horizontalCuts[i] - horizontalCuts[i - 1]));
        }
        maxH = max(maxH, (long long)(h - horizontalCuts.back()));

        long long maxW = verticalCuts[0];
        for (int i = 1; i < verticalCuts.size(); ++i) {
            maxW = max(maxW, (long long)(verticalCuts[i] - verticalCuts[i - 1]));
        }
        maxW = max(maxW, (long long)(w - verticalCuts.back()));

        return (maxH * maxW) % MOD;         
    }
};
