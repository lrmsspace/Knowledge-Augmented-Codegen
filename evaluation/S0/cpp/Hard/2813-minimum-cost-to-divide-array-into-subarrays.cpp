// Source: https://leetcode.com/problems/minimum-cost-to-divide-array-into-subarrays/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integer arrays, nums and cost, of the same size, and an integer k.
//
// You can divide nums into subarrays. The cost of the ith subarray consisting of elements nums[l..r] is:
//
//
// 	(nums[0] + nums[1] + ... + nums[r] + k * i) * (cost[l] + cost[l + 1] + ... + cost[r]).
//
//
// Note that i represents the order of the subarray: 1 for the first subarray, 2 for the second, and so on.
//
// Return the minimum total cost possible from any valid division.
//
// Example:
// Input: nums = [3,1,4], cost = [4,6,6], k = 1
//
// Output: 110
//
// Explanation:
// The minimum total cost possible can be achieved by dividing nums into subarrays [3, 1] and [4].
//
//
// 	The cost of the first subarray [3,1] is (3 + 1 + 1 * 1) * (4 + 6) = 50.
// 	The cost of the second subarray [4] is (3 + 1 + 4 + 1 * 2) * 6 = 60.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	cost.length == nums.length
// 	1 <= nums[i], cost[i] <= 1000
// 	1 <= k <= 1000
//

class Solution {
public:
    long long minimumCost(vector<int>& nums, vector<int>& cost, int k) {
        int n = nums.size();
        vector<long long> prefixSumNums(n + 1, 0);
        vector<long long> prefixSumCost(n + 1, 0);
        
        for (int i = 0; i < n; i++) {
            prefixSumNums[i + 1] = prefixSumNums[i] + nums[i];
            prefixSumCost[i + 1] = prefixSumCost[i] + cost[i];
        }
        
        vector<long long> dp(n + 1, LLONG_MAX);
        dp[0] = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                long long subarrayCost = (prefixSumNums[i] - prefixSumNums[j] + k * (j + 1)) * (prefixSumCost[i] - prefixSumCost[j]);
                dp[i] = min(dp[i], dp[j] + subarrayCost);
            }
        }
        
        return dp[n];           
    }
};
