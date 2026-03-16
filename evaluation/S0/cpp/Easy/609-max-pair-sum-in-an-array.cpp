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

class Solution {
public:
    int maxSum(vector<int>& nums) {
        vector<int> maxDigit(10, -1);
        int result = -1;

        for (int num : nums) {
            int largest = 0, n = num;

            while (n > 0) {
                largest = max(largest, n % 10);
                n /= 10;
            }

            if (maxDigit[largest] != -1) {
                result = max(result, num + maxDigit[largest]);
            }

            maxDigit[largest] = max(maxDigit[largest], num);
        }

        return result;          
    }
};
