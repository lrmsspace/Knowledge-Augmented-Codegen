// Source: https://leetcode.com/problems/maximize-the-distance-between-points-on-a-square/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer side, representing the edge length of a square with corners at (0, 0), (0, side), (side, 0), and (side, side) on a Cartesian plane.
//
// You are also given a positive integer k and a 2D integer array points, where points[i] = [xi, yi] represents the coordinate of a point lying on the boundary of the square.
//
// You need to select k elements among points such that the minimum Manhattan distance between any two points is maximized.
//
// Return the maximum possible minimum Manhattan distance between the selected k points.
//
// The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.
//
// Example:
// Input: side = 2, points = [[0,2],[2,0],[2,2],[0,0]], k = 4
//
// Output: 2
//
// Explanation:
//
//
//
// Select all four points.
//
// Constraints:
// 1 <= side <= 109
// 	4 <= points.length <= min(4 * side, 15 * 103)
// 	points[i] == [xi, yi]
// 	The input is generated such that:
// 	
// 		points[i] lies on the boundary of the square.
// 		All points[i] are unique.
// 	
// 	
// 	4 <= k <= min(25, points.length)
//

int maxDistance(int side, int** points, int pointsSize, int* pointsColSize, int k) {
    int n = pointsSize;
    int left = 0, right = 2 * side;
    int ans = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        /* Greedily select points with at least 'mid' distance apart */
        int count = 1; /* always select the first point */
        int lastX = points[0][0];
        int lastY = points[0][1];

        for (int i = 1; i < n; ++i) {
            int dist = abs(points[i][0] - lastX) + abs(points[i][1] - lastY);
            if (dist >= mid) {
                count++;
                lastX = points[i][0];
                lastY = points[i][1];
                if (count >= k) break; /* early exit if we already selected k points */
            }
        }

        if (count >= k) {
            ans = mid; /* mid is a valid minimum distance */
            left = mid + 1; /* try for a larger minimum distance */
        } else {
            right = mid - 1; /* try for a smaller minimum distance */
        }
    }

    return ans;     
}
