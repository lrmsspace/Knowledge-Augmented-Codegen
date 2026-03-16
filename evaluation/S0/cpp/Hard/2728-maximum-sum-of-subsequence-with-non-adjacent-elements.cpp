// Source: https://leetcode.com/problems/maximum-sum-of-subsequence-with-non-adjacent-elements/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums consisting of integers. You are also given a 2D array queries, where queries[i] = [posi, xi].
//
// For query i, we first set nums[posi] equal to xi, then we calculate the answer to query i which is the maximum sum of a subsequence of nums where no two adjacent elements are selected.
//
// Return the sum of the answers to all queries.
//
// Since the final answer may be very large, return it modulo 109 + 7.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [3,5,9], queries = [[1,-2],[0,-3]]
//
// Output: 21
//
// Explanation:
// After the 1st query, nums = [3,-2,9] and the maximum sum of a subsequence with non-adjacent elements is 3 + 9 = 12.
// After the 2nd query, nums = [-3,-2,9] and the maximum sum of a subsequence with non-adjacent elements is 9.
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	-105 <= nums[i] <= 105
// 	1 <= queries.length <= 5 * 104
// 	queries[i] == [posi, xi]
// 	0 <= posi <= nums.length - 1
// 	-105 <= xi <= 105
//

class Solution {
public:
    int maximumSumSubsequence(vector<int>& nums, vector<vector<int>>& queries) {
        const int MOD = 1e9 + 7;
        int n = nums.size();
        vector<long long> dp0(n + 1, 0); // max sum excluding current
        vector<long long> dp1(n + 1, 0); // max sum including current
        
        for (int i = 0; i < n; i++) {
            dp1[i + 1] = dp0[i] + max(0, nums[i]);
            dp0[i + 1] = max(dp0[i], dp1[i]);
        }
        
        long long totalSum = max(dp0[n], dp1[n]);
        long long result = 0;
        
        for (const auto& query : queries) {
            int pos = query[0];
            int x = query[1];
            
            long long oldVal = nums[pos];
            nums[pos] = x;
            
            // Recompute DP for the modified position
            dp0[0] = 0;
            dp1[0] = 0;
            for (int i = 0; i < n; i++) {
                dp1[i + 1] = dp0[i] + max(0, nums[i]);
                dp0[i + 1] = max(dp0[i], dp1[i]);
            }
            
            long long newSum = max(dp0[n], dp1[n]);
            result = (result + newSum) % MOD;
            
            nums[pos] = oldVal; // revert back
        }
        
        return result;          
    }
};
