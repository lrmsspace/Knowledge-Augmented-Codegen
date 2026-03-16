// Source: https://leetcode.com/problems/count-number-of-maximum-bitwise-or-subsets/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, find the maximum possible bitwise OR of a subset of nums and return the number of different non-empty subsets with the maximum bitwise OR.
//
// An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b. Two subsets are considered different if the indices of the elements chosen are different.
//
// The bitwise OR of an array a is equal to a[0] OR a[1] OR ... OR a[a.length - 1] (0-indexed).
//
// Example:
// Input: nums = [3,1]
// Output: 2
// Explanation: The maximum possible bitwise OR of a subset is 3. There are 2 subsets with a bitwise OR of 3:
// - [3]
// - [3,1]
//
// Constraints:
// 1 <= nums.length <= 16
// 	1 <= nums[i] <= 105
//

int countMaxOrSubsets(int* nums, int numsSize) {
    int max_or = 0;
    int count = 0;
    int total_subsets = 1 << numsSize; // 2^numsSize

    // Calculate the maximum bitwise OR
    for (int i = 0; i < numsSize; i++) {
        max_or |= nums[i];
    }

    // Count subsets with maximum bitwise OR
    for (int subset = 1; subset < total_subsets; subset++) {
        int current_or = 0;
        for (int j = 0; j < numsSize; j++) {
            if (subset & (1 << j)) {
                current_or |= nums[j];
            }
        }
        if (current_or == max_or) {
            count++;
        }
    }

    return count;       
}
