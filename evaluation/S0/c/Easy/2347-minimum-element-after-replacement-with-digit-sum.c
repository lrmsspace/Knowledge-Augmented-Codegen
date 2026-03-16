// Source: https://leetcode.com/problems/minimum-element-after-replacement-with-digit-sum/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums.
//
// You replace each element in nums with the sum of its digits.
//
// Return the minimum element in nums after all replacements.
//
// Example:
// Input: nums = [10,12,13,14]
//
// Output: 1
//
// Explanation:
//
// nums becomes [1, 3, 4, 5] after all replacements, with minimum element 1.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 104
//

int minElement(int* nums, int numsSize) {
    int min = 10; // Since the maximum digit sum for any number <= 10^4 is 36, we can safely start with 10.
    
    for (int i = 0; i < numsSize; i++) {
        int sum = 0;
        int num = nums[i];
        
        // Calculate the sum of digits
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }
        
        // Update minimum if current sum is less
        if (sum < min) {
            min = sum;
        }
    }
    
    return min;     
}
