// Source: https://leetcode.com/problems/length-of-the-longest-increasing-path/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D array of integers coordinates of length n and an integer k, where 0 <= k < n.
//
// coordinates[i] = [xi, yi] indicates the point (xi, yi) in a 2D plane.
//
// An increasing path of length m is defined as a list of points (x1, y1), (x2, y2), (x3, y3), ..., (xm, ym) such that:
//
//
// 	xi < xi + 1 and yi < yi + 1 for all i where 1 <= i < m.
// 	(xi, yi) is in the given coordinates for all i where 1 <= i <= m.
//
//
// Return the maximum length of an increasing path that contains coordinates[k].
//
// Example:
// Input: coordinates = [[3,1],[2,2],[4,1],[0,0],[5,3]], k = 1
//
// Output: 3
//
// Explanation:
//
// (0, 0), (2, 2), (5, 3) is the longest increasing path that contains (2, 2).
//
// Constraints:
// 1 <= n == coordinates.length <= 105
// 	coordinates[i].length == 2
// 	0 <= coordinates[i][0], coordinates[i][1] <= 109
// 	All elements in coordinates are distinct.
// 	0 <= k <= n - 1
//

class Solution {
    public int maxPathLength(int[][] coordinates, int k) {
        int n = coordinates.length;
        int[][] points = new int[n][3];
        for (int i = 0; i < n; i++) {
            points[i][0] = coordinates[i][0];
            points[i][1] = coordinates[i][1];
            points[i][2] = i;
        }
        Arrays.sort(points, (a, b) -> a[0] != b[0] ? Integer.compare(a[0], b[0]) : Integer.compare(a[1], b[1]));

        int[] bit = new int[n + 1];

        int maxLength = 0;
        for (int[] point : points) {
            int x = point[0];
            int y = point[1];
            int index = point[2];

            int length = query(bit, y) + 1;
            if (index == k) {
                maxLength = length;
            }
            update(bit, y, length);
        }

        return maxLength;           
    }
}
