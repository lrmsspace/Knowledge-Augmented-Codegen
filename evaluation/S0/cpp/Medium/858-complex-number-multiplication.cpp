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
public:
    string complexNumberMultiply(string num1, string num2) {
        auto parseComplex = [](const string& num) {
            size_t plusPos = num.find('+');
            int real = stoi(num.substr(0, plusPos));
            int imag = stoi(num.substr(plusPos + 1, num.length() - plusPos - 2)); // exclude 'i'
            return make_pair(real, imag);
        };

        auto [a, b] = parseComplex(num1);
        auto [c, d] = parseComplex(num2);

        int realPart = a * c - b * d;
        int imagPart = a * d + b * c;

        return to_string(realPart) + "+" + to_string(imagPart) + "i";           
    }
};
