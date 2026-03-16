// Source: https://leetcode.com/problems/minimum-operations-to-convert-all-elements-to-zero/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums of size n, consisting of non-negative integers. Your task is to apply some (possibly zero) operations on the array so that all elements become 0.
//
// In one operation, you can select a subarray [i, j] (where 0 <= i <= j < n) and set all occurrences of the minimum non-negative integer in that subarray to 0.
//
// Return the minimum number of operations required to make all elements in the array 0.
//
// Example:
// Input: nums = [0,2]
//
// Output: 1
//
// Explanation:
//
//
// 	Select the subarray [1,1] (which is [2]), where the minimum non-negative integer is 2. Setting all occurrences of 2 to 0 results in [0,0].
// 	Thus, the minimum number of operations required is 1.
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	0 <= nums[i] <= 105
//

int minOperations(int* nums, int numsSize) {
    int operations = 0;
    int maxNum = 0;

    // Find the maximum number in the array
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > maxNum) {
            maxNum = nums[i];
        }
    }

    // Create a boolean array to track presence of numbers
    char *present = (char *)calloc(maxNum + 1, sizeof(char));
    if (!present) {
        return -1; // Memory allocation failed
    }

    // Mark the presence of each number in the input array
    for (int i = 0; i < numsSize; i++) {
        present[nums[i]] = 1;
    }

    // Count the number of unique non-zero numbers
    for (int i = 1; i <= maxNum; i++) {
        if (present[i]) {
            operations++;
        }
    }

    free(present);
    return operations;      
}
