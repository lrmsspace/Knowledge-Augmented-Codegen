// Source: https://leetcode.com/problems/4sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
//
//
// 	0 <= a, b, c, d < n
// 	a, b, c, and d are distinct.
// 	nums[a] + nums[b] + nums[c] + nums[d] == target
//
//
// You may return the answer in any order.
//
// Example:
// Input: nums = [1,0,-1,0,-2,2], target = 0
// Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
//
// Constraints:
// 1 <= nums.length <= 200
// 	-109 <= nums[i] <= 109
// 	-109 <= target <= 109
//

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        int n = nums.size();
        if (n < 4) return result;

        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 3; ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue; // Skip duplicates for the first number

            for (int j = i + 1; j < n - 2; ++j) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue; // Skip duplicates for the second number

                int left = j + 1;
                int right = n - 1;

                while (left < right) {
                    long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];

                    if (sum == target) {
                        result.push_back({nums[i], nums[j], nums[left], nums[right]});

                        // Skip duplicates for the third number
                        while (left < right && nums[left] == nums[left + 1]) ++left;
                        // Skip duplicates for the fourth number
                        while (left < right && nums[right] == nums[right - 1]) --right;

                        ++left;
                        --right;
                    } else if (sum < target) {
                        ++left;
                    } else {
                        --right;
                    }
                }
            }
        }

        return result;          
    }
};
