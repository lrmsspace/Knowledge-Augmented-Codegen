// Source: https://leetcode.com/problems/constrained-subsequence-sum/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and an integer k, return the maximum sum of a non-empty subsequence of that array such that for every two consecutive integers in the subsequence, nums[i] and nums[j], where i < j, the condition j - i <= k is satisfied.
//
// A subsequence of an array is obtained by deleting some number of elements (can be zero) from the array, leaving the remaining elements in their original order.
//
// Example:
// Input: nums = [10,2,-10,5,20], k = 2
// Output: 37
// Explanation: The subsequence is [10, 2, 5, 20].
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	-104 <= nums[i] <= 104
//

class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> dp(n, 0);
        deque<int> dq;  // stores indices of dp elements
        
        int maxSum = nums[0];
        dp[0] = nums[0];
        dq.push_back(0);
        
        for (int i = 1; i < n; i++) {
            // Remove indices out of the window
            while (!dq.empty() && dq.front() < i - k) {
                dq.pop_front();
            }
            
            // Calculate dp[i]
            dp[i] = nums[i];
            if (!dq.empty() && dp[dq.front()] > 0) {
                dp[i] += dp[dq.front()];
            }
            
            // Update maxSum
            maxSum = max(maxSum, dp[i]);
            
            // Maintain deque in decreasing order of dp values
            while (!dq.empty() && dp[dq.back()] <= dp[i]) {
                dq.pop_back();
            }
            dq.push_back(i);
        }
        
        return maxSum;          
    }
};
