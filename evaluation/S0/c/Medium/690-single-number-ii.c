// Source: https://leetcode.com/problems/single-number-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums where every element appears three times except for one, which appears exactly once. Find the single element and return it.
//
// You must implement a solution with a linear runtime complexity and use only constant extra space.
//
// Example:
// Input: nums = [2,2,3,2]
// Output: 3
//
// Constraints:
// 1 <= nums.length <= 3 * 104
// 	-231 <= nums[i] <= 231 - 1
// 	Each element in nums appears exactly three times except for one element which appears once.
//

int singleNumber(int* nums, int numsSize) {
    int result = 0;
    for (int i = 0; i < 32; i++) {
        int bitCount = 0;
        for (int j = 0; j < numsSize; j++) {
            if ((nums[j] >> i) & 1) {
                bitCount++;
            }
        }
        if (bitCount % 3 != 0) {
            result |= (1 << i);
        }
    }
    return result;      
}
