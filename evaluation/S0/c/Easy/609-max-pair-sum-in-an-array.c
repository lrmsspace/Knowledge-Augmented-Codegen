// Source: https://leetcode.com/problems/max-pair-sum-in-an-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums. You have to find the maximum sum of a pair of numbers from nums such that the largest digit in both numbers is equal.
//
// For example, 2373 is made up of three distinct digits: 2, 3, and 7, where 7 is the largest among them.
//
// Return the maximum sum or -1 if no such pair exists.
//
// Example:
// Input: nums = [112,131,411]
//
// Output: -1
//
// Explanation:
//
// Each numbers largest digit in order is [2,3,4].
//
// Constraints:
// 2 <= nums.length <= 100
// 	1 <= nums[i] <= 104
//

int maxSum(int* nums, int numsSize) {
    int maxSum = -1;
    int digitBuckets[10][2]; // Each bucket holds the top two largest numbers for each digit

    // Initialize the buckets
    for (int i = 0; i < 10; i++) {
        digitBuckets[i][0] = -1; // Largest number
        digitBuckets[i][1] = -1; // Second largest number
    }

    // Function to find the largest digit in a number
    int largestDigit(int num) {
        int maxDigit = 0;
        while (num > 0) {
            int digit = num % 10;
            if (digit > maxDigit) {
                maxDigit = digit;
            }
            num /= 10;
        }
        return maxDigit;
    }

    // Populate the buckets
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        int lDigit = largestDigit(num);

        if (num > digitBuckets[lDigit][0]) {
            digitBuckets[lDigit][1] = digitBuckets[lDigit][0];
            digitBuckets[lDigit][0] = num;
        } else if (num > digitBuckets[lDigit][1]) {
            digitBuckets[lDigit][1] = num;
        }
    }

    // Calculate the maximum sum from the buckets
    for (int i = 0; i < 10; i++) {
        if (digitBuckets[i][1] != -1) { // Ensure there are at least two numbers
            int currentSum = digitBuckets[i][0] + digitBuckets[i][1];
            if (currentSum > maxSum) {
                maxSum = currentSum;
            }
        }
    }

    return maxSum;      
}
