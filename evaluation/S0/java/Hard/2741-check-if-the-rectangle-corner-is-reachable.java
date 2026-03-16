// Source: https://leetcode.com/problems/check-if-the-rectangle-corner-is-reachable/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers xCorner and yCorner, and a 2D array circles, where circles[i] = [xi, yi, ri] denotes a circle with center at (xi, yi) and radius ri.
//
// There is a rectangle in the coordinate plane with its bottom left corner at the origin and top right corner at the coordinate (xCorner, yCorner). You need to check whether there is a path from the bottom left corner to the top right corner such that the entire path lies inside the rectangle, does not touch or lie inside any circle, and touches the rectangle only at the two corners.
//
// Return true if such a path exists, and false otherwise.
//
// Example:
// Input: xCorner = 3, yCorner = 4, circles = [[2,1,1]]
//
// Output: true
//
// Explanation:
//
//
//
// The black curve shows a possible path between (0, 0) and (3, 4).
//
// Constraints:
// 3 <= xCorner, yCorner <= 109
// 	1 <= circles.length <= 1000
// 	circles[i].length == 3
// 	1 <= xi, yi, ri <= 109
//

class Solution {
    public boolean canReachCorner(int xCorner, int yCorner, int[][] circles) {
        int n = circles.length;
        boolean[] visited = new boolean[n];
        for (int i = 0; i < n; i++) {
            int x = circles[i][0], y = circles[i][1], r = circles[i][2];
            if (isPointInCircle(0, 0, x, y, r)) {
                return false;
            }
        }
        for (int i = 0; i < n; i++) {
            int x = circles[i][0], y = circles[i][1], r = circles[i][2];
            if (isPointInCircle(xCorner, yCorner, x, y, r)) {
                return false;
            }
        }
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                if (dfs(i, circles, visited, xCorner, yCorner)) {
                    return false;
                }
            }
        }
        return true;            
    }
}
