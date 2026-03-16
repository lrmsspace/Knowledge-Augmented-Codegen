// Source: https://leetcode.com/problems/harshad-number/   |   Difficulty: Easy
//
// Problem Description:
// An integer divisible by the sum of its digits is said to be a Harshad number. You are given an integer x. Return the sum of the digits of x if x is a Harshad number, otherwise, return -1.
//
// Example:
// Input: x = 18
//
// Output: 9
//
// Explanation:
//
// The sum of digits of x is 9. 18 is divisible by 9. So 18 is a Harshad number and the answer is 9.
//
// Constraints:
// 1 <= x <= 100
//

class Solution {
    public int sumOfTheDigitsOfHarshadNumber(int x) {
        int sum = 0;
        int temp = x;

        while (temp > 0) {
            sum += temp % 10;
            temp /= 10;
        }

        if (x % sum == 0) {
            return sum;
        } else {
            return -1;
        }           
    }
}
