// Source: https://leetcode.com/problems/add-strings/   |   Difficulty: Easy
//
// Problem Description:
// Given two non-negative integers, num1 and num2 represented as string, return the sum of num1 and num2 as a string.
//
// You must solve the problem without using any built-in library for handling large integers (such as BigInteger). You must also not convert the inputs to integers directly.
//
// Example:
// Input: num1 = "11", num2 = "123"
// Output: "134"
//
// Constraints:
// 1 <= num1.length, num2.length <= 104
// 	num1 and num2 consist of only digits.
// 	num1 and num2 don't have any leading zeros except for the zero itself.
//

class Solution {
public:
    string addStrings(string num1, string num2) {
        string result;
        int carry = 0;
        int i = num1.size() - 1;
        int j = num2.size() - 1;

        while (i >= 0 || j >= 0 || carry) {
            int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
            int digit2 = (j >= 0) ? num2[j--] - '0' : 0;

            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result.push_back((sum % 10) + '0');
        }

        reverse(result.begin(), result.end());
        return result;          
    }
};
