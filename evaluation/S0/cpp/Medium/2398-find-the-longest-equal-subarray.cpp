// Source: https://leetcode.com/problems/find-the-longest-equal-subarray/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer k.
//
// A subarray is called equal if all of its elements are equal. Note that the empty subarray is an equal subarray.
//
// Return the length of the longest possible equal subarray after deleting at most k elements from nums.
//
// A subarray is a contiguous, possibly empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,3,2,3,1,3], k = 3
// Output: 3
// Explanation: It's optimal to delete the elements at index 2 and index 4.
// After deleting them, nums becomes equal to [1, 3, 3, 3].
// The longest equal subarray starts at i = 1 and ends at j = 3 with length equal to 3.
// It can be proven that no longer equal subarrays can be created.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= nums.length
// 	0 <= k <= nums.length
//

class Solution {
public:
    int longestEqualSubarray(vector<int>& nums, int k) {
        unordered_map<int, int> countMap;
        int left = 0, maxCount = 0, result = 0;

        for (int right = 0; right < nums.size(); ++right) {
            countMap[nums[right]]++;
            maxCount = max(maxCount, countMap[nums[right]]);

            while ((right - left + 1) - maxCount > k) {
                countMap[nums[left]]--;
                left++;
            }

            result = max(result, right - left + 1);
        }

        return result;          
    }
};
