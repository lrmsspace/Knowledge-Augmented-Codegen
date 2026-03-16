// Source: https://leetcode.com/problems/special-array-i/   |   Difficulty: Easy
//
// Problem Description:
// An array is considered special if the parity of every pair of adjacent elements is different. In other words, one element in each pair must be even, and the other must be odd.
//
// You are given an array of integers nums. Return true if nums is a special array, otherwise, return false.
//
// Example:
// Input: nums = [1]
//
// Output: true
//
// Explanation:
//
// There is only one element. So the answer is true.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
//

bool isArraySpecial(int* nums, int numsSize) {
    for (int i = 0; i < numsSize - 1; i++) {
        if ((nums[i] % 2) == (nums[i + 1] % 2)) {
            return false;
        }
    }
    return true;        
}
