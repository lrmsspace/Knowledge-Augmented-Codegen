// Source: https://leetcode.com/problems/find-subarrays-with-equal-sum/   |   Difficulty: Easy
//
// Problem Description:
// Given a 0-indexed integer array nums, determine whether there exist two subarrays of length 2 with equal sum. Note that the two subarrays must begin at different indices.
//
// Return true if these subarrays exist, and false otherwise.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [4,2,4]
// Output: true
// Explanation: The subarrays with elements [4,2] and [2,4] have the same sum of 6.
//
// Constraints:
// 2 <= nums.length <= 1000
// 	-109 <= nums[i] <= 109
//

class Solution {
public:
    bool findSubarrays(vector<int>& nums) {
        unordered_set<int> seenSums;
        for (size_t i = 0; i < nums.size() - 1; ++i) {
            int currentSum = nums[i] + nums[i + 1];
            if (seenSums.count(currentSum)) {
                return true;
            }
            seenSums.insert(currentSum);
        }
        return false;           
    }
};
