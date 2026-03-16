// Source: https://leetcode.com/problems/continuous-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums. A subarray of nums is called continuous if:
//
//
// 	Let i, i + 1, ..., j be the indices in the subarray. Then, for each pair of indices i <= i1, i2 <= j, 0 <= |nums[i1] - nums[i2]| <= 2.
//
//
// Return the total number of continuous subarrays.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [5,4,2,4]
// Output: 8
// Explanation: 
// Continuous subarray of size 1: [5], [4], [2], [4].
// Continuous subarray of size 2: [5,4], [4,2], [2,4].
// Continuous subarray of size 3: [4,2,4].
// There are no subarrys of size 4.
// Total continuous subarrays = 4 + 3 + 1 = 8.
// It can be shown that there are no more continuous subarrays.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

long long continuousSubarrays(int* nums, int numsSize){
    long long result = 0;
    int left = 0, right = 0;
    int minDeque[numsSize], maxDeque[numsSize];
    int minFront = 0, minBack = -1, maxFront = 0, maxBack = -1;

    while (right < numsSize) {
        while (minBack >= minFront && nums[minDeque[minBack]] >= nums[right]) {
            minBack--;
        }
        minDeque[++minBack] = right;

        while (maxBack >= maxFront && nums[maxDeque[maxBack]] <= nums[right]) {
            maxBack--;
        }
        maxDeque[++maxBack] = right;

        while (nums[maxDeque[maxFront]] - nums[minDeque[minFront]] > 2) {
            if (minDeque[minFront] == left) {
                minFront++;
            }
            if (maxDeque[maxFront] == left) {
                maxFront++;
            }
            left++;
        }

        result += right - left + 1;
        right++;
    }

    return result;
}
