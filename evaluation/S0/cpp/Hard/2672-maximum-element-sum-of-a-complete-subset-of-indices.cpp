// Source: https://leetcode.com/problems/maximum-element-sum-of-a-complete-subset-of-indices/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 1-indexed array nums. Your task is to select a complete subset from nums where every pair of selected indices multiplied is a perfect square,. i. e. if you select ai and aj, i * j must be a perfect square.
//
// Return the sum of the complete subset with the maximum sum.
//
// Example:
// Input: nums = [8,7,3,5,7,2,4,9]
//
// Output: 16
//
// Explanation:
//
// We select elements at indices 2 and 8 and 2 * 8 is a perfect square.
//
// Constraints:
// 1 <= n == nums.length <= 104
// 	1 <= nums[i] <= 109
//

class Solution {
public:
    long long maximumSum(vector<int>& nums) {
        int n = nums.size();
        vector<long long> dp(n + 1, 0);
        long long result = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j * j <= i; j++) {
                int idx = i / (j * j);
                dp[i] = max(dp[i], dp[idx] + nums[i - 1]);
            }
            result = max(result, dp[i]);
        }
        
        return result;          
    }
};
