// Source: https://leetcode.com/problems/minimum-operations-to-make-median-of-array-equal-to-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and a non-negative integer k. In one operation, you can increase or decrease any element by 1.
//
// Return the minimum number of operations needed to make the median of nums equal to k.
//
// The median of an array is defined as the middle element of the array when it is sorted in non-decreasing order. If there are two choices for a median, the larger of the two values is taken.
//
// Example:
// Input: nums = [2,5,6,8,5], k = 4
//
// Output: 2
//
// Explanation:
//
// We can subtract one from nums[1] and nums[4] to obtain [2, 4, 6, 8, 4]. The median of the resulting array is equal to k.
//
// Constraints:
// 1 <= nums.length <= 2 * 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 109
//

class Solution {
    public long minOperationsToMakeMedianK(int[] nums, int k) {
        Arrays.sort(nums);
        int n = nums.length;
        int medianIndex = n / 2;
        long operations = 0;

        for (int i = 0; i < n; i++) {
            if (i < medianIndex && nums[i] > k) {
                operations += nums[i] - k;
            } else if (i > medianIndex && nums[i] < k) {
                operations += k - nums[i];
            }
        }

        // Handle the median element
        if (nums[medianIndex] < k) {
            operations += k - nums[medianIndex];
        } else if (nums[medianIndex] > k) {
            operations += nums[medianIndex] - k;
        }

        return operations;          
    }
}
