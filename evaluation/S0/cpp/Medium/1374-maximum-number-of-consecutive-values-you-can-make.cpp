// Source: https://leetcode.com/problems/maximum-number-of-consecutive-values-you-can-make/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array coins of length n which represents the n coins that you own. The value of the ith coin is coins[i]. You can make some value x if you can choose some of your n coins such that their values sum up to x.
//
// Return the maximum number of consecutive integer values that you can make with your coins starting from and including 0.
//
// Note that you may have multiple coins of the same value.
//
// Example:
// Input: coins = [1,3]
// Output: 2
// Explanation: You can make the following values:
// - 0: take []
// - 1: take [1]
// You can make 2 consecutive integer values starting from 0.
//
// Constraints:
// coins.length == n
// 	1 <= n <= 4 * 104
// 	1 <= coins[i] <= 4 * 104
//

class Solution {
public:
    int getMaximumConsecutive(vector<int>& coins) {
        sort(coins.begin(), coins.end());
        int maxConstructible = 0;
        for (const int& coin : coins) {
            if (coin > maxConstructible + 1) {
                break;
            }
            maxConstructible += coin;
        }
        return maxConstructible + 1;            
    }
};
