// Source: https://leetcode.com/problems/minimum-operations-to-make-array-equal/   |   Difficulty: Medium
//
// Problem Description:
// You have an array arr of length n where arr[i] = (2 * i) + 1 for all valid values of i (i.e., 0 <= i < n).
//
// In one operation, you can select two indices x and y where 0 <= x, y < n and subtract 1 from arr[x] and add 1 to arr[y] (i.e., perform arr[x] -=1 and arr[y] += 1). The goal is to make all the elements of the array equal. It is guaranteed that all the elements of the array can be made equal using some operations.
//
// Given an integer n, the length of the array, return the minimum number of operations needed to make all the elements of arr equal.
//
// Example:
// Input: n = 3
// Output: 2
// Explanation: arr = [1, 3, 5]
// First operation choose x = 2 and y = 0, this leads arr to be [2, 3, 4]
// In the second operation choose x = 2 and y = 0 again, thus arr = [3, 3, 3].
//
// Constraints:
// 1 <= n <= 104
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
    public int minOperations(int n) {
        int operations = 0;
        int left = 0;
        int right = n - 1;
        int target = n; // Since arr[i] = (2 * i) + 1, the average (target) will always be n for any n.

        while (left < right) {
            operations += target - ((2 * left) + 1);
            left++;
            right--;
        }

        return operations;          
    }
}
