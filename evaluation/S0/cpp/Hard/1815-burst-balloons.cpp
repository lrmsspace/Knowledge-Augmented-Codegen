// Source: https://leetcode.com/problems/burst-balloons/   |   Difficulty: Hard
//
// Problem Description:
// You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an array nums. You are asked to burst all the balloons.
//
// If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.
//
// Return the maximum coins you can collect by bursting the balloons wisely.
//
// Example:
// Input: nums = [3,1,5,8]
// Output: 167
// Explanation:
// nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
// coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
//
// Constraints:
// n == nums.length
// 	1 <= n <= 300
// 	0 <= nums[i] <= 100
//

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int> balloons(n + 2, 1);
        for (int i = 0; i < n; i++) {
            balloons[i + 1] = nums[i];
        }
        
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
        
        for (int length = 1; length <= n; length++) {
            for (int left = 1; left <= n - length + 1; left++) {
                int right = left + length - 1;
                for (int k = left; k <= right; k++) {
                    int coins = balloons[left - 1] * balloons[k] * balloons[right + 1];
                    coins += dp[left][k - 1] + dp[k + 1][right];
                    dp[left][right] = max(dp[left][right], coins);
                }
            }
        }
        
        return dp[1][n];            
    }
};
