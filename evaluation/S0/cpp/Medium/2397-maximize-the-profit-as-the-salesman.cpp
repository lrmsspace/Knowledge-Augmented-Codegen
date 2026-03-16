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
public:
    int maximizeTheProfit(int n, vector<vector<int>>& offers) {
        vector<vector<pair<int, int>>> offerMap(n);
        for (const auto& offer : offers) {
            offerMap[offer[1]].emplace_back(offer[0], offer[2]);
        }

        vector<int> dp(n, 0);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                dp[i] = dp[i - 1];
            }
            for (const auto& [start, gold] : offerMap[i]) {
                int totalGold = gold + (start > 0 ? dp[start - 1] : 0);
                dp[i] = max(dp[i], totalGold);
            }
        }

        return dp[n - 1];           
    }
};
