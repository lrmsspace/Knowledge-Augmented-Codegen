// Source: https://leetcode.com/problems/ways-to-split-array-into-three-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// A split of an integer array is good if:
//
//
// 	The array is split into three non-empty contiguous subarrays - named left, mid, right respectively from left to right.
// 	The sum of the elements in left is less than or equal to the sum of the elements in mid, and the sum of the elements in mid is less than or equal to the sum of the elements in right.
//
//
// Given nums, an array of non-negative integers, return the number of good ways to split nums. As the number may be too large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,1,1]
// Output: 1
// Explanation: The only good way to split nums is [1] [1] [1].
//
// Constraints:
// 3 <= nums.length <= 105
// 	0 <= nums[i] <= 104
//

class Solution {
    public int waysToSplit(int[] nums) {
        int mod = (int)1e9 + 7;
        int n = nums.length;
        int[] prefixSum = new int[n];
        prefixSum[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefixSum[i] = prefixSum[i - 1] + nums[i];
        }

        int totalWays = 0;

        for (int i = 0; i < n - 2; i++) {
            int leftSum = prefixSum[i];

            // Binary search for the minimum index j
            int low = i + 1, high = n - 2;
            int minJ = -1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (prefixSum[mid] >= 2 * leftSum) {
                    minJ = mid;
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }

            // Binary search for the maximum index j
            low = i + 1;
            high = n - 2;
            int maxJ = -1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (prefixSum[mid] <= (prefixSum[n - 1] + leftSum) / 2) {
                    maxJ = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }

            if (minJ != -1 && maxJ != -1 && maxJ >= minJ) {
                totalWays = (totalWays + (maxJ - minJ + 1)) % mod;
            }
        }

        return totalWays;           
    }
}
