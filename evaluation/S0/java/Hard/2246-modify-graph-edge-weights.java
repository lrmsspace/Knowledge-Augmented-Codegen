// Source: https://leetcode.com/problems/modify-graph-edge-weights/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected weighted connected graph containing n nodes labeled from 0 to n - 1, and an integer array edges where edges[i] = [ai, bi, wi] indicates that there is an edge between nodes ai and bi with weight wi.
//
// Some edges have a weight of -1 (wi = -1), while others have a positive weight (wi > 0).
//
// Your task is to modify all edges with a weight of -1 by assigning them positive integer values in the range [1, 2 * 109] so that the shortest distance between the nodes source and destination becomes equal to an integer target. If there are multiple modifications that make the shortest distance between source and destination equal to target, any of them will be considered correct.
//
// Return an array containing all edges (even unmodified ones) in any order if it is possible to make the shortest distance from source to destination equal to target, or an empty array if it's impossible.
//
// Note: You are not allowed to modify the weights of edges with initial positive weights.
//
// Example:
// Input: n = 5, edges = [[4,1,-1],[2,0,-1],[0,3,-1],[4,3,-1]], source = 0, destination = 1, target = 5
// Output: [[4,1,1],[2,0,1],[0,3,3],[4,3,1]]
// Explanation: The graph above shows a possible modification to the edges, making the distance from 0 to 1 equal to 5.
//
// Constraints:
// 1 <= n <= 100
// 	1 <= edges.length <= n * (n - 1) / 2
// 	edges[i].length == 3
// 	0 <= ai, bi < n
// 	wi = -1 or 1 <= wi <= 107
// 	ai != bi
// 	0 <= source, destination < n
// 	source != destination
// 	1 <= target <= 109
// 	The graph is connected, and there are no self-loops or repeated edges
//

class Solution {
    public int[][] modifiedGraphEdges(int n, int[][] edges, int source, int destination, int target) {
        int m = edges.length;
        int left = 1, right = (int) 2e9;
        int[][] result = new int[m];

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int[][] modifiedEdges = new int[m][3];

            for (int i = 0; i < m; i++) {
                modifiedEdges[i][0] = edges[i][0];
                modifiedEdges[i][1] = edges[i][1];
                modifiedEdges[i][2] = edges[i][2] == -1 ? mid : edges[i][2];
            }

            long dist = dijkstra(n, modifiedEdges, source, destination);

            if (dist == target) {
                return modifiedEdges;
            } else if (dist < target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return new int[0][0];           
    }
}
