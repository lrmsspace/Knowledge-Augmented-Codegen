// Source: https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and a positive integer k.
//
// Return the number of subarrays where the maximum element of nums appears at least k times in that subarray.
//
// A subarray is a contiguous sequence of elements within an array.
//
// Example:
// Input: nums = [1,3,2,3,3], k = 2
// Output: 6
// Explanation: The subarrays that contain the element 3 at least 2 times are: [1,3,2,3], [1,3,2,3,3], [3,2,3], [3,2,3,3], [2,3,3] and [3,3].
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
// 	1 <= k <= 105
//

long long countSubarrays(int* nums, int numsSize, int k) {
    long long result = 0;
    int max = 0;
    int count = 0;
    int start = 0;
    int i;

    for (i = 0; i < numsSize; i++) {
        if (nums[i] > max) {
            max = nums[i];
            count = 1;
        } else if (nums[i] == max) {
            count++;
        }

        while (count >= k) {
            result += numsSize - i;
            if (nums[start] == max) {
                count--;
            }
            start++;
        }
    }

    return result;      
}
