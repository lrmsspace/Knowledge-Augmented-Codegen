// Source: https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/   |   Difficulty: Easy
//
// Problem Description:
// Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.
//
// Example:
// Input: nums = [4,3,2,7,8,2,3,1]
// Output: [5,6]
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	1 <= nums[i] <= n
//
//
//  
// Follow up: Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.
//

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> result;
        for (int i = 0; i < nums.size(); ++i) {
            int index = abs(nums[i]) - 1;
            if (nums[index] > 0) {
                nums[index] = -nums[index];
            }
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] > 0) {
                result.push_back(i + 1);
            }
        }
        return result;          
    }
};
