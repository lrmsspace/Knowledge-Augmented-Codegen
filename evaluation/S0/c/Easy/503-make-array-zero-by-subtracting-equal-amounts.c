// Source: https://leetcode.com/problems/make-array-zero-by-subtracting-equal-amounts/   |   Difficulty: Easy
//
// Problem Description:
// You are given a non-negative integer array nums. In one operation, you must:
//
//
// 	Choose a positive integer x such that x is less than or equal to the smallest non-zero element in nums.
// 	Subtract x from every positive element in nums.
//
//
// Return the minimum number of operations to make every element in nums equal to 0.
//
// Example:
// Input: nums = [1,5,0,3,5]
// Output: 3
// Explanation:
// In the first operation, choose x = 1. Now, nums = [0,4,0,2,4].
// In the second operation, choose x = 2. Now, nums = [0,2,0,0,2].
// In the third operation, choose x = 2. Now, nums = [0,0,0,0,0].
//
// Constraints:
// 1 <= nums.length <= 100
// 	0 <= nums[i] <= 100
//

int minimumOperations(int* nums, int numsSize) {
    int seen[101] = {0};
    int operations = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > 0 && seen[nums[i]] == 0) {
            seen[nums[i]] = 1;
            operations++;
        }
    }

    return operations;      
}
