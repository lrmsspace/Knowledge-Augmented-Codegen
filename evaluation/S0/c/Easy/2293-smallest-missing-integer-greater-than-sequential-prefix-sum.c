// Source: https://leetcode.com/problems/smallest-missing-integer-greater-than-sequential-prefix-sum/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed array of integers nums.
//
// A prefix nums[0..i] is sequential if, for all 1 <= j <= i, nums[j] = nums[j - 1] + 1. In particular, the prefix consisting only of nums[0] is sequential.
//
// Return the smallest integer x missing from nums such that x is greater than or equal to the sum of the longest sequential prefix.
//
// Example:
// Input: nums = [1,2,3,2,5]
// Output: 6
// Explanation: The longest sequential prefix of nums is [1,2,3] with a sum of 6. 6 is not in the array, therefore 6 is the smallest missing integer greater than or equal to the sum of the longest sequential prefix.
//
// Constraints:
// 1 <= nums.length <= 50
// 	1 <= nums[i] <= 50
//

int missingInteger(int* nums, int numsSize) {
    int expected = nums[0];
    int prefix_sum = 0;
    int i;

    for (i = 0; i < numsSize; i++) {
        if (nums[i] == expected) {
            prefix_sum += nums[i];
            expected++;
        } else {
            break;
        }
    }

    for (i = 0; i < numsSize; i++) {
        if (nums[i] == prefix_sum) {
            return prefix_sum + 1;
        }
    }

    return prefix_sum;      
}
