// Source: https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array nums of non-negative integers and an integer k.
//
// An array is called special if the bitwise OR of all of its elements is at least k.
//
// Return the length of the shortest special non-empty subarray of nums, or return -1 if no special subarray exists.
//
// Example:
// Input: nums = [1,2,3], k = 2
//
// Output: 1
//
// Explanation:
//
// The subarray [3] has OR value of 3. Hence, we return 1.
//
// Note that [2] is also a special subarray.
//
// Constraints:
// 1 <= nums.length <= 50
// 	0 <= nums[i] <= 50
// 	0 <= k < 64
//

class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) {
        int n = nums.size();
        int minLength = INT_MAX;

        for (int start = 0; start < n; ++start) {
            int currentOR = 0;
            for (int end = start; end < n; ++end) {
                currentOR |= nums[end];
                if (currentOR >= k) {
                    minLength = min(minLength, end - start + 1);
                    break; // No need to check longer subarrays starting from 'start'
                }
            }
        }

        return (minLength == INT_MAX) ? -1 : minLength;         
    }
};
