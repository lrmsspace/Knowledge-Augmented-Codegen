// Source: https://leetcode.com/problems/minimum-array-length-after-pair-removals/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array num sorted in non-decreasing order.
//
// You can perform the following operation any number of times:
//
//
// 	Choose two indices, i and j, where nums[i] < nums[j].
// 	Then, remove the elements at indices i and j from nums. The remaining elements retain their original order, and the array is re-indexed.
//
//
// Return the minimum length of nums after applying the operation zero or more times.
//
// Example:
// Input: nums = [1,2,3,4]
//
// Output: 0
//
// Explanation:
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	nums is sorted in non-decreasing order.
//

int minLengthAfterRemovals(int* nums, int numsSize) {
    int left = 0, right = numsSize / 2, result = numsSize;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int i = 0, j = numsSize - mid;
        int pairs = 0;

        while (i < mid && j < numsSize) {
            if (nums[i] < nums[j]) {
                pairs++;
                i++;
            }
            j++;
        }

        if (pairs >= mid) {
            result = numsSize - mid * 2;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;      
}
