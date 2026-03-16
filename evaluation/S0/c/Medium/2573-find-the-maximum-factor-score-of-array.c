// Source: https://leetcode.com/problems/find-the-maximum-factor-score-of-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
// The factor score of an array is defined as the product of the LCM and GCD of all elements of that array.
//
// Return the maximum factor score of nums after removing at most one element from it.
//
// Note that both the LCM and GCD of a single number are the number itself, and the factor score of an empty array is 0.
//
// Example:
// Input: nums = [2,4,8,16]
//
// Output: 64
//
// Explanation:
//
// On removing 2, the GCD of the rest of the elements is 4 while the LCM is 16, which gives a maximum factor score of 4 * 16 = 64.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 30
//

long long maxScore(int* nums, int numsSize) {
    // Helper function to compute GCD
    int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    // Helper function to compute LCM
    int lcm(int a, int b) {
        return (a / gcd(a, b)) * b;
    }

    long long max_factor_score = 0;

    for (int i = 0; i < numsSize; i++) {
        int current_gcd = 0;
        int current_lcm = 1;

        for (int j = 0; j < numsSize; j++) {
            if (i == j) continue; // Skip the removed element
            current_gcd = (current_gcd == 0) ? nums[j] : gcd(current_gcd, nums[j]);
            current_lcm = lcm(current_lcm, nums[j]);
        }

        long long factor_score = (long long)current_gcd * current_lcm;
        if (factor_score > max_factor_score) {
            max_factor_score = factor_score;
        }
    }

    return max_factor_score;
}
