// Source: https://leetcode.com/problems/find-the-pivot-integer/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer n, find the pivot integer x such that:
//
//
// 	The sum of all elements between 1 and x inclusively equals the sum of all elements between x and n inclusively.
//
//
// Return the pivot integer x. If no such integer exists, return -1. It is guaranteed that there will be at most one pivot index for the given input.
//
// Example:
// Input: n = 8
// Output: 6
// Explanation: 6 is the pivot integer since: 1 + 2 + 3 + 4 + 5 + 6 = 6 + 7 + 8 = 21.
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
    public int pivotInteger(int n) {
        int sum = n * (n + 1) / 2; // Sum of first n integers
        int leftSum = 0;

        for (int x = 1; x <= n; x++) {
            leftSum += x; // Update left sum to include current x
            int rightSum = sum - leftSum + x; // Calculate right sum by removing left sum and adding back x

            if (leftSum == rightSum) {
                return x; // Found the pivot integer
            }
        }

        return -1; // No pivot integer found            
    }
}
