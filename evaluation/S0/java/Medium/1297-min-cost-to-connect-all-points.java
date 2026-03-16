// Source: https://leetcode.com/problems/min-cost-to-connect-all-points/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].
//
// The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.
//
// Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.
//
// Example:
// Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
// Output: 20
// Explanation: 
//
// We can connect the points as shown above to get the minimum cost of 20.
// Notice that there is a unique path between every pair of points.
//
// Constraints:
// 1 <= points.length <= 1000
// 	-106 <= xi, yi <= 106
// 	All pairs (xi, yi) are distinct.
//

class Solution {
    public int minCostConnectPoints(int[][] points) {
        int n = points.length;
        boolean[] inMST = new boolean[n];
        int[] minDist = new int[n];
        Arrays.fill(minDist, Integer.MAX_VALUE);
        minDist[0] = 0;

        int totalCost = 0;

        for (int i = 0; i < n; i++) {
            int u = -1;
            for (int j = 0; j < n; j++) {
                if (!inMST[j] && (u == -1 || minDist[j] < minDist[u])) {
                    u = j;
                }
            }

            inMST[u] = true;
            totalCost += minDist[u];

            for (int v = 0; v < n; v++) {
                if (!inMST[v]) {
                    int dist = Math.abs(points[u][0] - points[v][0]) + Math.abs(points[u][1] - points[v][1]);
                    minDist[v] = Math.min(minDist[v], dist);
                }
            }
        }

        return totalCost;           
    }
}
