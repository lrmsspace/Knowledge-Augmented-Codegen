// Source: https://leetcode.com/problems/maximize-total-cost-of-alternating-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums with length n.
//
// The cost of a subarray nums[l..r], where 0 <= l <= r < n, is defined as:
//
// cost(l, r) = nums[l] - nums[l + 1] + ... + nums[r] * (−1)r − l
//
// Your task is to split nums into subarrays such that the total cost of the subarrays is maximized, ensuring each element belongs to exactly one subarray.
//
// Formally, if nums is split into k subarrays, where k > 1, at indices i1, i2, ..., ik − 1, where 0 <= i1 < i2 < ... < ik - 1 < n - 1, then the total cost will be:
//
// cost(0, i1) + cost(i1 + 1, i2) + ... + cost(ik − 1 + 1, n − 1)
//
// Return an integer denoting the maximum total cost of the subarrays after splitting the array optimally.
//
// Note: If nums is not split into subarrays, i.e. k = 1, the total cost is simply cost(0, n - 1).
//
// Example:
// Input: nums = [1,-2,3,4]
//
// Output: 10
//
// Explanation:
//
// One way to maximize the total cost is by splitting [1, -2, 3, 4] into subarrays [1, -2, 3] and [4]. The total cost will be (1 + 2 + 3) + 4 = 10.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
//

class Solution {
public:
    long long maximumTotalCost(vector<int>& nums) {
        long long n = nums.size();
        vector<long long> dp(n + 1, LLONG_MIN);
        dp[0] = 0;

        for (long long i = 1; i <= n; ++i) {
            long long currSum = 0;
            for (long long j = i; j >= 1; --j) {
                currSum += (i - j) % 2 == 0 ? nums[j - 1] : -nums[j - 1];
                dp[i] = max(dp[i], dp[j - 1] + currSum);
            }
        }

        return dp[n];           
    }
};
