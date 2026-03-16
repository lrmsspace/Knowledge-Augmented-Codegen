// Source: https://leetcode.com/problems/russian-doll-envelopes/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] represents the width and the height of an envelope.
//
// One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height.
//
// Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).
//
// Note: You cannot rotate an envelope.
//
// Example:
// Input: envelopes = [[5,4],[6,4],[6,7],[2,3]]
// Output: 3
// Explanation: The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).
//
// Constraints:
// 1 <= envelopes.length <= 105
// 	envelopes[i].length == 2
// 	1 <= wi, hi <= 105
//

class Solution {
    public int maxEnvelopes(int[][] envelopes) {
        Arrays.sort(envelopes, (a, b) -> {
            if (a[0] != b[0]) {
                return Integer.compare(a[0], b[0]);
            } else {
                return Integer.compare(b[1], a[1]);
            }
        });

        int n = envelopes.length;
        int[] dp = new int[n];
        int length = 0;

        for (int[] envelope : envelopes) {
            int height = envelope[1];
            int index = Arrays.binarySearch(dp, 0, length, height);
            if (index < 0) {
                index = -(index + 1);
            }
            dp[index] = height;
            if (index == length) {
                length++;
            }
        }

        return length;          
    }
}
