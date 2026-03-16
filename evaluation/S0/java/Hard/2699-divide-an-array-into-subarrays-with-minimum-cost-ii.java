// Source: https://leetcode.com/problems/divide-an-array-into-subarrays-with-minimum-cost-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array of integers nums of length n, and two positive integers k and dist.
//
// The cost of an array is the value of its first element. For example, the cost of [1,2,3] is 1 while the cost of [3,4,1] is 3.
//
// You need to divide nums into k disjoint contiguous subarrays, such that the difference between the starting index of the second subarray and the starting index of the kth subarray should be less than or equal to dist. In other words, if you divide nums into the subarrays nums[0..(i1 - 1)], nums[i1..(i2 - 1)], ..., nums[ik-1..(n - 1)], then ik-1 - i1 <= dist.
//
// Return the minimum possible sum of the cost of these subarrays.
//
// Example:
// Input: nums = [1,3,2,6,4,2], k = 3, dist = 3
// Output: 5
// Explanation: The best possible way to divide nums into 3 subarrays is: [1,3], [2,6,4], and [2]. This choice is valid because ik-1 - i1 is 5 - 2 = 3 which is equal to dist. The total cost is nums[0] + nums[2] + nums[5] which is 1 + 2 + 2 = 5.
// It can be shown that there is no possible way to divide nums into 3 subarrays at a cost lower than 5.
//
// Constraints:
// 3 <= n <= 105
//  1 <= nums[i] <= 109
//  3 <= k <= n
//  k - 2 <= dist <= n - 2
//

class Solution {
    public long minimumCost(int[] nums, int k, int dist) {
        int n = nums.length;
        long[] dp = new long[n];
        long[] prefixMin = new long[n];
        Arrays.fill(dp, Long.MAX_VALUE);
        Arrays.fill(prefixMin, Long.MAX_VALUE);

        for (int i = 0; i < n; i++) {
            if (i + 1 < k) {
                dp[i] = Long.MAX_VALUE;
            } else if (i + 1 == k) {
                dp[i] = nums[0];
            } else {
                int left = Math.max(0, i - dist);
                int right = i - 1;
                long minPrevCost = prefixMin[right];
                if (left > 0) {
                    minPrevCost = Math.min(minPrevCost, prefixMin[right] - prefixMin[left - 1]);
                }
                if (minPrevCost != Long.MAX_VALUE) {
                    dp[i] = minPrevCost + nums[i - dist >= 0 ? i - dist : 0];
                }
            }
            prefixMin[i] = dp[i] + (i > 0 ? prefixMin[i - 1] : 0);
        }

        return dp[n - 1];           
    }
}
