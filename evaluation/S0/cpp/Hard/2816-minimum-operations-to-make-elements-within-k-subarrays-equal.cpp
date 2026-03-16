// Source: https://leetcode.com/problems/minimum-operations-to-make-elements-within-k-subarrays-equal/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers, x and k. You can perform the following operation any number of times (including zero):
//
//
// 	Increase or decrease any element of nums by 1.
//
//
// Return the minimum number of operations needed to have at least k non-overlapping subarrays of size exactly x in nums, where all elements within each subarray are equal.
//
// Example:
// Input: nums = [5,-2,1,3,7,3,6,4,-1], x = 3, k = 2
//
// Output: 8
//
// Explanation:
//
//
// 	Use 3 operations to add 3 to nums[1] and use 2 operations to subtract 2 from nums[3]. The resulting array is [5, 1, 1, 1, 7, 3, 6, 4, -1].
// 	Use 1 operation to add 1 to nums[5] and use 2 operations to subtract 2 from nums[6]. The resulting array is [5, 1, 1, 1, 7, 4, 4, 4, -1].
// 	Now, all elements within each subarray [1, 1, 1] (from indices 1 to 3) and [4, 4, 4] (from indices 5 to 7) are equal. Since 8 total operations were used, 8 is the output.
//
// Constraints:
// 2 <= nums.length <= 105
// 	-106 <= nums[i] <= 106
// 	2 <= x <= nums.length
// 	1 <= k <= 15
// 	2 <= k * x <= nums.length
//

class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();
        const long long INF = 1e15;
        vector<long long> dp(n + 1, -INF);
        dp[0] = 0;
        
        for (int i = 0; i <= n - x; i++) {
            // Calculate cost to make nums[i..i+x-1] equal
            vector<int> sub(nums.begin() + i, nums.begin() + i + x);
            sort(sub.begin(), sub.end());
            long long median = sub[x / 2];
            long long cost = 0;
            for (int val : sub) {
                cost += abs(val - median);
            }
            
            // Update dp
            for (int j = n / x; j >= 1; j--) {
                if (dp[j - 1] != -INF) {
                    dp[j] = max(dp[j], dp[j - 1] + cost);
                }
            }
        }
        
        long long totalCost = 0;
        for (int val : nums) {
            totalCost += abs(val);
        }
        
        return totalCost - dp[k];           
    }
};
