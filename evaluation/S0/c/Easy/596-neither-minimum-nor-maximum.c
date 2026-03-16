// Source: https://leetcode.com/problems/neither-minimum-nor-maximum/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums containing distinct positive integers, find and return any number from the array that is neither the minimum nor the maximum value in the array, or -1 if there is no such number.
//
// Return the selected integer.
//
// Example:
// Input: nums = [3,2,1,4]
// Output: 2
// Explanation: In this example, the minimum value is 1 and the maximum value is 4. Therefore, either 2 or 3 can be valid answers.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
// 	All values in nums are distinct
//

int findNonMinOrMax(int* nums, int numsSize) {
    if (numsSize <= 2) {
        return -1;
    }

    int min = nums[0];
    int max = nums[0];

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < min) {
            min = nums[i];
        } else if (nums[i] > max) {
            max = nums[i];
        }
    }

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != min && nums[i] != max) {
            return nums[i];
        }
    }

    return -1; // This line should never be reached due to the earlier size check       
}
