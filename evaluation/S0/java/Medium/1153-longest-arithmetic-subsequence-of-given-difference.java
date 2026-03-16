// Source: https://leetcode.com/problems/longest-arithmetic-subsequence-of-given-difference/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr and an integer difference, return the length of the longest subsequence in arr which is an arithmetic sequence such that the difference between adjacent elements in the subsequence equals difference.
//
// A subsequence is a sequence that can be derived from arr by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: arr = [1,2,3,4], difference = 1
// Output: 4
// Explanation: The longest arithmetic subsequence is [1,2,3,4].
//
// Constraints:
// 1 <= arr.length <= 105
// 	-104 <= arr[i], difference <= 104
//

class Solution {
    public int longestSubsequence(int[] arr, int difference) {
        Map<Integer, Integer> dp = new HashMap<>();
        int maxLength = 0;

        for (int num : arr) {
            int prevNum = num - difference;
            int currLength = dp.getOrDefault(prevNum, 0) + 1;
            dp.put(num, currLength);
            maxLength = Math.max(maxLength, currLength);
        }

        return maxLength;           
    }
}
