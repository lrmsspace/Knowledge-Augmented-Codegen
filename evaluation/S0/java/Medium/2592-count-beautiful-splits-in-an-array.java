// Source: https://leetcode.com/problems/count-beautiful-splits-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums.
//
// A split of an array nums is beautiful if:
//
//
// 	The array nums is split into three subarrays: nums1, nums2, and nums3, such that nums can be formed by concatenating nums1, nums2, and nums3 in that order.
// 	The subarray nums1 is a prefix of nums2 OR nums2 is a prefix of nums3.
//
//
// Return the number of ways you can make this split.
//
// Example:
// Input: nums = [1,1,2,1]
//
// Output: 2
//
// Explanation:
//
// The beautiful splits are:
//
//
// 	A split with nums1 = [1], nums2 = [1,2], nums3 = [1].
// 	A split with nums1 = [1], nums2 = [1], nums3 = [2,1].
//
// Constraints:
// 1 <= nums.length <= 5000
// 	0 <= nums[i] <= 50
//

class Solution {
    public int beautifulSplits(int[] nums) {
        int n = nums.length;
        int[] prefixUnique = new int[n];
        int[] suffixUnique = new int[n];

        boolean[] seen = new boolean[51];
        int uniqueCount = 0;

        // Calculate prefix unique counts
        for (int i = 0; i < n; i++) {
            if (!seen[nums[i]]) {
                seen[nums[i]] = true;
                uniqueCount++;
            }
            prefixUnique[i] = uniqueCount;
        }

        // Reset for suffix calculation
        seen = new boolean[51];
        uniqueCount = 0;

        // Calculate suffix unique counts
        for (int i = n - 1; i >= 0; i--) {
            if (!seen[nums[i]]) {
                seen[nums[i]] = true;
                uniqueCount++;
            }
            suffixUnique[i] = uniqueCount;
        }

        int beautifulSplitsCount = 0;

        // Count beautiful splits
        for (int i = 0; i < n - 1; i++) {
            if (prefixUnique[i] >= suffixUnique[i + 1]) {
                beautifulSplitsCount++;
            }
        }

        return beautifulSplitsCount;            
    }
}
