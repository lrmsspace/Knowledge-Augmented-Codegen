// Source: https://leetcode.com/problems/find-the-maximum-length-of-valid-subsequence-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and a positive integer k.
// A subsequence sub of nums with length x is called valid if it satisfies:
//
//
// 	(sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k.
//
// Return the length of the longest valid subsequence of nums.
//
// Example:
// Input: nums = [1,2,3,4,5], k = 2
//
// Output: 5
//
// Explanation:
//
// The longest valid subsequence is [1, 2, 3, 4, 5].
//
// Constraints:
// 2 <= nums.length <= 103
// 	1 <= nums[i] <= 107
// 	1 <= k <= 103
//

class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(k, 1));
        int maxLength = 1;

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if ((nums[i] + nums[j]) % k == 0) {
                    for (int r = 0; r < k; ++r) {
                        if ((r + nums[j]) % k == 0) {
                            dp[i][(r + nums[i]) % k] = max(dp[i][(r + nums[i]) % k], dp[j][r] + 1);
                            maxLength = max(maxLength, dp[i][(r + nums[i]) % k]);
                        }
                    }
                }
            }
        }

        return maxLength;           
    }
};
