// Source: https://leetcode.com/problems/single-number-iii/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once. You can return the answer in any order.
//
// You must write an algorithm that runs in linear runtime complexity and uses only constant extra space.
//
// Example:
// Input: nums = [1,2,1,3,2,5]
// Output: [3,5]
// Explanation:  [5, 3] is also a valid answer.
//
// Constraints:
// 2 <= nums.length <= 3 * 104
// 	-231 <= nums[i] <= 231 - 1
// 	Each integer in nums will appear twice, only two integers will appear once.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* singleNumber(int* nums, int numsSize, int* returnSize) {
    int xor = 0;
    for (int i = 0; i < numsSize; i++) {
        xor ^= nums[i];
    }
    
    // Find a set bit (rightmost set bit)
    int diffBit = xor & (-xor);
    
    int* result = (int*)malloc(2 * sizeof(int));
    result[0] = 0;
    result[1] = 0;
    
    // Divide numbers into two groups based on the diffBit
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] & diffBit) {
            result[0] ^= nums[i];
        } else {
            result[1] ^= nums[i];
        }
    }
    
    *returnSize = 2;
    return result;
            
}
