// Source: https://leetcode.com/problems/sum-of-good-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. A good subsequence is defined as a subsequence of nums where the absolute difference between any two consecutive elements in the subsequence is exactly 1.
//
// Return the sum of all possible good subsequences of nums.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Note that a subsequence of size 1 is considered good by definition.
//
// Example:
// Input: nums = [1,2,1]
//
// Output: 14
//
// Explanation:
//
//
// 	Good subsequences are: [1], [2], [1], [1,2], [2,1], [1,2,1].
// 	The sum of elements in these subsequences is 14.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 105
//

class Solution {
public:
    int sumOfGoodSubsequences(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        const int MAX_VAL = 100000;
        vector<long long> dp(MAX_VAL + 1, 0);
        long long result = 0;

        for (int num : nums) {
            long long count = 1; // subsequence of size 1

            if (num > 0) {
                count = (count + dp[num - 1]) % MOD;
            }
            if (num < MAX_VAL) {
                count = (count + dp[num + 1]) % MOD;
            }

            dp[num] = (dp[num] + count) % MOD;
            result = (result + count) % MOD;
        }

        return (int)result;         
    }
};
