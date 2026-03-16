// Source: https://leetcode.com/problems/maximum-sum-of-almost-unique-subarray/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and two positive integers m and k.
//
// Return the maximum sum out of all almost unique subarrays of length k of nums. If no such subarray exists, return 0.
//
// A subarray of nums is almost unique if it contains at least m distinct elements.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [2,6,7,3,1,7], m = 3, k = 4
// Output: 18
// Explanation: There are 3 almost unique subarrays of size k = 4. These subarrays are [2, 6, 7, 3], [6, 7, 3, 1], and [7, 3, 1, 7]. Among these subarrays, the one with the maximum sum is [2, 6, 7, 3] which has a sum of 18.
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= m <= k <= nums.length
// 	1 <= nums[i] <= 109
//

class Solution {
    public long maxSum(List<Integer> nums, int m, int k) {
        Map<Integer, Integer> freqMap = new HashMap<>();
        long currentSum = 0;
        long maxSum = 0;

        for (int i = 0; i < nums.size(); i++) {
            int numToAdd = nums.get(i);
            freqMap.put(numToAdd, freqMap.getOrDefault(numToAdd, 0) + 1);
            currentSum += numToAdd;

            if (i >= k) {
                int numToRemove = nums.get(i - k);
                freqMap.put(numToRemove, freqMap.get(numToRemove) - 1);
                if (freqMap.get(numToRemove) == 0) {
                    freqMap.remove(numToRemove);
                }
                currentSum -= numToRemove;
            }

            if (i >= k - 1 && freqMap.size() >= m) {
                maxSum = Math.max(maxSum, currentSum);
            }
        }

        return maxSum;          
    }
}
