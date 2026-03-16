// Source: https://leetcode.com/problems/detect-pattern-of-length-m-repeated-k-or-more-times/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of positive integers arr, find a pattern of length m that is repeated k or more times.
//
// A pattern is a subarray (consecutive sub-sequence) that consists of one or more values, repeated multiple times consecutively without overlapping. A pattern is defined by its length and the number of repetitions.
//
// Return true if there exists a pattern of length m that is repeated k or more times, otherwise return false.
//
// Example:
// Input: arr = [1,2,4,4,4,4], m = 1, k = 3
// Output: true
// Explanation: The pattern (4) of length 1 is repeated 4 consecutive times. Notice that pattern can be repeated k or more times but not less.
//
// Constraints:
// 2 <= arr.length <= 100
// 	1 <= arr[i] <= 100
// 	1 <= m <= 100
// 	2 <= k <= 100
//

class Solution {
    public boolean containsPattern(int[] arr, int m, int k) {
        int n = arr.length;
        for (int i = 0; i <= n - m * k; i++) {
            boolean match = true;
            for (int j = 1; j < k; j++) {
                for (int p = 0; p < m; p++) {
                    if (arr[i + p] != arr[i + j * m + p]) {
                        match = false;
                        break;
                    }
                }
                if (!match) {
                    break;
                }
            }
            if (match) {
                return true;
            }
        }
        return false;           
    }
}
