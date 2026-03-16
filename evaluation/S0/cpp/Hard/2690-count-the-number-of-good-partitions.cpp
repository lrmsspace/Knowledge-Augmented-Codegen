// Source: https://leetcode.com/problems/count-the-number-of-good-partitions/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array nums consisting of positive integers.
//
// A partition of an array into one or more contiguous subarrays is called good if no two subarrays contain the same number.
//
// Return the total number of good partitions of nums.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 8
// Explanation: The 8 possible good partitions are: ([1], [2], [3], [4]), ([1], [2], [3,4]), ([1], [2,3], [4]), ([1], [2,3,4]), ([1,2], [3], [4]), ([1,2], [3,4]), ([1,2,3], [4]), and ([1,2,3,4]).
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

class Solution {
public:
    int numberOfGoodPartitions(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        vector<int> lastIndex(1e5 + 1, -1);
        vector<long long> dp(n + 1, 0);
        dp[0] = 1;  // base case: one way to partition empty array
        int left = 0;  // left pointer for the sliding window

        for (int right = 0; right < n; ++right) {
            int num = nums[right];
            if (lastIndex[num] != -1) {
                left = max(left, lastIndex[num] + 1);
            }
            dp[right + 1] = (dp[right] + dp[right] - dp[left] + MOD) % MOD;
            lastIndex[num] = right;
        }

        return (dp[n] - 1 + MOD) % MOD;  // subtract the empty partition            
    }
};
