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

class Solution {
public:
    int sumOfEncryptedInt(vector<int>& nums) {
        int totalSum = 0;

        for (int num : nums) {
            int maxDigit = 0;
            int temp = num;

            // Find the largest digit in the number
            while (temp > 0) {
                int digit = temp % 10;
                maxDigit = max(maxDigit, digit);
                temp /= 10;
            }

            // Add the encrypted value to the total sum
            totalSum += maxDigit * to_string(num).length();
        }

        return totalSum;            
    }
};
