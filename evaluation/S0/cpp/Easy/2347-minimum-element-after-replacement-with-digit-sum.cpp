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

class Solution {
public:
    int minElement(vector<int>& nums) {
        int min_sum = INT_MAX;

        for (int num : nums) {
            int digit_sum = 0;
            while (num > 0) {
                digit_sum += num % 10;
                num /= 10;
            }
            min_sum = min(min_sum, digit_sum);
        }

        return min_sum;         
    }
};
