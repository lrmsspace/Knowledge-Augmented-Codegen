// Source: https://leetcode.com/problems/maximum-width-ramp/   |   Difficulty: Medium
//
// Problem Description:
// A ramp in an integer array nums is a pair (i, j) for which i < j and nums[i] <= nums[j]. The width of such a ramp is j - i.
//
// Given an integer array nums, return the maximum width of a ramp in nums. If there is no ramp in nums, return 0.
//
// Example:
// Input: nums = [6,0,8,2,1,5]
// Output: 4
// Explanation: The maximum width ramp is achieved at (i, j) = (1, 5): nums[1] = 0 and nums[5] = 5.
//
// Constraints:
// 2 <= nums.length <= 5 * 104
// 	0 <= nums[i] <= 5 * 104
//

class Solution {
    public int maxWidthRamp(int[] nums) {
        int n = nums.length;
        int maxWidth = 0;

        // Create an array of indices and sort it based on the values in nums
        Integer[] indices = new Integer[n];
        for (int i = 0; i < n; i++) {
            indices[i] = i;
        }
        Arrays.sort(indices, (a, b) -> Integer.compare(nums[a], nums[b]));

        int minIndex = n; // Initialize to a large value

        // Traverse the sorted indices to find the maximum width ramp
        for (int index : indices) {
            if (index < minIndex) {
                minIndex = index; // Update the minimum index found so far
            } else {
                maxWidth = Math.max(maxWidth, index - minIndex); // Calculate width and update maxWidth
            }
        }

        return maxWidth;            
    }
}
