// Source: https://leetcode.com/problems/maximum-strength-of-a-group/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums representing the score of students in an exam. The teacher would like to form one non-empty group of students with maximal strength, where the strength of a group of students of indices i0, i1, i2, ... , ik is defined as nums[i0] * nums[i1] * nums[i2] * ... * nums[ik​].
//
// Return the maximum strength of a group the teacher can create.
//
// Example:
// Input: nums = [3,-1,-5,2,5,-9]
// Output: 1350
// Explanation: One way to form a group of maximal strength is to group the students at indices [0,2,3,4,5]. Their strength is 3 * (-5) * 2 * 5 * (-9) = 1350, which we can show is optimal.
//
// Constraints:
// 1 <= nums.length <= 13
// 	-9 <= nums[i] <= 9
//

long long maxStrength(int* nums, int numsSize) {
    long long max_product = LLONG_MIN;
    int total_subsets = 1 << numsSize; // Total subsets = 2^n

    for (int subset_mask = 1; subset_mask < total_subsets; subset_mask++) {
        long long current_product = 1;
        for (int j = 0; j < numsSize; j++) {
            if (subset_mask & (1 << j)) {
                current_product *= nums[j];
            }
        }
        if (current_product > max_product) {
            max_product = current_product;
        }
    }

    return max_product;     
}
