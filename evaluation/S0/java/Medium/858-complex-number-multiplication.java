// Source: https://leetcode.com/problems/complex-number-multiplication/   |   Difficulty: Medium
//
// Problem Description:
// A complex number can be represented as a string on the form "real+imaginaryi" where:
//
//
// 	real is the real part and is an integer in the range [-100, 100].
// 	imaginary is the imaginary part and is an integer in the range [-100, 100].
// 	i2 == -1.
//
//
// Given two complex numbers num1 and num2 as strings, return a string of the complex number that represents their multiplications.
//
// Example:
// Input: num1 = "1+1i", num2 = "1+1i"
// Output: "0+2i"
// Explanation: (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i, and you need convert it to the form of 0+2i.
//
// Constraints:
// num1 and num2 are valid complex numbers.
//

class Solution {
    public String complexNumberMultiply(String num1, String num2) {
        String[] parts1 = num1.split("\\+");
        String[] parts2 = num2.split("\\+");

        int a = Integer.parseInt(parts1[0]);
        int b = Integer.parseInt(parts1[1].substring(0, parts1[1].length() - 1));

        int c = Integer.parseInt(parts2[0]);
        int d = Integer.parseInt(parts2[1].substring(0, parts2[1].length() - 1));

        int realPart = a * c - b * d;
        int imaginaryPart = a * d + b * c;

        return realPart + "+" + imaginaryPart + "i";            
    }
}
