// Source: https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return any array containing n unique integers such that they add up to 0.
//
// Example:
// Input: n = 5
// Output: [-7,-1,1,3,4]
// Explanation: These arrays also are accepted [-5,-1,1,2,3] , [-3,-1,2,-2,4].
//
// Constraints:
// 1 <= n <= 1000
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
    public int[] sumZero(int n) {
        int[] result = new int[n];
        for (int i = 0; i < n; i++) {
            result[i] = i - n / 2;
        }
        return result;          
    }
}
