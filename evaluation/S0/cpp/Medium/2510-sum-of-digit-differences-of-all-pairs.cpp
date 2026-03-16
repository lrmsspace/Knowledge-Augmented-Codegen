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

class Solution {
public:
    long long sumDigitDifferences(vector<int>& nums) {
        int n = nums.size();
        int d = to_string(nums[0]).size(); // number of digits
        vector<vector<int>> count(d, vector<int>(10, 0));

        // Count occurrences of each digit at each position
        for (int num : nums) {
            string s = to_string(num);
            for (int i = 0; i < d; ++i) {
                count[i][s[i] - '0']++;
            }
        }

        long long totalDiff = 0;
        // Calculate the sum of digit differences
        for (int i = 0; i < d; ++i) {
            for (int digit1 = 0; digit1 < 10; ++digit1) {
                for (int digit2 = 0; digit2 < 10; ++digit2) {
                    if (digit1 != digit2) {
                        totalDiff += (long long)count[i][digit1] * count[i][digit2];
                    }
                }
            }
        }

        return totalDiff;           
    }
};
