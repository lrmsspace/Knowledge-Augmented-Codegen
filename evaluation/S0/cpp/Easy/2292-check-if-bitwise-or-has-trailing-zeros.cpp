// Source: https://leetcode.com/problems/check-if-bitwise-or-has-trailing-zeros/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of positive integers nums.
//
// You have to check if it is possible to select two or more elements in the array such that the bitwise OR of the selected elements has at least one trailing zero in its binary representation.
//
// For example, the binary representation of 5, which is "101", does not have any trailing zeros, whereas the binary representation of 4, which is "100", has two trailing zeros.
//
// Return true if it is possible to select two or more elements whose bitwise OR has trailing zeros, return false otherwise.
//
// Example:
// Input: nums = [1,2,3,4,5]
// Output: true
// Explanation: If we select the elements 2 and 4, their bitwise OR is 6, which has the binary representation "110" with one trailing zero.
//
// Constraints:
// 2 <= nums.length <= 100
// 	1 <= nums[i] <= 100
//

class Solution {
public:
    bool hasTrailingZeros(vector<int>& nums) {
        int countEven = 0;
        for (int num : nums) {
            if (num % 2 == 0) {
                countEven++;
                if (countEven >= 2) {
                    return true;
                }
            }
        }
        return false;           
    }
};
