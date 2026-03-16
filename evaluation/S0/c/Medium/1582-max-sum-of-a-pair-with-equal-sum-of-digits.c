// Source: https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums consisting of positive integers. You can choose two indices i and j, such that i != j, and the sum of digits of the number nums[i] is equal to that of nums[j].
//
// Return the maximum value of nums[i] + nums[j] that you can obtain over all possible indices i and j that satisfy the conditions. If no such pair of indices exists, return -1.
//
// Example:
// Input: nums = [18,43,36,13,7]
// Output: 54
// Explanation: The pairs (i, j) that satisfy the conditions are:
// - (0, 2), both numbers have a sum of digits equal to 9, and their sum is 18 + 36 = 54.
// - (1, 4), both numbers have a sum of digits equal to 7, and their sum is 43 + 7 = 50.
// So the maximum sum that we can obtain is 54.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

int maximumSum(int* nums, int numsSize) {
    int maxSum = -1;
    int digitSumMap[91][2] = {0}; // Since the maximum sum of digits for a number <= 10^9 is 81 (9*9), we use 91 to be safe.

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        int digitSum = 0;

        // Calculate the sum of digits
        while (num > 0) {
            digitSum += num % 10;
            num /= 10;
        }

        // Update the two largest numbers for this digit sum
        if (nums[i] > digitSumMap[digitSum][0]) {
            digitSumMap[digitSum][1] = digitSumMap[digitSum][0];
            digitSumMap[digitSum][0] = nums[i];
        } else if (nums[i] > digitSumMap[digitSum][1]) {
            digitSumMap[digitSum][1] = nums[i];
        }
    }

    // Calculate the maximum sum of pairs with equal digit sums
    for (int i = 0; i < 91; i++) {
        if (digitSumMap[i][1] > 0) { // Ensure there are at least two numbers
            int currentSum = digitSumMap[i][0] + digitSumMap[i][1];
            if (currentSum > maxSum) {
                maxSum = currentSum;
            }
        }
    }

    return maxSum;      
}
