// Source: https://leetcode.com/problems/find-the-number-of-distinct-colors-among-the-balls/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer limit and a 2D array queries of size n x 2.
//
// There are limit + 1 balls with distinct labels in the range [0, limit]. Initially, all balls are uncolored. For every query in queries that is of the form [x, y], you mark ball x with the color y. After each query, you need to find the number of colors among the balls.
//
// Return an array result of length n, where result[i] denotes the number of colors after ith query.
//
// Note that when answering a query, lack of a color will not be considered as a color.
//
// Example:
// Input: limit = 4, queries = [[1,4],[2,5],[1,3],[3,4]]
//
// Output: [1,2,2,3]
//
// Explanation:
//
//
//
//
// 	After query 0, ball 1 has color 4.
// 	After query 1, ball 1 has color 4, and ball 2 has color 5.
// 	After query 2, ball 1 has color 3, and ball 2 has color 5.
// 	After query 3, ball 1 has color 3, ball 2 has color 5, and ball 3 has color 4.
//
// Constraints:
// 1 <= limit <= 109
// 	1 <= n == queries.length <= 105
// 	queries[i].length == 2
// 	0 <= queries[i][0] <= limit
// 	1 <= queries[i][1] <= 109
//

class Solution {
    public int[] queryResults(int limit, int[][] queries) {
        Map<Integer, Integer> ballColorMap = new HashMap<>();
        Map<Integer, Integer> colorCountMap = new HashMap<>();
        int distinctColorCount = 0;
        int[] result = new int[queries.length];

        for (int i = 0; i < queries.length; i++) {
            int ball = queries[i][0];
            int newColor = queries[i][1];

            if (ballColorMap.containsKey(ball)) {
                int oldColor = ballColorMap.get(ball);
                colorCountMap.put(oldColor, colorCountMap.get(oldColor) - 1);
                if (colorCountMap.get(oldColor) == 0) {
                    distinctColorCount--;
                }
            }

            ballColorMap.put(ball, newColor);
            colorCountMap.put(newColor, colorCountMap.getOrDefault(newColor, 0) + 1);
            if (colorCountMap.get(newColor) == 1) {
                distinctColorCount++;
            }

            result[i] = distinctColorCount;
        }

        return result;          
    }
}
