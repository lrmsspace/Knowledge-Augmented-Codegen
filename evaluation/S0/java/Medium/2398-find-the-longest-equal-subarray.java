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
    public int longestEqualSubarray(List<Integer> nums, int k) {
        Map<Integer, List<Integer>> indicesMap = new HashMap<>();
        int n = nums.size();

        // Collect indices for each number
        for (int i = 0; i < n; i++) {
            indicesMap.computeIfAbsent(nums.get(i), key -> new ArrayList<>()).add(i);
        }

        int maxLength = 0;

        // Process each unique number's indices
        for (List<Integer> indices : indicesMap.values()) {
            int left = 0;

            for (int right = 0; right < indices.size(); right++) {
                // Calculate the number of deletions needed
                while (indices.get(right) - indices.get(left) - (right - left) > k) {
                    left++;
                }
                // Update maximum length found
                maxLength = Math.max(maxLength, right - left + 1);
            }
        }

        return maxLength;           
    }
}
