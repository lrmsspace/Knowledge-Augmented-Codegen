// Source: https://leetcode.com/problems/find-the-xor-of-numbers-which-appear-twice/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array nums, where each number in the array appears either once or twice.
//
// Return the bitwise XOR of all the numbers that appear twice in the array, or 0 if no number appears twice.
//
// Example:
// Input: nums = [1,2,1,3]
//
// Output: 1
//
// Explanation:
//
// The only number that appears twice in nums is 1.
//
// Constraints:
// 1 <= nums.length <= 50
// 	1 <= nums[i] <= 50
// 	Each number in nums appears either once or twice.
//

int duplicateNumbersXOR(int* nums, int numsSize) {
    int count[51] = {0};
    int result = 0;

    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }

    for (int i = 1; i <= 50; i++) {
        if (count[i] == 2) {
            result ^= i;
        }
    }

    return result;      
}
