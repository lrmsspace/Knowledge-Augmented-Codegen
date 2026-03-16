// Source: https://leetcode.com/problems/count-the-digits-that-divide-a-number/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer num, return the number of digits in num that divide num.
//
// An integer val divides nums if nums % val == 0.
//
// Example:
// Input: num = 7
// Output: 1
// Explanation: 7 divides itself, hence the answer is 1.
//
// Constraints:
// 1 <= num <= 109
// 	num does not contain 0 as one of its digits.
//

class Solution {
    public int countDigits(int num) {
        int count = 0;
        int originalNum = num;

        while (num > 0) {
            int digit = num % 10;
            if (digit != 0 && originalNum % digit == 0) {
                count++;
            }
            num /= 10;
        }

        return count;           
    }
}
