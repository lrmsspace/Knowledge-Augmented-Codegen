// Source: https://leetcode.com/problems/coin-change/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
//
// Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
//
// You may assume that you have an infinite number of each kind of coin.
//
// Example:
// Input: coins = [1,2,5], amount = 11
// Output: 3
// Explanation: 11 = 5 + 5 + 1
//
// Constraints:
// 1 <= coins.length <= 12
// 	1 <= coins[i] <= 231 - 1
// 	0 <= amount <= 104
//

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;

        for (int coin : coins) {
            for (int x = coin; x <= amount; ++x) {
                dp[x] = min(dp[x], dp[x - coin] + 1);
            }
        }

        return dp[amount] > amount ? -1 : dp[amount];           
    }
};
