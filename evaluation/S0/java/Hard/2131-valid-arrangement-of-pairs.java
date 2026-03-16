// Source: https://leetcode.com/problems/valid-arrangement-of-pairs/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array pairs where pairs[i] = [starti, endi]. An arrangement of pairs is valid if for every index i where 1 <= i < pairs.length, we have endi-1 == starti.
//
// Return any valid arrangement of pairs.
//
// Note: The inputs will be generated such that there exists a valid arrangement of pairs.
//
// Example:
// Input: pairs = [[5,1],[4,5],[11,9],[9,4]]
// Output: [[11,9],[9,4],[4,5],[5,1]]
// Explanation:
// This is a valid arrangement since endi-1 always equals starti.
// end0 = 9 == 9 = start1 
// end1 = 4 == 4 = start2
// end2 = 5 == 5 = start3
//
// Constraints:
// 1 <= pairs.length <= 105
// 	pairs[i].length == 2
// 	0 <= starti, endi <= 109
// 	starti != endi
// 	No two pairs are exactly the same.
// 	There exists a valid arrangement of pairs.
//

class Solution {
    public int[][] validArrangement(int[][] pairs) {
        Map<Integer, Deque<Integer>> graph = new HashMap<>();
        Map<Integer, Integer> inDegree = new HashMap<>();
        Map<Integer, Integer> outDegree = new HashMap<>();

        for (int[] pair : pairs) {
            graph.computeIfAbsent(pair[0], k -> new ArrayDeque<>()).add(pair[1]);
            outDegree.put(pair[0], outDegree.getOrDefault(pair[0], 0) + 1);
            inDegree.put(pair[1], inDegree.getOrDefault(pair[1], 0) + 1);
        }

        int startNode = pairs[0][0];
        for (int node : graph.keySet()) {
            int outDeg = outDegree.getOrDefault(node, 0);
            int inDeg = inDegree.getOrDefault(node, 0);
            if (outDeg - inDeg == 1) {
                startNode = node;
                break;
            }
        }

        List<int[]> result = new ArrayList<>();
        dfs(graph, startNode, result);

        Collections.reverse(result);
        return result.toArray(new int[result.size()][]);            
    }
}
