// Source: https://leetcode.com/problems/fraction-addition-and-subtraction/   |   Difficulty: Medium
//
// Problem Description:
// Given a string expression representing an expression of fraction addition and subtraction, return the calculation result in string format.
//
// The final result should be an irreducible fraction. If your final result is an integer, change it to the format of a fraction that has a denominator 1. So in this case, 2 should be converted to 2/1.
//
// Example:
// Input: expression = "-1/2+1/2"
// Output: "0/1"
//
// Constraints:
// The input string only contains '0' to '9', '/', '+' and '-'. So does the output.
// 	Each fraction (input and output) has the format ±numerator/denominator. If the first input fraction or the output is positive, then '+' will be omitted.
// 	The input only contains valid irreducible fractions, where the numerator and denominator of each fraction will always be in the range [1, 10]. If the denominator is 1, it means this fraction is actually an integer in a fraction format defined above.
// 	The number of given fractions will be in the range [1, 10].
// 	The numerator and denominator of the final result are guaranteed to be valid and in the range of 32-bit int.
//

class Solution {
public:
    string fractionAddition(string expression) {
        int numerator = 0, denominator = 1;
        int i = 0, n = expression.size();

        while (i < n) {
            int sign = 1;
            if (expression[i] == '+' || expression[i] == '-') {
                sign = (expression[i] == '+') ? 1 : -1;
                i++;
            }

            int num = 0;
            while (i < n && isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            num *= sign;

            i++; // skip '/'

            int denom = 0;
            while (i < n && isdigit(expression[i])) {
                denom = denom * 10 + (expression[i] - '0');
                i++;
            }

            numerator = numerator * denom + num * denominator;
            denominator *= denom;

            int gcdVal = gcd(abs(numerator), denominator);
            numerator /= gcdVal;
            denominator /= gcdVal;
        }

        return to_string(numerator) + "/" + to_string(denominator);         
    }
};
