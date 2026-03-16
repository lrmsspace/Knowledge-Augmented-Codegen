// Source: https://leetcode.com/problems/plates-between-candles/   |   Difficulty: Medium
//
// Problem Description:
// There is a long table with a line of plates and candles arranged on top of it. You are given a 0-indexed string s consisting of characters '*' and '|' only, where a '*' represents a plate and a '|' represents a candle.
//
// You are also given a 0-indexed 2D integer array queries where queries[i] = [lefti, righti] denotes the substring s[lefti...righti] (inclusive). For each query, you need to find the number of plates between candles that are in the substring. A plate is considered between candles if there is at least one candle to its left and at least one candle to its right in the substring.
//
//
// 	For example, s = "||**||**|*", and a query [3, 8] denotes the substring "*||**|". The number of plates between candles in this substring is 2, as each of the two plates has at least one candle in the substring to its left and right.
//
//
// Return an integer array answer where answer[i] is the answer to the ith query.
//
// Example:
// Input: s = "**|**|***|", queries = [[2,5],[5,9]]
// Output: [2,3]
// Explanation:
// - queries[0] has two plates between candles.
// - queries[1] has three plates between candles.
//
// Constraints:
// 3 <= s.length <= 105
// 	s consists of '*' and '|' characters.
// 	1 <= queries.length <= 105
// 	queries[i].length == 2
// 	0 <= lefti <= righti < s.length
//

class Solution {
    public int[] platesBetweenCandles(String s, int[][] queries) {
        int n = s.length();
        int[] prefixPlates = new int[n];
        int[] leftCandle = new int[n];
        int[] rightCandle = new int[n];

        // Precompute prefix sum of plates and nearest candles
        int plateCount = 0;
        int lastCandle = -1;
        for (int i = 0; i < n; i++) {
            if (s.charAt(i) == '|') {
                lastCandle = i;
            } else {
                plateCount++;
            }
            prefixPlates[i] = plateCount;
            leftCandle[i] = lastCandle;
        }

        lastCandle = -1;
        for (int i = n - 1; i >= 0; i--) {
            if (s.charAt(i) == '|') {
                lastCandle = i;
            }
            rightCandle[i] = lastCandle;
        }

        // Process each query
        int qLen = queries.length;
        int[] result = new int[qLen];
        for (int i = 0; i < qLen; i++) {
            int left = queries[i][0];
            int right = queries[i][1];

            int rightBound = leftCandle[right];
            int leftBound = rightCandle[left];

            if (leftBound != -1 && rightBound != -1 && leftBound < rightBound) {
                result[i] = prefixPlates[rightBound] - prefixPlates[leftBound];
            } else {
                result[i] = 0;
            }
        }

        return result;          
    }
}
