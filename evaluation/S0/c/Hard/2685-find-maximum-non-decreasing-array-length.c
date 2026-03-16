// Source: https://leetcode.com/problems/find-maximum-non-decreasing-array-length/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums.
//
// You can perform any number of operations, where each operation involves selecting a subarray of the array and replacing it with the sum of its elements. For example, if the given array is [1,3,5,6] and you select subarray [3,5] the array will convert to [1,8,6].
//
// Return the maximum length of a non-decreasing array that can be made after applying operations.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [5,2,2]
// Output: 1
// Explanation: This array with length 3 is not non-decreasing.
// We have two ways to make the array length two.
// First, choosing subarray [2,2] converts the array to [5,4].
// Second, choosing subarray [5,2] converts the array to [7,2].
// In these two ways the array is not non-decreasing.
// And if we choose subarray [5,2,2] and replace it with [9] it becomes non-decreasing. 
// So the answer is 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

int findMaximumLength(int* nums, int numsSize) {
    long long sum = 0;
    for (int i = 0; i < numsSize; ++i) {
        sum += nums[i];
    }
    int left = 1, right = numsSize, ans = 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        long long target = sum / mid;
        if (target * mid != sum) {
            right = mid - 1;
            continue;
        }
        long long currSum = 0;
        int count = 0;
        for (int i = 0; i < numsSize; ++i) {
            currSum += nums[i];
            if (currSum == target) {
                ++count;
                currSum = 0;
            } else if (currSum > target) {
                break;
            }
        }
        if (count == mid) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;     
}
