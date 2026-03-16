// Source: https://leetcode.com/problems/sum-of-subarray-ranges/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. The range of a subarray of nums is the difference between the largest and smallest element in the subarray.
//
// Return the sum of all subarray ranges of nums.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,3]
// Output: 4
// Explanation: The 6 subarrays of nums are the following:
// [1], range = largest - smallest = 1 - 1 = 0 
// [2], range = 2 - 2 = 0
// [3], range = 3 - 3 = 0
// [1,2], range = 2 - 1 = 1
// [2,3], range = 3 - 2 = 1
// [1,2,3], range = 3 - 1 = 2
// So the sum of all ranges is 0 + 0 + 0 + 1 + 1 + 2 = 4.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	-109 <= nums[i] <= 109
//
//
//  
// Follow-up: Could you find a solution with O(n) time complexity?
//

class Solution {
    public long subArrayRanges(int[] nums) {
        int n = nums.length;
        long totalMax = 0, totalMin = 0;

        // Calculate total contribution as maximum
        for (int i = 0; i < n; i++) {
            int left = i - 1, right = i + 1;

            while (left >= 0 && nums[left] < nums[i]) {
                left--;
            }
            while (right < n && nums[right] <= nums[i]) {
                right++;
            }

            long count = (long) (i - left) * (right - i);
            totalMax += count * nums[i];
        }

        // Calculate total contribution as minimum
        for (int i = 0; i < n; i++) {
            int left = i - 1, right = i + 1;

            while (left >= 0 && nums[left] > nums[i]) {
                left--;
            }
            while (right < n && nums[right] >= nums[i]) {
                right++;
            }

            long count = (long) (i - left) * (right - i);
            totalMin += count * nums[i];
        }

        return totalMax - totalMin;         
    }
}
