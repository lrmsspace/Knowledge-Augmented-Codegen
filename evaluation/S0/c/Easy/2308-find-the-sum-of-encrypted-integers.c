// Source: https://leetcode.com/problems/find-the-sum-of-encrypted-integers/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums containing positive integers. We define a function encrypt such that encrypt(x) replaces every digit in x with the largest digit in x. For example, encrypt(523) = 555 and encrypt(213) = 333.
//
// Return the sum of encrypted elements.
//
// Example:
// Input: nums = [1,2,3]
//
// Output: 6
//
// Explanation: The encrypted elements are [1,2,3]. The sum of encrypted elements is 1 + 2 + 3 == 6.
//
// Constraints:
// 1 <= nums.length <= 50
// 	1 <= nums[i] <= 1000
//

int sumOfEncryptedInt(int* nums, int numsSize) {
    int totalSum = 0;
    
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        int maxDigit = 0;
        
        // Find the maximum digit in the current number
        while (num > 0) {
            int digit = num % 10;
            if (digit > maxDigit) {
                maxDigit = digit;
            }
            num /= 10;
        }
        
        // Calculate the encrypted value
        int encryptedValue = 0;
        int tempNum = nums[i];
        int placeValue = 1;
        
        while (tempNum > 0) {
            encryptedValue += maxDigit * placeValue;
            placeValue *= 10;
            tempNum /= 10;
        }
        
        totalSum += encryptedValue;
    }
    
    return totalSum;        
}
