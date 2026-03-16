// Source: https://leetcode.com/problems/adjacent-increasing-subarrays-detection-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of n integers, your task is to find the maximum value of k for which there exist two adjacent subarrays of length k each, such that both subarrays are strictly increasing. Specifically, check if there are two subarrays of length k starting at indices a and b (a < b), where:
//
//
// 	Both subarrays nums[a..a + k - 1] and nums[b..b + k - 1] are strictly increasing.
// 	The subarrays must be adjacent, meaning b = a + k.
//
//
// Return the maximum possible value of k.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [2,5,7,8,9,2,3,4,3,1]
//
// Output: 3
//
// Explanation:
//
//
// 	The subarray starting at index 2 is [7, 8, 9], which is strictly increasing.
// 	The subarray starting at index 5 is [2, 3, 4], which is also strictly increasing.
// 	These two subarrays are adjacent, and 3 is the maximum possible value of k for which two such adjacent strictly increasing subarrays exist.
//
// Constraints:
// 2 <= nums.length <= 2 * 105
// 	-109 <= nums[i] <= 109
//

class Solution {
public:
    int maxIncreasingSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> incLen(n, 1);

        // Calculate lengths of increasing subarrays ending at each index
        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[i - 1]) {
                incLen[i] = incLen[i - 1] + 1;
            }
        }

        int maxK = 0;

        // Check for adjacent increasing subarrays
        for (int i = 1; i < n; ++i) {
            int k = min(incLen[i - 1], incLen[i]);
            maxK = max(maxK, k);
        }

        return maxK;            
    }
};
