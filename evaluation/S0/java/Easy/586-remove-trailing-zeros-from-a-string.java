// Source: https://leetcode.com/problems/remove-trailing-zeros-from-a-string/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer num represented as a string, return the integer num without trailing zeros as a string.
//
// Example:
// Input: num = "51230100"
// Output: "512301"
// Explanation: Integer "51230100" has 2 trailing zeros, we remove them and return integer "512301".
//
// Constraints:
// 1 <= num.length <= 1000
// 	num consists of only digits.
// 	num doesn't have any leading zeros.
//

class Solution {
    public String removeTrailingZeros(String num) {
        int i = num.length() - 1;
        while (i >= 0 && num.charAt(i) == '0') {
            i--;
        }
        return num.substring(0, i + 1);         
    }
}
