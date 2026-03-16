// Source: https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/   |   Difficulty: Hard
//
// Problem Description:
// You may recall that an array arr is a mountain array if and only if:
//
//
// 	arr.length >= 3
// 	There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
// 	
// 		arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
// 		arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
// 	
// 	
//
//
// Given an integer array nums​​​, return the minimum number of elements to remove to make nums​​​ a mountain array.
//
// Example:
// Input: nums = [1,3,1]
// Output: 0
// Explanation: The array itself is a mountain array so we do not need to remove any elements.
//
// Constraints:
// 3 <= nums.length <= 1000
// 	1 <= nums[i] <= 109
// 	It is guaranteed that you can make a mountain array out of nums.
//

int minimumMountainRemovals(int* nums, int numsSize) {
    if (numsSize < 3) return 0;

    int *left = (int*)calloc(numsSize, sizeof(int));
    int *right = (int*)calloc(numsSize, sizeof(int));
    if (!left || !right) {
        free(left);
        free(right);
        return 0;
    }

    for (int i = 0; i < numsSize; ++i) {
        left[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (nums[j] < nums[i] && left[j] + 1 > left[i]) {
                left[i] = left[j] + 1;
            }
        }
    }

    for (int i = numsSize - 1; i >= 0; --i) {
        right[i] = 1;
        for (int j = numsSize - 1; j > i; --j) {
            if (nums[j] < nums[i] && right[j] + 1 > right[i]) {
                right[i] = right[j] + 1;
            }
        }
    }

    int maxMountainLen = 0;
    for (int i = 1; i < numsSize - 1; ++i) {
        if (left[i] > 1 && right[i] > 1) {
            int mountainLen = left[i] + right[i] - 1;
            if (mountainLen > maxMountainLen) {
                maxMountainLen = mountainLen;
            }
        }
    }

    free(left);
    free(right);

    return numsSize - maxMountainLen;       
}
