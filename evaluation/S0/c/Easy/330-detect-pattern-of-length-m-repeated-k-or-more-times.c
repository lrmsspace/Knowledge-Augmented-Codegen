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

bool containsPattern(int* arr, int arrSize, int m, int k) {
    int count = 0;
    for (int i = 0; i <= arrSize - m; i++) {
        count = 0;
        for (int j = i + m; j <= arrSize - m; j += m) {
            int match = 1;
            for (int p = 0; p < m; p++) {
                if (arr[i + p] != arr[j + p]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                count++;
                if (count == k - 1) {
                    return true;
                }
            } else {
                break;
            }
        }
    }
    return false;       
}
