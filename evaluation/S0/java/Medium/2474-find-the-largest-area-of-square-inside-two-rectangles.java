// Source: https://leetcode.com/problems/find-the-largest-area-of-square-inside-two-rectangles/   |   Difficulty: Medium
//
// Problem Description:
// There exist n rectangles in a 2D plane with edges parallel to the x and y axis. You are given two 2D integer arrays bottomLeft and topRight where bottomLeft[i] = [a_i, b_i] and topRight[i] = [c_i, d_i] represent the bottom-left and top-right coordinates of the ith rectangle, respectively.
//
// You need to find the maximum area of a square that can fit inside the intersecting region of at least two rectangles. Return 0 if such a square does not exist.
//
// Example:
// Input: bottomLeft = [[1,1],[2,2],[3,1]], topRight = [[3,3],[4,4],[6,6]]
//
// Output: 1
//
// Explanation:
//
// A square with side length 1 can fit inside either the intersecting region of rectangles 0 and 1 or the intersecting region of rectangles 1 and 2. Hence the maximum area is 1. It can be shown that a square with a greater side length can not fit inside any intersecting region of two rectangles.
//
// Constraints:
// n == bottomLeft.length == topRight.length
// 	2 <= n <= 103
// 	bottomLeft[i].length == topRight[i].length == 2
// 	1 <= bottomLeft[i][0], bottomLeft[i][1] <= 107
// 	1 <= topRight[i][0], topRight[i][1] <= 107
// 	bottomLeft[i][0] < topRight[i][0]
// 	bottomLeft[i][1] < topRight[i][1]
//

class Solution {
    public long largestSquareArea(int[][] bottomLeft, int[][] topRight) {
        int n = bottomLeft.length;
        long maxArea = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int x1 = Math.max(bottomLeft[i][0], bottomLeft[j][0]);
                int y1 = Math.max(bottomLeft[i][1], bottomLeft[j][1]);
                int x2 = Math.min(topRight[i][0], topRight[j][0]);
                int y2 = Math.min(topRight[i][1], topRight[j][1]);

                if (x1 < x2 && y1 < y2) {
                    int sideLength = Math.min(x2 - x1, y2 - y1);
                    long area = (long) sideLength * sideLength;
                    maxArea = Math.max(maxArea, area);
                }
            }
        }

        return maxArea;         
    }
}
