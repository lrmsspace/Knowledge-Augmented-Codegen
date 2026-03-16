// Source: https://leetcode.com/problems/kth-smallest-number-in-multiplication-table/   |   Difficulty: Hard
//
// Problem Description:
// Nearly everyone has used the Multiplication Table. The multiplication table of size m x n is an integer matrix mat where mat[i][j] == i * j (1-indexed).
//
// Given three integers m, n, and k, return the kth smallest element in the m x n multiplication table.
//
// Example:
// Input: m = 3, n = 3, k = 5
// Output: 3
// Explanation: The 5th smallest number is 3.
//
// Constraints:
// 1 <= m, n <= 3 * 104
// 	1 <= k <= m * n
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int findKthNumber(int m, int n, int k) {
        int low = 1, high = m * n;
        while (low < high) {
            int mid = low + (high - low) / 2;
            if (countLessEqual(mid, m, n) < k) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low;         
    }
}
