// Source: https://leetcode.com/problems/largest-perimeter-triangle/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, return the largest perimeter of a triangle with a non-zero area, formed from three of these lengths. If it is impossible to form any triangle of a non-zero area, return 0.
//
// Example:
// Input: nums = [2,1,2]
// Output: 5
// Explanation: You can form a triangle with three side lengths: 1, 2, and 2.
//
// Constraints:
// 3 <= nums.length <= 104
// 	1 <= nums[i] <= 106
//

int largestPerimeter(int* nums, int numsSize) {
    // Sort the array in descending order
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = 0; j < numsSize - i - 1; j++) {
            if (nums[j] < nums[j + 1]) {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }

    // Check for the largest perimeter
    for (int i = 0; i < numsSize - 2; i++) {
        if (nums[i] < nums[i + 1] + nums[i + 2]) {
            return nums[i] + nums[i + 1] + nums[i + 2];
        }
    }

    return 0;       
}
