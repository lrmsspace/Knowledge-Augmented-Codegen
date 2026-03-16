// Source: https://leetcode.com/problems/smallest-good-base/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n represented as a string, return the smallest good base of n.
//
// We call k >= 2 a good base of n, if all digits of n base k are 1's.
//
// Example:
// Input: n = "13"
// Output: "3"
// Explanation: 13 base 3 is 111.
//
// Constraints:
// n is an integer in the range [3, 1018].
// 	n does not contain any leading zeros.
//

class Solution {
    public String smallestGoodBase(String n) {
        long num = Long.parseLong(n);
        for (int m = 63; m >= 2; m--) {
            long k = getBase(num, m);
            if (k != -1) {
                return String.valueOf(k);
            }
        }
        return String.valueOf(num - 1);         
    }
}
