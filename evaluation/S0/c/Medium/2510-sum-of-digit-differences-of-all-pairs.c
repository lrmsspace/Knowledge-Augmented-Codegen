// Source: https://leetcode.com/problems/sum-of-digit-differences-of-all-pairs/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers where all integers have the same number of digits.
//
// The digit difference between two integers is the count of different digits that are in the same position in the two integers.
//
// Return the sum of the digit differences between all pairs of integers in nums.
//
// Example:
// Input: nums = [13,23,12]
//
// Output: 4
//
// Explanation:
// We have the following:
// - The digit difference between 13 and 23 is 1.
// - The digit difference between 13 and 12 is 1.
// - The digit difference between 23 and 12 is 2.
// So the total sum of digit differences between all pairs of integers is 1 + 1 + 2 = 4.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] < 109
// 	All integers in nums have the same number of digits.
//

long long sumDigitDifferences(int* nums, int numsSize) {
    long long result = 0;
    int digitCount = 0;
    int temp = nums[0];
    
    // Determine the number of digits in the numbers
    while (temp > 0) {
        digitCount++;
        temp /= 10;
    }
    
    // Create a frequency array for each digit position
    int freq[digitCount][10];
    for (int i = 0; i < digitCount; i++) {
        for (int j = 0; j < 10; j++) {
            freq[i][j] = 0;
        }
    }
    
    // Populate the frequency array
    for (int i = 0; i < numsSize; i++) {
        int number = nums[i];
        for (int d = digitCount - 1; d >= 0; d--) {
            int digit = number % 10;
            freq[d][digit]++;
            number /= 10;
        }
    }
    
    // Calculate the sum of digit differences
    for (int d = 0; d < digitCount; d++) {
        for (int digit1 = 0; digit1 < 10; digit1++) {
            for (int digit2 = 0; digit2 < 10; digit2++) {
                if (digit1 != digit2) {
                    result += (long long)freq[d][digit1] * freq[d][digit2];
                }
            }
        }
    }
    
    return result;      
}
