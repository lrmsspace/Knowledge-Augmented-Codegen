// Source: https://leetcode.com/problems/k-radius-subarray-averages/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums of n integers, and an integer k.
//
// The k-radius average for a subarray of nums centered at some index i with the radius k is the average of all elements in nums between the indices i - k and i + k (inclusive). If there are less than k elements before or after the index i, then the k-radius average is -1.
//
// Build and return an array avgs of length n where avgs[i] is the k-radius average for the subarray centered at index i.
//
// The average of x elements is the sum of the x elements divided by x, using integer division. The integer division truncates toward zero, which means losing its fractional part.
//
//
// 	For example, the average of four elements 2, 3, 1, and 5 is (2 + 3 + 1 + 5) / 4 = 11 / 4 = 2.75, which truncates to 2.
//
// Example:
// Input: nums = [7,4,3,9,1,8,5,2,6], k = 3
// Output: [-1,-1,-1,5,4,4,-1,-1,-1]
// Explanation:
// - avg[0], avg[1], and avg[2] are -1 because there are less than k elements before each index.
// - The sum of the subarray centered at index 3 with radius 3 is: 7 + 4 + 3 + 9 + 1 + 8 + 5 = 37.
//   Using integer division, avg[3] = 37 / 7 = 5.
// - For the subarray centered at index 4, avg[4] = (4 + 3 + 9 + 1 + 8 + 5 + 2) / 7 = 4.
// - For the subarray centered at index 5, avg[5] = (3 + 9 + 1 + 8 + 5 + 2 + 6) / 7 = 4.
// - avg[6], avg[7], and avg[8] are -1 because there are less than k elements after each index.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	0 <= nums[i], k <= 105
//

class Solution {
    public int[] getAverages(int[] nums, int k) {
        int n = nums.length;
        int[] avgs = new int[n];
        long windowSum = 0;
        int windowSize = 2 * k + 1;

        // Initialize all averages to -1
        for (int i = 0; i < n; i++) {
            avgs[i] = -1;
        }

        // Edge case: if k is 0, return the original array
        if (k == 0) {
            return nums;
        }

        // Calculate the sum of the first window
        for (int i = 0; i < Math.min(windowSize, n); i++) {
            windowSum += nums[i];
        }

        // Slide the window across the array
        for (int i = k; i < n - k; i++) {
            if (i > k) {
                windowSum += nums[i + k]; // Add the next element in the window
                windowSum -= nums[i - k - 1]; // Remove the element that is no longer in the window
            }
            avgs[i] = (int)(windowSum / windowSize); // Calculate average using integer division
        }

        return avgs;            
    }
}
