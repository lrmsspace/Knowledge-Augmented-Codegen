// Source: https://leetcode.com/problems/subarrays-distinct-element-sum-of-squares-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums.
//
// The distinct count of a subarray of nums is defined as:
//
//
// 	Let nums[i..j] be a subarray of nums consisting of all the indices from i to j such that 0 <= i <= j < nums.length. Then the number of distinct values in nums[i..j] is called the distinct count of nums[i..j].
//
//
// Return the sum of the squares of distinct counts of all subarrays of nums.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,1]
// Output: 15
// Explanation: Six possible subarrays are:
// [1]: 1 distinct value
// [2]: 1 distinct value
// [1]: 1 distinct value
// [1,2]: 2 distinct values
// [2,1]: 2 distinct values
// [1,2,1]: 2 distinct values
// The sum of the squares of the distinct counts in all subarrays is equal to 12 + 12 + 12 + 22 + 22 + 22 = 15.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

class Solution {
    public int sumCounts(int[] nums) {
        int mod = (int)1e9 + 7;
        int n = nums.length;

        long result = 0;
        long currentSum = 0;

        int[] lastOccurrence = new int[100001];
        for (int i = 0; i < lastOccurrence.length; i++) {
            lastOccurrence[i] = -1;
        }

        for (int i = 0; i < n; i++) {
            int num = nums[i];
            int lastIndex = lastOccurrence[num];

            long totalSubarraysEndingHere = (long)(i + 1);
            long newDistinctSubarrays = (long)(i - lastIndex);

            long prevContribution = (totalSubarraysEndingHere - newDistinctSubarrays) * (totalSubarraysEndingHere - newDistinctSubarrays + 1) % mod * (2 * (totalSubarraysEndingHere - newDistinctSubarrays) + 1) % mod * modInverse(6, mod) % mod;
            long newContribution = totalSubarraysEndingHere * (totalSubarraysEndingHere + 1) % mod * (2 * totalSubarraysEndingHere + 1) % mod * modInverse(6, mod) % mod;

            currentSum = (currentSum - prevContribution + newContribution + mod) % mod;
            result = (result + currentSum) % mod;

            lastOccurrence[num] = i;
        }

        return (int)result;         
    }
}
