// Source: https://leetcode.com/problems/find-all-duplicates-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums of length n where all the integers of nums are in the range [1, n] and each integer appears at most twice, return an array of all the integers that appears twice.
//
// You must write an algorithm that runs in O(n) time and uses only constant auxiliary space, excluding the space needed to store the output
//
// Example:
// Input: nums = [4,3,2,7,8,2,3,1]
// Output: [2,3]
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	1 <= nums[i] <= n
// 	Each element in nums appears once or twice.
//

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> result;
        for (int i = 0; i < nums.size(); ++i) {
            int index = abs(nums[i]) - 1;
            if (nums[index] < 0) {
                result.push_back(index + 1);
            } else {
                nums[index] = -nums[index];
            }
        }
        return result;          
    }
};
