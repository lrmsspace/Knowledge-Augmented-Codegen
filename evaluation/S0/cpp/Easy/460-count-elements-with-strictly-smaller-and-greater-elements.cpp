// Source: https://leetcode.com/problems/count-elements-with-strictly-smaller-and-greater-elements/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, return the number of elements that have both a strictly smaller and a strictly greater element appear in nums.
//
// Example:
// Input: nums = [11,7,2,15]
// Output: 2
// Explanation: The element 7 has the element 2 strictly smaller than it and the element 11 strictly greater than it.
// Element 11 has element 7 strictly smaller than it and element 15 strictly greater than it.
// In total there are 2 elements having both a strictly smaller and a strictly greater element appear in nums.
//
// Constraints:
// 1 <= nums.length <= 100
// 	-105 <= nums[i] <= 105
//

class Solution {
public:
    int countElements(vector<int>& nums) {
        int minVal = *min_element(nums.begin(), nums.end());
        int maxVal = *max_element(nums.begin(), nums.end());
        int count = 0;

        for (int num : nums) {
            if (num > minVal && num < maxVal) {
                count++;
            }
        }

        return count;           
    }
};
