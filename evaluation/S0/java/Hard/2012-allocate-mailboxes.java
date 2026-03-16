// Source: https://leetcode.com/problems/allocate-mailboxes/   |   Difficulty: Hard
//
// Problem Description:
// Given the array houses where houses[i] is the location of the ith house along a street and an integer k, allocate k mailboxes in the street.
//
// Return the minimum total distance between each house and its nearest mailbox.
//
// The test cases are generated so that the answer fits in a 32-bit integer.
//
// Example:
// Input: houses = [1,4,8,10,20], k = 3
// Output: 5
// Explanation: Allocate mailboxes in position 3, 9 and 20.
// Minimum total distance from each houses to nearest mailboxes is |3-1| + |4-3| + |9-8| + |10-9| + |20-20| = 5
//
// Constraints:
// 1 <= k <= houses.length <= 100
// 	1 <= houses[i] <= 104
// 	All the integers of houses are unique.
//

class Solution {
    public int minDistance(int[] houses, int k) {
        int n = houses.length;
        Arrays.sort(houses);
        
        // Precompute the cost of placing one mailbox for every subarray of houses
        int[][] cost = new int[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int mid = (i + j) / 2;
                for (int m = i; m <= j; m++) {
                    cost[i][j] += Math.abs(houses[m] - houses[mid]);
                }
            }
        }
        
        // DP array to store the minimum distance
        int[][] dp = new int[n + 1][k + 1];
        for (int i = 0; i <= n; i++) {
            Arrays.fill(dp[i], Integer.MAX_VALUE / 2);
        }
        dp[0][0] = 0;
        
        // Fill the DP table
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= k; j++) {
                for (int p = 0; p < i; p++) {
                    dp[i][j] = Math.min(dp[i][j], dp[p][j - 1] + cost[p][i - 1]);
                }
            }
        }
        
        return dp[n][k];                    
    }
}
