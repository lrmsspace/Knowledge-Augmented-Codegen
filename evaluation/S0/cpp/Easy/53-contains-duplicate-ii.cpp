// Source: https://leetcode.com/problems/contains-duplicate-ii/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums and an integer k, return true if there are two distinct indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.
//
// Example:
// Input: nums = [1,2,3,1], k = 3
// Output: true
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
// 	0 <= k <= 105
//

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> numIndices; // Map to store the last index of each number

        for (int i = 0; i < nums.size(); ++i) {
            if (numIndices.find(nums[i]) != numIndices.end()) {
                // If the number has been seen before, check the index difference
                if (i - numIndices[nums[i]] <= k) {
                    return true; // Found a duplicate within the allowed distance
                }
            }
            // Update the last index of the current number
            numIndices[nums[i]] = i;
        }

        return false; // No duplicates found within the allowed distance            
    }
};
