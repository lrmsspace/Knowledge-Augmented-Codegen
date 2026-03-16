// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-x-and-y-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integers x and y.
//
// In one operation, you can do one of the four following operations:
//
//
// 	Divide x by 11 if x is a multiple of 11.
// 	Divide x by 5 if x is a multiple of 5.
// 	Decrement x by 1.
// 	Increment x by 1.
//
//
// Return the minimum number of operations required to make  x and y equal.
//
// Example:
// Input: x = 26, y = 1
// Output: 3
// Explanation: We can make 26 equal to 1 by applying the following operations: 
// 1. Decrement x by 1
// 2. Divide x by 5
// 3. Divide x by 5
// It can be shown that 3 is the minimum number of operations required to make 26 equal to 1.
//
// Constraints:
// 1 <= x, y <= 104
//

class Solution {
    public int minimumOperationsToMakeEqual(int x, int y) {
        int operations = 0;

        while (x != y) {
            if (x < y) {
                operations += (y - x);
                break;
            } else if (x % 11 == 0 && x / 11 >= y) {
                x /= 11;
                operations++;
            } else if (x % 5 == 0 && x / 5 >= y) {
                x /= 5;
                operations++;
            } else {
                x--;
                operations++;
            }
        }

        return operations;          
    }
}
