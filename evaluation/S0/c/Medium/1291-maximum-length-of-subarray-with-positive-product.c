// Source: https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums, find the maximum length of a subarray where the product of all its elements is positive.
//
// A subarray of an array is a consecutive sequence of zero or more values taken out of that array.
//
// Return the maximum length of a subarray with positive product.
//
// Example:
// Input: nums = [1,-2,-3,4]
// Output: 4
// Explanation: The array nums already has a positive product of 24.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
//

int getMaxLen(int* nums, int numsSize) {
    int maxLength = 0;
    int positiveLength = 0;
    int negativeLength = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > 0) {
            positiveLength++;
            negativeLength = (negativeLength > 0) ? negativeLength + 1 : 0;
        } else if (nums[i] < 0) {
            int temp = positiveLength;
            positiveLength = (negativeLength > 0) ? negativeLength + 1 : 0;
            negativeLength = temp + 1;
        } else {
            positiveLength = 0;
            negativeLength = 0;
        }
        if (positiveLength > maxLength) {
            maxLength = positiveLength;
        }
    }

    return maxLength;       
}
