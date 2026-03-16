// Source: https://leetcode.com/problems/find-the-median-of-the-uniqueness-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. The uniqueness array of nums is the sorted array that contains the number of distinct elements of all the subarrays of nums. In other words, it is a sorted array consisting of distinct(nums[i..j]), for all 0 <= i <= j < nums.length.
//
// Here, distinct(nums[i..j]) denotes the number of distinct elements in the subarray that starts at index i and ends at index j.
//
// Return the median of the uniqueness array of nums.
//
// Note that the median of an array is defined as the middle element of the array when it is sorted in non-decreasing order. If there are two choices for a median, the smaller of the two values is taken.
//
// Example:
// Input: nums = [1,2,3]
//
// Output: 1
//
// Explanation:
//
// The uniqueness array of nums is [distinct(nums[0..0]), distinct(nums[1..1]), distinct(nums[2..2]), distinct(nums[0..1]), distinct(nums[1..2]), distinct(nums[0..2])] which is equal to [1, 1, 1, 2, 2, 3]. The uniqueness array has a median of 1. Therefore, the answer is 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

class Solution {
    public int medianOfUniquenessArray(int[] nums) {
        int n = nums.length;
        int maxNum = 0;
        for (int num : nums) {
            maxNum = Math.max(maxNum, num);
        }

        int[] lastSeen = new int[maxNum + 1];
        Arrays.fill(lastSeen, -1);

        long totalSubarrays = (long) n * (n + 1) / 2;
        long target = (totalSubarrays + 1) / 2;

        long count = 0;
        int left = 1, right = n;

        while (left < right) {
            int mid = left + (right - left) / 2;
            count = countSubarraysWithAtMostKDistinct(nums, mid, lastSeen);

            if (count < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        return left;            
    }
}
