// Source: https://leetcode.com/problems/unit-conversion-i/   |   Difficulty: Medium
//
// Problem Description:
// There are n types of units indexed from 0 to n - 1. You are given a 2D integer array conversions of length n - 1, where conversions[i] = [sourceUniti, targetUniti, conversionFactori]. This indicates that a single unit of type sourceUniti is equivalent to conversionFactori units of type targetUniti.
//
// Return an array baseUnitConversion of length n, where baseUnitConversion[i] is the number of units of type i equivalent to a single unit of type 0. Since the answer may be large, return each baseUnitConversion[i] modulo 109 + 7.
//
// Example:
// Input: conversions = [[0,1,2],[1,2,3]]
//
// Output: [1,2,6]
//
// Explanation:
//
//
// 	Convert a single unit of type 0 into 2 units of type 1 using conversions[0].
// 	Convert a single unit of type 0 into 6 units of type 2 using conversions[0], then conversions[1].
//
// Constraints:
// 2 <= n <= 105
// 	conversions.length == n - 1
// 	0 <= sourceUniti, targetUniti < n
// 	1 <= conversionFactori <= 109
// 	It is guaranteed that unit 0 can be converted into any other unit through a unique combination of conversions without using any conversions in the opposite direction.
//

class Solution {
    public int[] baseUnitConversions(int[][] conversions) {
        int MOD = 1_000_000_007;
        int n = conversions.length + 1;
        int[] result = new int[n];
        result[0] = 1;

        // Create an adjacency list to represent the conversion graph
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] conversion : conversions) {
            int src = conversion[0];
            int dest = conversion[1];
            int factor = conversion[2];
            graph.get(src).add(new int[]{dest, factor});
            graph.get(dest).add(new int[]{src, modInverse(factor, MOD)});
        }

        // BFS to calculate conversions from unit 0 to all other units
        boolean[] visited = new boolean[n];
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(0);
        visited[0] = true;

        while (!queue.isEmpty()) {
            int current = queue.poll();
            for (int[] neighbor : graph.get(current)) {
                int nextUnit = neighbor[0];
                int conversionFactor = neighbor[1];
                if (!visited[nextUnit]) {
                    result[nextUnit] = (int)((long)result[current] * conversionFactor % MOD);
                    visited[nextUnit] = true;
                    queue.offer(nextUnit);
                }
            }
        }

        return result;          
    }
}
