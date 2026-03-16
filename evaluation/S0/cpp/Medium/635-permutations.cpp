// Source: https://leetcode.com/problems/permutations/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.
//
// Example:
// Input: nums = [1,2,3]
// Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
//
// Constraints:
// 1 <= nums.length <= 6
// 	-10 <= nums[i] <= 10
// 	All the integers of nums are unique.
//

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        vector<bool> used(nums.size(), false);

        function<void()> backtrack = [&]() {
            if (current.size() == nums.size()) {
                result.push_back(current);
                return;
            }
            for (size_t i = 0; i < nums.size(); ++i) {
                if (used[i]) continue;
                used[i] = true;
                current.push_back(nums[i]);
                backtrack();
                current.pop_back();
                used[i] = false;
            }
        };

        backtrack();
        return result;          
    }
};
