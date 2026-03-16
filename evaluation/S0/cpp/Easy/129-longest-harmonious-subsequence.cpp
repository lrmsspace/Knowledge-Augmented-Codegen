// Source: https://leetcode.com/problems/longest-harmonious-subsequence/   |   Difficulty: Easy
//
// Problem Description:
// We define a harmonious array as an array where the difference between its maximum value and its minimum value is exactly 1.
//
// Given an integer array nums, return the length of its longest harmonious subsequence among all its possible subsequences.
//
// Example:
// Input: nums = [1,3,2,2,5,2,3,7]
//
// Output: 5
//
// Explanation:
//
// The longest harmonious subsequence is [3,2,2,2,3].
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	-109 <= nums[i] <= 109
//

class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> countMap;
        int longestLength = 0;

        for (int num : nums) {
            countMap[num]++;
        }

        for (const auto& [num, count] : countMap) {
            if (countMap.find(num + 1) != countMap.end()) {
                longestLength = max(longestLength, count + countMap[num + 1]);
            }
        }

        return longestLength;           
    }
};
