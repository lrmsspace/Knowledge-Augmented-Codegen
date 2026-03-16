// Source: https://leetcode.com/problems/remove-digit-from-number-to-maximize-result/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string number representing a positive integer and a character digit.
//
// Return the resulting string after removing exactly one occurrence of digit from number such that the value of the resulting string in decimal form is maximized. The test cases are generated such that digit occurs at least once in number.
//
// Example:
// Input: number = "123", digit = "3"
// Output: "12"
// Explanation: There is only one '3' in "123". After removing '3', the result is "12".
//
// Constraints:
// 2 <= number.length <= 100
// 	number consists of digits from '1' to '9'.
// 	digit is a digit from '1' to '9'.
// 	digit occurs at least once in number.
//

class Solution {
    public String removeDigit(String number, char digit) {
        String maxNumber = "";
        for (int i = 0; i < number.length(); i++) {
            if (number.charAt(i) == digit) {
                String newNumber = number.substring(0, i) + number.substring(i + 1);
                if (newNumber.compareTo(maxNumber) > 0) {
                    maxNumber = newNumber;
                }
            }
        }
        return maxNumber;           
    }
}
