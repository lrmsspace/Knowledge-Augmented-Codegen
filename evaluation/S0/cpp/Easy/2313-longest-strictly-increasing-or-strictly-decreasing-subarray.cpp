// Source: https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of integers nums. Return the length of the longest subarray of nums which is either strictly increasing or strictly decreasing.
//
// Example:
// Input: nums = [1,4,3,3,2]
//
// Output: 2
//
// Explanation:
//
// The strictly increasing subarrays of nums are [1], [2], [3], [3], [4], and [1,4].
//
// The strictly decreasing subarrays of nums are [1], [2], [3], [3], [4], [3,2], and [4,3].
//
// Hence, we return 2.
//
// Constraints:
// 1 <= nums.length <= 50
// 	1 <= nums[i] <= 50
//

class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 1;

        int maxLength = 1;
        int currentLength = 1;
        bool increasing = false;
        bool decreasing = false;

        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[i - 1]) {
                if (increasing) {
                    currentLength++;
                } else {
                    currentLength = 2; // reset length for new increasing subarray
                    increasing = true;
                    decreasing = false;
                }
            } else if (nums[i] < nums[i - 1]) {
                if (decreasing) {
                    currentLength++;
                } else {
                    currentLength = 2; // reset length for new decreasing subarray
                    decreasing = true;
                    increasing = false;
                }
            } else {
                currentLength = 1; // reset length for equal elements
                increasing = false;
                decreasing = false;
            }
            maxLength = max(maxLength, currentLength);
        }

        return maxLength;           
    }
};
