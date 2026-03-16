// Source: https://leetcode.com/problems/shortest-unsorted-continuous-subarray/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, you need to find one continuous subarray such that if you only sort this subarray in non-decreasing order, then the whole array will be sorted in non-decreasing order.
//
// Return the shortest such subarray and output its length.
//
// Example:
// Input: nums = [2,6,4,8,10,9,15]
// Output: 5
// Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
//
// Constraints:
// 1 <= nums.length <= 104
// 	-105 <= nums[i] <= 105
//
//
//  
// Follow up: Can you solve it in O(n) time complexity?
//

class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        int left = -1, right = -1;
        int max_so_far = nums[0];
        int min_so_far = nums[n - 1];

        for (int i = 1; i < n; ++i) {
            max_so_far = max(max_so_far, nums[i]);
            if (nums[i] < max_so_far) {
                right = i;
            }
        }

        for (int i = n - 2; i >= 0; --i) {
            min_so_far = min(min_so_far, nums[i]);
            if (nums[i] > min_so_far) {
                left = i;
            }
        }

        return left == -1 ? 0 : right - left + 1;           
    }
};
