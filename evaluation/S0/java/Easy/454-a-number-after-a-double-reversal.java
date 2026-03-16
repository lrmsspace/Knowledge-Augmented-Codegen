// Source: https://leetcode.com/problems/a-number-after-a-double-reversal/   |   Difficulty: Easy
//
// Problem Description:
// Reversing an integer means to reverse all its digits.
//
//
// 	For example, reversing 2021 gives 1202. Reversing 12300 gives 321 as the leading zeros are not retained.
//
//
// Given an integer num, reverse num to get reversed1, then reverse reversed1 to get reversed2. Return true if reversed2 equals num. Otherwise return false.
//
// Example:
// Input: num = 526
// Output: true
// Explanation: Reverse num to get 625, then reverse 625 to get 526, which equals num.
//
// Constraints:
// 0 <= num <= 106
//

class Solution {
    public boolean isSameAfterReversals(int num) {
        // A number is the same after double reversal if it is 0 or does not end with 0
        return num == 0 || num % 10 != 0;           
    }
}
