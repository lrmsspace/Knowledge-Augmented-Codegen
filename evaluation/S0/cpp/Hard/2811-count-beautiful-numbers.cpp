// Source: https://leetcode.com/problems/count-beautiful-numbers/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers, l and r. A positive integer is called beautiful if the product of its digits is divisible by the sum of its digits.
//
// Return the count of beautiful numbers between l and r, inclusive.
//
// Example:
// Input: l = 10, r = 20
//
// Output: 2
//
// Explanation:
//
// The beautiful numbers in the range are 10 and 20.
//
// Constraints:
// 1 <= l <= r < 109
//

class Solution {
public:
    int beautifulNumbers(int l, int r) {
        return countBeautiful(r) - countBeautiful(l - 1);           
    }
};
