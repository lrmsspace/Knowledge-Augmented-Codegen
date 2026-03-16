// Source: https://leetcode.com/problems/maximum-total-damage-with-spell-casting/   |   Difficulty: Medium
//
// Problem Description:
// A magician has various spells.
//
// You are given an array power, where each element represents the damage of a spell. Multiple spells can have the same damage value.
//
// It is a known fact that if a magician decides to cast a spell with a damage of power[i], they cannot cast any spell with a damage of power[i] - 2, power[i] - 1, power[i] + 1, or power[i] + 2.
//
// Each spell can be cast only once.
//
// Return the maximum possible total damage that a magician can cast.
//
// Example:
// Input: power = [1,1,3,4]
//
// Output: 6
//
// Explanation:
//
// The maximum possible damage of 6 is produced by casting spells 0, 1, 3 with damage 1, 1, 4.
//
// Constraints:
// 1 <= power.length <= 105
// 	1 <= power[i] <= 109
//

class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        sort(power.begin(), power.end());
        int n = power.size();
        vector<long long> dp(n + 1, 0);
        dp[1] = power[0];

        for (int i = 2; i <= n; ++i) {
            if (power[i - 1] - power[i - 2] <= 2) {
                dp[i] = max(dp[i - 1], dp[i - 2] + power[i - 1]);
            } else {
                dp[i] = dp[i - 1] + power[i - 1];
            }
        }

        return dp[n];           
    }
};
