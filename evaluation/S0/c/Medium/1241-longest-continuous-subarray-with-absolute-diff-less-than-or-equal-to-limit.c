// Source: https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums and an integer limit, return the size of the longest non-empty subarray such that the absolute difference between any two elements of this subarray is less than or equal to limit.
//
// Example:
// Input: nums = [8,2,4,7], limit = 4
// Output: 2 
// Explanation: All subarrays are: 
// [8] with maximum absolute diff |8-8| = 0 <= 4.
// [8,2] with maximum absolute diff |8-2| = 6 > 4. 
// [8,2,4] with maximum absolute diff |8-2| = 6 > 4.
// [8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
// [2] with maximum absolute diff |2-2| = 0 <= 4.
// [2,4] with maximum absolute diff |2-4| = 2 <= 4.
// [2,4,7] with maximum absolute diff |2-7| = 5 > 4.
// [4] with maximum absolute diff |4-4| = 0 <= 4.
// [4,7] with maximum absolute diff |4-7| = 3 <= 4.
// [7] with maximum absolute diff |7-7| = 0 <= 4. 
// Therefore, the size of the longest subarray is 2.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	0 <= limit <= 109
//

int longestSubarray(int* nums, int numsSize, int limit) {
    int maxDeque[numsSize];
    int minDeque[numsSize];
    int maxFront = 0, maxBack = -1;
    int minFront = 0, minBack = -1;
    int left = 0, right;
    int maxLength = 0;

    for (right = 0; right < numsSize; right++) {
        while (maxBack >= maxFront && nums[maxDeque[maxBack]] <= nums[right]) {
            maxBack--;
        }
        maxDeque[++maxBack] = right;

        while (minBack >= minFront && nums[minDeque[minBack]] >= nums[right]) {
            minBack--;
        }
        minDeque[++minBack] = right;

        while (nums[maxDeque[maxFront]] - nums[minDeque[minFront]] > limit) {
            if (maxDeque[maxFront] == left) {
                maxFront++;
            }
            if (minDeque[minFront] == left) {
                minFront++;
            }
            left++;
        }

        if (right - left + 1 > maxLength) {
            maxLength = right - left + 1;
        }
    }

    return maxLength;       
}
