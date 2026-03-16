// Source: https://leetcode.com/problems/number-of-great-partitions/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums consisting of positive integers and an integer k.
//
// Partition the array into two ordered groups such that each element is in exactly one group. A partition is called great if the sum of elements of each group is greater than or equal to k.
//
// Return the number of distinct great partitions. Since the answer may be too large, return it modulo 109 + 7.
//
// Two partitions are considered distinct if some element nums[i] is in different groups in the two partitions.
//
// Example:
// Input: nums = [1,2,3,4], k = 4
// Output: 6
// Explanation: The great partitions are: ([1,2,3], [4]), ([1,3], [2,4]), ([1,4], [2,3]), ([2,3], [1,4]), ([2,4], [1,3]) and ([4], [1,2,3]).
//
// Constraints:
// 1 <= nums.length, k <= 1000
// 	1 <= nums[i] <= 109
//

class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        long long totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }
        
        if (totalSum < 2 * k) {
            return 0;
        }
        
        // DP to count subsets with sum < k
        vector<long long> dp(k, 0);
        dp[0] = 1;  // one way to make sum 0
        
        for (int num : nums) {
            for (int j = k - 1; j >= num; j--) {
                dp[j] = (dp[j] + dp[j - num]) % MOD;
            }
        }
        
        long long invalidPartitions = 0;
        for (int sum = 0; sum < k; sum++) {
            invalidPartitions = (invalidPartitions + dp[sum]) % MOD;
        }
        
        long long totalPartitions = 1;
        for (int i = 0; i < n; i++) {
            totalPartitions = (totalPartitions * 2) % MOD;
        }
        
        long long greatPartitions = (totalPartitions - 2 * invalidPartitions + MOD) % MOD;
        
        return (int)greatPartitions;            
    }
};
