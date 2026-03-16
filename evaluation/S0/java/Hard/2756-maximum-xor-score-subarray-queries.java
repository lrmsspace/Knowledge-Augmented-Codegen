// Source: https://leetcode.com/problems/maximum-xor-score-subarray-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums of n integers, and a 2D integer array queries of size q, where queries[i] = [li, ri].
//
// For each query, you must find the maximum XOR score of any subarray of nums[li..ri].
//
// The XOR score of an array a is found by repeatedly applying the following operations on a so that only one element remains, that is the score:
//
//
// 	Simultaneously replace a[i] with a[i] XOR a[i + 1] for all indices i except the last one.
// 	Remove the last element of a.
//
//
// Return an array answer of size q where answer[i] is the answer to query i.
//
// Example:
// Input: nums = [2,8,4,32,16,1], queries = [[0,2],[1,4],[0,5]]
//
// Output: [12,60,60]
//
// Explanation:
//
// In the first query, nums[0..2] has 6 subarrays [2], [8], [4], [2, 8], [8, 4], and [2, 8, 4] each with a respective XOR score of 2, 8, 4, 10, 12, and 6. The answer for the query is 12, the largest of all XOR scores.
//
// In the second query, the subarray of nums[1..4] with the largest XOR score is nums[1..4] with a score of 60.
//
// In the third query, the subarray of nums[0..5] with the largest XOR score is nums[1..4] with a score of 60.
//
// Constraints:
// 1 <= n == nums.length <= 2000
// 	0 <= nums[i] <= 231 - 1
// 	1 <= q == queries.length <= 105
// 	queries[i].length == 2 
// 	queries[i] = [li, ri]
// 	0 <= li <= ri <= n - 1
//

class Solution {
    public int[] maximumSubarrayXor(int[] nums, int[][] queries) {
        int n = nums.length;
        int[][] dp = new int[n][n];
        for (int i = 0; i < n; i++) {
            dp[i][i] = nums[i];
        }
        for (int length = 2; length <= n; length++) {
            for (int i = 0; i <= n - length; i++) {
                int j = i + length - 1;
                dp[i][j] = dp[i][j - 1] ^ dp[i + 1][j];
            }
        }

        int[][] maxXor = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (i == j) {
                    maxXor[i][j] = dp[i][j];
                } else {
                    maxXor[i][j] = Math.max(maxXor[i][j - 1], Math.max(maxXor[i + 1][j], dp[i][j]));
                }
            }
        }

        int q = queries.length;
        int[] result = new int[q];
        for (int i = 0; i < q; i++) {
            int l = queries[i][0];
            int r = queries[i][1];
            result[i] = maxXor[l][r];
        }

        return result;          
    }
}
