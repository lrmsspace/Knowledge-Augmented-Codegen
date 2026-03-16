// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums consisiting of positive integers. You can do the following operation on the array any number of times:
//
//
// 	Select an index i such that 0 <= i < n - 1 and replace either of nums[i] or nums[i+1] with their gcd value.
//
//
// Return the minimum number of operations to make all elements of nums equal to 1. If it is impossible, return -1.
//
// The gcd of two integers is the greatest common divisor of the two integers.
//
// Example:
// Input: nums = [2,6,3,4]
// Output: 4
// Explanation: We can do the following operations:
// - Choose index i = 2 and replace nums[2] with gcd(3,4) = 1. Now we have nums = [2,6,1,4].
// - Choose index i = 1 and replace nums[1] with gcd(6,1) = 1. Now we have nums = [2,1,1,4].
// - Choose index i = 0 and replace nums[0] with gcd(2,1) = 1. Now we have nums = [1,1,1,4].
// - Choose index i = 2 and replace nums[3] with gcd(1,4) = 1. Now we have nums = [1,1,1,1].
//
// Constraints:
// 2 <= nums.length <= 50
// 	1 <= nums[i] <= 106
//

int minOperations(int* nums, int numsSize) {
    int count_of_ones = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 1) {
            count_of_ones++;
        }
    }
    if (count_of_ones > 0) {
        return numsSize - count_of_ones;
    }

    int min_length = 100;
    for (int i = 0; i < numsSize; i++) {
        int current_gcd = nums[i];
        for (int j = i + 1; j < numsSize; j++) {
            current_gcd = gcd(current_gcd, nums[j]);
            if (current_gcd == 1) {
                int length = j - i + 1;
                if (length < min_length) {
                    min_length = length;
                }
                break;
            }
        }
    }

    if (min_length == 100) {
        return -1;
    } else {
        return numsSize - 1 + (min_length - 1);
    }       
}
