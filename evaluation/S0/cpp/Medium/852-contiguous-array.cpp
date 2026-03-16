// Source: https://leetcode.com/problems/contiguous-array/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.
//
// Example:
// Input: nums = [0,1]
// Output: 2
// Explanation: [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is either 0 or 1.
//

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> countIndexMap;
        countIndexMap[0] = -1; // Initialize with count 0 at index -1
        int maxLength = 0;
        int count = 0;

        for (int i = 0; i < nums.size(); ++i) {
            count += (nums[i] == 1) ? 1 : -1;

            if (countIndexMap.find(count) != countIndexMap.end()) {
                maxLength = max(maxLength, i - countIndexMap[count]);
            } else {
                countIndexMap[count] = i;
            }
        }

        return maxLength;           
    }
};
