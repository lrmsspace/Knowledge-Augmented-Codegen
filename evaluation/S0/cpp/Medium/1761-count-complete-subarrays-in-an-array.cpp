// Source: https://leetcode.com/problems/count-complete-subarrays-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers.
//
// We call a subarray of an array complete if the following condition is satisfied:
//
//
// 	The number of distinct elements in the subarray is equal to the number of distinct elements in the whole array.
//
//
// Return the number of complete subarrays.
//
// A subarray is a contiguous non-empty part of an array.
//
// Example:
// Input: nums = [1,3,1,2,2]
// Output: 4
// Explanation: The complete subarrays are the following: [1,3,1,2], [1,3,1,2,2], [3,1,2] and [3,1,2,2].
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 2000
//

class Solution {
public:
    int countCompleteSubarrays(vector<int>& nums) {
        unordered_set<int> distinctElements(nums.begin(), nums.end());
        int totalDistinct = distinctElements.size();
        int n = nums.size();
        int completeSubarrayCount = 0;

        for (int start = 0; start < n; ++start) {
            unordered_set<int> currentDistinct;
            for (int end = start; end < n; ++end) {
                currentDistinct.insert(nums[end]);
                if (currentDistinct.size() == totalDistinct) {
                    completeSubarrayCount += (n - end);
                    break; // No need to check further, as all longer subarrays will also be complete
                }
            }
        }

        return completeSubarrayCount;           
    }
};
