// Source: https://leetcode.com/problems/find-the-count-of-monotonic-pairs-i/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums of length n.
//
// We call a pair of non-negative integer arrays (arr1, arr2) monotonic if:
//
//
// 	The lengths of both arrays are n.
// 	arr1 is monotonically non-decreasing, in other words, arr1[0] <= arr1[1] <= ... <= arr1[n - 1].
// 	arr2 is monotonically non-increasing, in other words, arr2[0] >= arr2[1] >= ... >= arr2[n - 1].
// 	arr1[i] + arr2[i] == nums[i] for all 0 <= i <= n - 1.
//
//
// Return the count of monotonic pairs.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [2,3,2]
//
// Output: 4
//
// Explanation:
//
// The good pairs are:
//
//
// 	([0, 1, 1], [2, 2, 1])
// 	([0, 1, 2], [2, 2, 0])
// 	([0, 2, 2], [2, 1, 0])
// 	([1, 2, 2], [1, 1, 0])
//
// Constraints:
// 1 <= n == nums.length <= 2000
// 	1 <= nums[i] <= 50
//

class Solution {
    public int countOfPairs(int[] nums) {
        int mod = (int)1e9 + 7;
        int n = nums.length;
        int maxNum = 50;

        // dpInc[i][j] = number of ways to form a non-decreasing array of length i with last element j
        long[][] dpInc = new long[n + 1][maxNum + 1];
        // dpDec[i][j] = number of ways to form a non-increasing array of length i with last element j
        long[][] dpDec = new long[n + 1][maxNum + 1];

        // Base case: one way to form an empty array
        for (int j = 0; j <= maxNum; j++) {
            dpInc[0][j] = 1;
            dpDec[0][j] = 1;
        }

        // Fill dpInc
        for (int i = 1; i <= n; i++) {
            long sum = 0;
            for (int j = 0; j <= maxNum; j++) {
                sum = (sum + dpInc[i - 1][j]) % mod;
                dpInc[i][j] = sum;
            }
        }

        // Fill dpDec
        for (int i = 1; i <= n; i++) {
            long sum = 0;
            for (int j = maxNum; j >= 0; j--) {
                sum = (sum + dpDec[i - 1][j]) % mod;
                dpDec[i][j] = sum;
            }
        }

        // Calculate the result
        long result = 1;
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            long waysInc = dpInc[i + 1][num];
            long waysDec = dpDec[n - i][num];
            result = (result * ((waysInc * waysDec) % mod)) % mod;
        }

        return (int)result;         
    }
}
