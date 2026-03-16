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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        auto lower_bound = [&](const vector<int>& arr, int tgt) -> int {
            int l = 0, r = arr.size();
            while (l < r) {
                int mid = l + (r - l) / 2;
                if (arr[mid] < tgt)
                    l = mid + 1;
                else
                    r = mid;
            }
            return l;
        };

        auto upper_bound = [&](const vector<int>& arr, int tgt) -> int {
            int l = 0, r = arr.size();
            while (l < r) {
                int mid = l + (r - l) / 2;
                if (arr[mid] <= tgt)
                    l = mid + 1;
                else
                    r = mid;
            }
            return l;
        };

        int left = lower_bound(nums, target);
        int right = upper_bound(nums, target) - 1;

        if (left <= right && right < nums.size() && nums[left] == target && nums[right] == target) {
            return {left, right};
        } else {
            return {-1, -1};
        }           
    }
};
