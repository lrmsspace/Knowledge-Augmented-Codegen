// Source: https://leetcode.com/problems/integer-replacement/   |   Difficulty: Medium
//
// Problem Description:
// Given a positive integer n, you can apply one of the following operations:
//
//
// 	If n is even, replace n with n / 2.
// 	If n is odd, replace n with either n + 1 or n - 1.
//
//
// Return the minimum number of operations needed for n to become 1.
//
// Example:
// Input: n = 8
// Output: 3
// Explanation: 8 -> 4 -> 2 -> 1
//
// Constraints:
// 1 <= n <= 231 - 1
//

class Solution {
public:
    int integerReplacement(int n) {
        long long num = n; // Use long long to avoid overflow
        int steps = 0;

        while (num != 1) {
            if ((num & 1) == 0) {
                num >>= 1; // n is even
            } else {
                if (num == 3 || ((num >> 1) & 1) == 0) {
                    num -= 1; // n is odd and either 3 or ends with 01 in binary
                } else {
                    num += 1; // n is odd and ends with 11 in binary
                }
            }
            steps++;
        }

        return steps;           
    }
};
