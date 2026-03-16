// Source: https://leetcode.com/problems/longest-arithmetic-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of integers, return the length of the longest arithmetic subsequence in nums.
//
// Note that:
//
//
// 	A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
// 	A sequence seq is arithmetic if seq[i + 1] - seq[i] are all the same value (for 0 <= i < seq.length - 1).
//
// Example:
// Input: nums = [3,6,9,12]
// Output: 4
// Explanation:  The whole array is an arithmetic sequence with steps of length = 3.
//
// Constraints:
// 2 <= nums.length <= 1000
// 	0 <= nums[i] <= 500
//

class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) return n;

        // dp[i][d] will store the length of the longest arithmetic subsequence ending with nums[i] with common difference d
        vector<unordered_map<int, int>> dp(n);
        int maxLength = 2; // Minimum length of arithmetic subsequence is 2

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                int diff = nums[i] - nums[j];
                // If there's already a subsequence ending at j with this difference, extend it
                if (dp[j].find(diff) != dp[j].end()) {
                    dp[i][diff] = dp[j][diff] + 1;
                } else {
                    // Otherwise, start a new subsequence of length 2
                    dp[i][diff] = 2;
                }
                maxLength = max(maxLength, dp[i][diff]);
            }
        }

        return maxLength;           
    }
};
