// Source: https://leetcode.com/problems/max-consecutive-ones-iii/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the array if you can flip at most k 0's.
//
// Example:
// Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
// Output: 6
// Explanation: [1,1,1,0,0,1,1,1,1,1,1]
// Bolded numbers were flipped from 0 to 1. The longest subarray is underlined.
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is either 0 or 1.
// 	0 <= k <= nums.length
//

int longestOnes(int* nums, int numsSize, int k) {
    int left = 0, right;
    int zeroCount = 0;
    int maxLength = 0;

    for (right = 0; right < numsSize; right++) {
        if (nums[right] == 0) {
            zeroCount++;
        }

        while (zeroCount > k) {
            if (nums[left] == 0) {
                zeroCount--;
            }
            left++;
        }

        maxLength = (right - left + 1) > maxLength ? (right - left + 1) : maxLength;
    }

    return maxLength;       
}
