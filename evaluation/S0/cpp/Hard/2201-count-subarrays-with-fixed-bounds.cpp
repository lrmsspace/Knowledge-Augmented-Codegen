// Source: https://leetcode.com/problems/count-subarrays-with-fixed-bounds/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers minK and maxK.
//
// A fixed-bound subarray of nums is a subarray that satisfies the following conditions:
//
//
// 	The minimum value in the subarray is equal to minK.
// 	The maximum value in the subarray is equal to maxK.
//
//
// Return the number of fixed-bound subarrays.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [1,3,5,2,7,5], minK = 1, maxK = 5
// Output: 2
// Explanation: The fixed-bound subarrays are [1,3,5] and [1,3,5,2].
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i], minK, maxK <= 106
//

class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        long long result = 0;
        int n = nums.size();
        int lastMin = -1, lastMax = -1, leftBound = -1;
        
        for (int i = 0; i < n; i++) {
            if (nums[i] < minK || nums[i] > maxK) {
                leftBound = i;
            }
            if (nums[i] == minK) {
                lastMin = i;
            }
            if (nums[i] == maxK) {
                lastMax = i;
            }
            int validStart = min(lastMin, lastMax);
            if (validStart > leftBound) {
                result += validStart - leftBound;
            }
        }
        
        return result;          
    }
};
