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
    public long maxArea(int[][] coords) {
        long maxArea = -1;
        int n = coords.length;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (coords[i][0] == coords[j][0] || coords[i][1] == coords[j][1]) {
                    continue;
                }

                int base = Math.abs(coords[i][0] - coords[j][0]);
                int height = Math.abs(coords[i][1] - coords[j][1]);
                long area = (long) base * height;

                maxArea = Math.max(maxArea, area);
            }
        }

        return maxArea;         
    }
}
