// Source: https://leetcode.com/problems/find-center-of-star-graph/   |   Difficulty: Easy
//
// Problem Description:
// There is an undirected star graph consisting of n nodes labeled from 1 to n. A star graph is a graph where there is one center node and exactly n - 1 edges that connect the center node with every other node.
//
// You are given a 2D integer array edges where each edges[i] = [ui, vi] indicates that there is an edge between the nodes ui and vi. Return the center of the given star graph.
//
// Example:
// Input: edges = [[1,2],[2,3],[4,2]]
// Output: 2
// Explanation: As shown in the figure above, node 2 is connected to every other node, so 2 is the center.
//
// Constraints:
// 3 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	1 <= ui, vi <= n
// 	ui != vi
// 	The given edges represent a valid star graph.
//

class Solution {
    public int findCenter(int[][] edges) {
        // The center node must appear in both of the first two edges
        int[] edge1 = edges[0];
        int[] edge2 = edges[1];

        if (edge1[0] == edge2[0] || edge1[0] == edge2[1]) {
            return edge1[0];
        } else {
            return edge1[1];
        }           
    }
}
