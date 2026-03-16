// Source: https://leetcode.com/problems/intersection-of-multiple-arrays/   |   Difficulty: Easy
//
// Problem Description:
// Given a 2D integer array nums where nums[i] is a non-empty array of distinct positive integers, return the list of integers that are present in each array of nums sorted in ascending order.
//
// Example:
// Input: nums = [[3,1,2,4,5],[1,2,3,4],[3,4,5,6]]
// Output: [3,4]
// Explanation: 
// The only integers present in each of nums[0] = [3,1,2,4,5], nums[1] = [1,2,3,4], and nums[2] = [3,4,5,6] are 3 and 4, so we return [3,4].
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= sum(nums[i].length) <= 1000
// 	1 <= nums[i][j] <= 1000
// 	All the values of nums[i] are unique.
//

class Solution {
public:
    vector<int> intersection(vector<vector<int>>& nums) {
        vector<int> count(1001, 0);
        for (const auto& arr : nums) {
            for (int num : arr) {
                count[num]++;
            }
        }

        vector<int> result;
        for (int i = 1; i <= 1000; ++i) {
            if (count[i] == nums.size()) {
                result.push_back(i);
            }
        }

        return result;          
    }
};
