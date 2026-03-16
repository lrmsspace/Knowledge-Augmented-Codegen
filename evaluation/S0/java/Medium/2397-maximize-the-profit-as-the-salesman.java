// Source: https://leetcode.com/problems/maximize-the-profit-as-the-salesman/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n representing the number of houses on a number line, numbered from 0 to n - 1.
//
// Additionally, you are given a 2D integer array offers where offers[i] = [starti, endi, goldi], indicating that ith buyer wants to buy all the houses from starti to endi for goldi amount of gold.
//
// As a salesman, your goal is to maximize your earnings by strategically selecting and selling houses to buyers.
//
// Return the maximum amount of gold you can earn.
//
// Note that different buyers can't buy the same house, and some houses may remain unsold.
//
// Example:
// Input: n = 5, offers = [[0,0,1],[0,2,2],[1,3,2]]
// Output: 3
// Explanation: There are 5 houses numbered from 0 to 4 and there are 3 purchase offers.
// We sell houses in the range [0,0] to 1st buyer for 1 gold and houses in the range [1,3] to 3rd buyer for 2 golds.
// It can be proven that 3 is the maximum amount of gold we can achieve.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= offers.length <= 105
// 	offers[i].length == 3
// 	0 <= starti <= endi <= n - 1
// 	1 <= goldi <= 103
//

class Solution {
    public int maximizeTheProfit(int n, List<List<Integer>> offers) {
        // Sort offers based on their end index
        offers.sort(Comparator.comparingInt(a -> a.get(1)));

        // dp[i] will store the maximum profit we can get by considering offers up to the i-th offer
        int m = offers.size();
        int[] dp = new int[m + 1];

        // Array to store the end indices for binary search
        int[] endIndices = new int[m];
        for (int i = 0; i < m; i++) {
            endIndices[i] = offers.get(i).get(1);
        }

        for (int i = 1; i <= m; i++) {
            List<Integer> offer = offers.get(i - 1);
            int start = offer.get(0);
            int end = offer.get(1);
            int gold = offer.get(2);

            // Find the last offer that ends before the current offer starts
            int idx = binarySearch(endIndices, start - 1);

            // Calculate profit including the current offer
            int includeProfit = gold + dp[idx + 1];

            // Calculate profit excluding the current offer
            int excludeProfit = dp[i - 1];

            // Take the maximum of including or excluding the current offer
            dp[i] = Math.max(includeProfit, excludeProfit);
        }

        return dp[m];           
    }
}
