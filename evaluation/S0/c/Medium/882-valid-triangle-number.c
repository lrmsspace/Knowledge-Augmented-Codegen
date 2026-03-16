// Source: https://leetcode.com/problems/valid-triangle-number/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.
//
// Example:
// Input: nums = [2,2,3,4]
// Output: 3
// Explanation: Valid combinations are: 
// 2,3,4 (using the first 2)
// 2,3,4 (using the second 2)
// 2,2,3
//
// Constraints:
// 1 <= nums.length <= 1000
// 	0 <= nums[i] <= 1000
//

int triangleNumber(int* nums, int numsSize) {
    int count = 0;
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    for (int i = numsSize - 1; i >= 2; i--) {
        int left = 0;
        int right = i - 1;

        while (left < right) {
            if (nums[left] + nums[right] > nums[i]) {
                count += right - left;
                right--;
            } else {
                left++;
            }
        }
    }

    return count;       
}
