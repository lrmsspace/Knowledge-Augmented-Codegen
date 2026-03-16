// Source: https://leetcode.com/problems/sum-of-subsequence-widths/   |   Difficulty: Hard
//
// Problem Description:
// The width of a sequence is the difference between the maximum and minimum elements in the sequence.
//
// Given an array of integers nums, return the sum of the widths of all the non-empty subsequences of nums. Since the answer may be very large, return it modulo 109 + 7.
//
// A subsequence is a sequence that can be derived from an array by deleting some or no elements without changing the order of the remaining elements. For example, [3,6,2,7] is a subsequence of the array [0,3,1,6,2,2,7].
//
// Example:
// Input: nums = [2,1,3]
// Output: 6
// Explanation: The subsequences are [1], [2], [3], [2,1], [2,3], [1,3], [2,1,3].
// The corresponding widths are 0, 0, 0, 1, 1, 2, 2.
// The sum of these widths is 6.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

class Solution {
    public int sumSubseqWidths(int[] nums) {
        final int MOD = 1_000_000_007;
        int n = nums.length;
        Arrays.sort(nums);

        long result = 0;
        long[] powerOfTwo = new long[n];
        powerOfTwo[0] = 1;

        for (int i = 1; i < n; i++) {
            powerOfTwo[i] = (powerOfTwo[i - 1] * 2) % MOD;
        }

        for (int i = 0; i < n; i++) {
            long maxContribution = powerOfTwo[i];
            long minContribution = powerOfTwo[n - 1 - i];
            result = (result + (nums[i] * (maxContribution - minContribution)) % MOD) % MOD;
        }

        return (int) result;            
    }
}
