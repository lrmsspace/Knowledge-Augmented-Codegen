// Source: https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.
//
// If target is not found in the array, return [-1, -1].
//
// You must write an algorithm with O(log n) runtime complexity.
//
// Example:
// Input: nums = [5,7,7,8,8,10], target = 8
// Output: [3,4]
//
// Constraints:
// 0 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
// 	nums is a non-decreasing array.
// 	-109 <= target <= 109
//

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        vector<int> result(2, -1);

        // Find the first occurrence
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        if (left >= nums.size() || nums[left] != target) {
            return result; // Target not found
        }
        result[0] = left;

        // Find the last occurrence
        right = nums.size() - 1; // Reset right pointer
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] <= target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        result[1] = right;

        return result;          
    }
};
