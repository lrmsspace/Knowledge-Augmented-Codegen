// Source: https://leetcode.com/problems/restore-the-array-from-adjacent-pairs/   |   Difficulty: Medium
//
// Problem Description:
// There is an integer array nums that consists of n unique elements, but you have forgotten it. However, you do remember every pair of adjacent elements in nums.
//
// You are given a 2D integer array adjacentPairs of size n - 1 where each adjacentPairs[i] = [ui, vi] indicates that the elements ui and vi are adjacent in nums.
//
// It is guaranteed that every adjacent pair of elements nums[i] and nums[i+1] will exist in adjacentPairs, either as [nums[i], nums[i+1]] or [nums[i+1], nums[i]]. The pairs can appear in any order.
//
// Return the original array nums. If there are multiple solutions, return any of them.
//
// Example:
// Input: adjacentPairs = [[2,1],[3,4],[3,2]]
// Output: [1,2,3,4]
// Explanation: This array has all its adjacent pairs in adjacentPairs.
// Notice that adjacentPairs[i] may not be in left-to-right order.
//
// Constraints:
// nums.length == n
// 	adjacentPairs.length == n - 1
// 	adjacentPairs[i].length == 2
// 	2 <= n <= 105
// 	-105 <= nums[i], ui, vi <= 105
// 	There exists some nums that has adjacentPairs as its pairs.
//

class Solution {
    public int[] restoreArray(int[][] adjacentPairs) {
        Map<Integer, List<Integer>> graph = new HashMap<>();

        // Build the graph from adjacent pairs
        for (int[] pair : adjacentPairs) {
            graph.putIfAbsent(pair[0], new ArrayList<>());
            graph.putIfAbsent(pair[1], new ArrayList<>());
            graph.get(pair[0]).add(pair[1]);
            graph.get(pair[1]).add(pair[0]);
        }

        // Find the starting point (an endpoint with only one neighbor)
        int start = 0;
        for (Map.Entry<Integer, List<Integer>> entry : graph.entrySet()) {
            if (entry.getValue().size() == 1) {
                start = entry.getKey();
                break;
            }
        }

        int n = adjacentPairs.length + 1;
        int[] result = new int[n];
        boolean[] visited = new boolean[n * 2 + 1]; // To handle negative values, offset by 10^5
        int index = 0;

        // DFS to reconstruct the array
        dfs(start, graph, visited, result, index);

        return result;          
    }
}
