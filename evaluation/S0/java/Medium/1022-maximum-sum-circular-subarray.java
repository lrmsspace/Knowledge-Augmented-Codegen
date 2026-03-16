// Source: https://leetcode.com/problems/maximum-sum-circular-subarray/   |   Difficulty: Medium
//
// Problem Description:
// Given a circular integer array nums of length n, return the maximum possible sum of a non-empty subarray of nums.
//
// A circular array means the end of the array connects to the beginning of the array. Formally, the next element of nums[i] is nums[(i + 1) % n] and the previous element of nums[i] is nums[(i - 1 + n) % n].
//
// A subarray may only include each element of the fixed buffer nums at most once. Formally, for a subarray nums[i], nums[i + 1], ..., nums[j], there does not exist i <= k1, k2 <= j with k1 % n == k2 % n.
//
// Example:
// Input: nums = [1,-2,3,-2]
// Output: 3
// Explanation: Subarray [3] has maximum sum 3.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 3 * 104
// 	-3 * 104 <= nums[i] <= 3 * 104
//

class Solution {
    public int maxSubarraySumCircular(int[] nums) {
        int total = 0;
        int maxSum = nums[0];
        int curMax = 0;
        int minSum = nums[0];
        int curMin = 0;

        for (int num : nums) {
            curMax = Math.max(curMax + num, num);
            maxSum = Math.max(maxSum, curMax);

            curMin = Math.min(curMin + num, num);
            minSum = Math.min(minSum, curMin);

            total += num;
        }

        return maxSum > 0 ? Math.max(maxSum, total - minSum) : maxSum;          
    }
}
