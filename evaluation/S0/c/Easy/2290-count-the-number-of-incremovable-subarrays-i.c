// Source: https://leetcode.com/problems/count-the-number-of-incremovable-subarrays-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array of positive integers nums.
//
// A subarray of nums is called incremovable if nums becomes strictly increasing on removing the subarray. For example, the subarray [3, 4] is an incremovable subarray of [5, 3, 4, 6, 7] because removing this subarray changes the array [5, 3, 4, 6, 7] to [5, 6, 7] which is strictly increasing.
//
// Return the total number of incremovable subarrays of nums.
//
// Note that an empty array is considered strictly increasing.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 10
// Explanation: The 10 incremovable subarrays are: [1], [2], [3], [4], [1,2], [2,3], [3,4], [1,2,3], [2,3,4], and [1,2,3,4], because on removing any one of these subarrays nums becomes strictly increasing. Note that you cannot select an empty subarray.
//
// Constraints:
// 1 <= nums.length <= 50
// 	1 <= nums[i] <= 50
//

int incremovableSubarrayCount(int* nums, int numsSize) {
    int count = 0;

    for (int start = 0; start < numsSize; start++) {
        for (int end = start; end < numsSize; end++) {
            int prev = -1;
            int isIncreasing = 1;

            for (int i = 0; i < numsSize; i++) {
                if (i >= start && i <= end) {
                    continue; // Skip the subarray
                }
                if (nums[i] <= prev) {
                    isIncreasing = 0;
                    break;
                }
                prev = nums[i];
            }

            if (isIncreasing) {
                count++;
            }
        }
    }

    return count;       
}
