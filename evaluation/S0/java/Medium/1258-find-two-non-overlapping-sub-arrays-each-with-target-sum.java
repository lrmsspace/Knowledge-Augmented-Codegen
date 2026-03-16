// Source: https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers arr and an integer target.
//
// You have to find two non-overlapping sub-arrays of arr each with a sum equal target. There can be multiple answers so you have to find an answer where the sum of the lengths of the two sub-arrays is minimum.
//
// Return the minimum sum of the lengths of the two required sub-arrays, or return -1 if you cannot find such two sub-arrays.
//
// Example:
// Input: arr = [3,2,2,4,3], target = 3
// Output: 2
// Explanation: Only two sub-arrays have sum = 3 ([3] and [3]). The sum of their lengths is 2.
//
// Constraints:
// 1 <= arr.length <= 105
// 	1 <= arr[i] <= 1000
// 	1 <= target <= 108
//

class Solution {
    public int minSumOfLengths(int[] arr, int target) {
        int n = arr.length;
        int[] dp = new int[n];
        Arrays.fill(dp, Integer.MAX_VALUE);
        int sum = 0, left = 0, minLen = Integer.MAX_VALUE, result = Integer.MAX_VALUE;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            while (sum > target) {
                sum -= arr[left++];
            }

            if (sum == target) {
                int currLen = right - left + 1;

                if (left > 0 && dp[left - 1] != Integer.MAX_VALUE) {
                    result = Math.min(result, currLen + dp[left - 1]);
                }

                minLen = Math.min(minLen, currLen);
            }

            dp[right] = minLen;
        }

        return result == Integer.MAX_VALUE ? -1 : result;           
    }
}
