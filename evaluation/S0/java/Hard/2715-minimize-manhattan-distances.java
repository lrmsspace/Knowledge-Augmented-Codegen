// Source: https://leetcode.com/problems/minimize-manhattan-distances/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array points representing integer coordinates of some points on a 2D plane, where points[i] = [xi, yi].
//
// The distance between two points is defined as their Manhattan distance.
//
// Return the minimum possible value for maximum distance between any two points by removing exactly one point.
//
// Example:
// Input: points = [[3,10],[5,15],[10,2],[4,4]]
//
// Output: 12
//
// Explanation:
//
// The maximum distance after removing each point is the following:
//
//
// 	After removing the 0th point the maximum distance is between points (5, 15) and (10, 2), which is |5 - 10| + |15 - 2| = 18.
// 	After removing the 1st point the maximum distance is between points (3, 10) and (10, 2), which is |3 - 10| + |10 - 2| = 15.
// 	After removing the 2nd point the maximum distance is between points (5, 15) and (4, 4), which is |5 - 4| + |15 - 4| = 12.
// 	After removing the 3rd point the maximum distance is between points (5, 15) and (10, 2), which is |5 - 10| + |15 - 2| = 18.
//
//
// 12 is the minimum possible maximum distance between any two points after removing exactly one point.
//
// Constraints:
// 3 <= points.length <= 105
// 	points[i].length == 2
// 	1 <= points[i][0], points[i][1] <= 108
//

class Solution {
    public int minimumDistance(int[][] points) {
        int n = points.length;
        int[][] sum = new int[n][2];
        int[][] diff = new int[n][2];

        for (int i = 0; i < n; i++) {
            sum[i][0] = points[i][0] + points[i][1];
            sum[i][1] = i;
            diff[i][0] = points[i][0] - points[i][1];
            diff[i][1] = i;
        }

        Arrays.sort(sum, (a, b) -> Integer.compare(b[0], a[0]));
        Arrays.sort(diff, (a, b) -> Integer.compare(b[0], a[0]));

        int result = Integer.MAX_VALUE;

        for (int i = 0; i < n; i++) {
            int maxDist = 0;

            for (int j = 0; j < 4; j++) {
                if (sum[j][1] != i) {
                    maxDist = Math.max(maxDist, sum[0][0] - sum[j][0]);
                    break;
                }
            }

            for (int j = 0; j < 4; j++) {
                if (diff[j][1] != i) {
                    maxDist = Math.max(maxDist, diff[0][0] - diff[j][0]);
                    break;
                }
            }

            result = Math.min(result, maxDist);
        }

        return result;          
    }
}
