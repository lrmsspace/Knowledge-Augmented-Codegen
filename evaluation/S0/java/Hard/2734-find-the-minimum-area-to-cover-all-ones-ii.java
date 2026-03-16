// Source: https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D binary array grid. You need to find 3 non-overlapping rectangles having non-zero areas with horizontal and vertical sides such that all the 1's in grid lie inside these rectangles.
//
// Return the minimum possible sum of the area of these rectangles.
//
// Note that the rectangles are allowed to touch.
//
// Example:
// Input: grid = [[1,0,1],[1,1,1]]
//
// Output: 5
//
// Explanation:
//
//
//
//
// 	The 1's at (0, 0) and (1, 0) are covered by a rectangle of area 2.
// 	The 1's at (0, 2) and (1, 2) are covered by a rectangle of area 2.
// 	The 1 at (1, 1) is covered by a rectangle of area 1.
//
// Constraints:
// 1 <= grid.length, grid[i].length <= 30
// 	grid[i][j] is either 0 or 1.
// 	The input is generated such that there are at least three 1's in grid.
//

class Solution {
    public int minimumSum(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int[][] preSum = new int[m + 1][n + 1];
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                preSum[i][j] = preSum[i - 1][j] + preSum[i][j - 1] - preSum[i - 1][j - 1] + grid[i - 1][j - 1];
            }
        }

        int minArea = Integer.MAX_VALUE;
        for (int r1 = 0; r1 < m - 2; r1++) {
            for (int r2 = r1 + 1; r2 < m - 1; r2++) {
                for (int c1 = 0; c1 < n - 2; c1++) {
                    for (int c2 = c1 + 1; c2 < n - 1; c2++) {
                        int area1 = getArea(preSum, 0, 0, r1, n - 1);
                        int area2 = getArea(preSum, r1 + 1, 0, r2, n - 1);
                        int area3 = getArea(preSum, r2 + 1, 0, m - 1, n - 1);
                        if (area1 > 0 && area2 > 0 && area3 > 0) {
                            minArea = Math.min(minArea, area1 + area2 + area3);
                        }

                        area1 = getArea(preSum, 0, 0, m - 1, c1);
                        area2 = getArea(preSum, 0, c1 + 1, m - 1, c2);
                        area3 = getArea(preSum, 0, c2 + 1, m - 1, n - 1);
                        if (area1 > 0 && area2 > 0 && area3 > 0) {
                            minArea = Math.min(minArea, area1 + area2 + area3);
                        }
                    }
                }
            }
        }

        return minArea == Integer.MAX_VALUE ? -1 : minArea;         
    }
}
