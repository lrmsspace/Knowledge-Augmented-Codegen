// Source: https://leetcode.com/problems/sliding-subarray-beauty/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums containing n integers, find the beauty of each subarray of size k.
//
// The beauty of a subarray is the xth smallest integer in the subarray if it is negative, or 0 if there are fewer than x negative integers.
//
// Return an integer array containing n - k + 1 integers, which denote the beauty of the subarrays in order from the first index in the array.
//
//
// 	
// 	A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,-1,-3,-2,3], k = 3, x = 2
// Output: [-1,-2,-2]
// Explanation: There are 3 subarrays with size k = 3. 
// The first subarray is [1, -1, -3] and the 2nd smallest negative integer is -1. 
// The second subarray is [-1, -3, -2] and the 2nd smallest negative integer is -2. 
// The third subarray is [-3, -2, 3] and the 2nd smallest negative integer is -2.
//
// Constraints:
// n == nums.length 
// 	1 <= n <= 105
// 	1 <= k <= n
// 	1 <= x <= k 
// 	-50 <= nums[i] <= 50
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getSubarrayBeauty(int* nums, int numsSize, int k, int x, int* returnSize) {
    int *res = (int *)malloc((numsSize - k + 1) * sizeof(int));
    *returnSize = numsSize - k + 1;
    int count[51] = {0};
    int i, j, idx, negCount;

    // Initialize the count array with the first k elements
    for (i = 0; i < k; i++) {
        if (nums[i] < 0) {
            count[-nums[i]]++;
        }
    }

    // Function to find the x-th smallest negative number
    auto findXthNegative = [&](int x) {
        negCount = 0;
        for (j = 50; j >= 1; j--) {
            negCount += count[j];
            if (negCount >= x) {
                return -j;
            }
        }
        return 0;
    };

    // Get the beauty for the first window
    res[0] = findXthNegative(x);

    // Slide the window
    for (i = k; i < numsSize; i++) {
        // Remove the element going out of the window
        if (nums[i - k] < 0) {
            count[-nums[i - k]]--;
        }
        // Add the new element coming into the window
        if (nums[i] < 0) {
            count[-nums[i]]++;
        }
        // Get the beauty for the current window
        res[i - k + 1] = findXthNegative(x);
    }

    return res;     
}
