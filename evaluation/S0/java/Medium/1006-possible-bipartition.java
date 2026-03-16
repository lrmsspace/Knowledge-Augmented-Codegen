// Source: https://leetcode.com/problems/possible-bipartition/   |   Difficulty: Medium
//
// Problem Description:
// We want to split a group of n people (labeled from 1 to n) into two groups of any size. Each person may dislike some other people, and they should not go into the same group.
//
// Given the integer n and the array dislikes where dislikes[i] = [ai, bi] indicates that the person labeled ai does not like the person labeled bi, return true if it is possible to split everyone into two groups in this way.
//
// Example:
// Input: n = 4, dislikes = [[1,2],[1,3],[2,4]]
// Output: true
// Explanation: The first group has [1,4], and the second group has [2,3].
//
// Constraints:
// 1 <= n <= 2000
// 	0 <= dislikes.length <= 104
// 	dislikes[i].length == 2
// 	1 <= ai < bi <= n
// 	All the pairs of dislikes are unique.
//

class Solution {
    public boolean possibleBipartition(int n, int[][] dislikes) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] dislike : dislikes) {
            graph.get(dislike[0]).add(dislike[1]);
            graph.get(dislike[1]).add(dislike[0]);
        }

        int[] colors = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            if (colors[i] == 0) {
                if (!dfs(graph, colors, i, 1)) {
                    return false;
                }
            }
        }
        return true;            
    }
}
