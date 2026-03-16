// Source: https://leetcode.com/problems/contains-duplicate/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
//
// Example:
// Input: nums = [1,2,3,1]
//
// Output: true
//
// Explanation:
//
// The element 1 occurs at the indices 0 and 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
//

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for (const int& num : nums) {
            if (seen.find(num) != seen.end()) {
                return true; // Duplicate found
            }
            seen.insert(num);
        }
        return false; // No duplicates found            
    }
};
