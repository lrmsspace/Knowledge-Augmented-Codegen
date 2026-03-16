// Source: https://leetcode.com/problems/split-array-largest-sum/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and an integer k, split nums into k non-empty subarrays such that the largest sum of any subarray is minimized.
//
// Return the minimized largest sum of the split.
//
// A subarray is a contiguous part of the array.
//
// Example:
// Input: nums = [7,2,5,10,8], k = 2
// Output: 18
// Explanation: There are four ways to split nums into two subarrays.
// The best way is to split it into [7,2,5] and [10,8], where the largest sum among the two subarrays is only 18.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	0 <= nums[i] <= 106
// 	1 <= k <= min(50, nums.length)
//

int splitArray(int* nums, int numsSize, int k) {
    int left = 0, right = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > left) left = nums[i];
        right += nums[i];
    }

    while (left < right) {
        int mid = left + (right - left) / 2;
        int currentSum = 0;
        int requiredSplits = 1;

        for (int i = 0; i < numsSize; ++i) {
            if (currentSum + nums[i] > mid) {
                requiredSplits++;
                currentSum = nums[i];
            } else {
                currentSum += nums[i];
            }
        }

        if (requiredSplits > k) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;        
}
