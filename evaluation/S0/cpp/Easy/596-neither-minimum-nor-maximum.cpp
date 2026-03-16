// Source: https://leetcode.com/problems/neither-minimum-nor-maximum/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums containing distinct positive integers, find and return any number from the array that is neither the minimum nor the maximum value in the array, or -1 if there is no such number.
//
// Return the selected integer.
//
// Example:
// Input: nums = [3,2,1,4]
// Output: 2
// Explanation: In this example, the minimum value is 1 and the maximum value is 4. Therefore, either 2 or 3 can be valid answers.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
// 	All values in nums are distinct
//

class Solution {
public:
    int findNonMinOrMax(vector<int>& nums) {
        if (nums.size() <= 2) {
            return -1;
        }
        
        int minVal = INT_MAX;
        int maxVal = INT_MIN;
        
        for (int num : nums) {
            minVal = min(minVal, num);
            maxVal = max(maxVal, num);
        }
        
        for (int num : nums) {
            if (num != minVal && num != maxVal) {
                return num;
            }
        }
        
        return -1; // This line should never be reached due to the earlier size check           
    }
};
