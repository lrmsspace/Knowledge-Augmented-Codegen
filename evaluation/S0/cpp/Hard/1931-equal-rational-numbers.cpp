// Source: https://leetcode.com/problems/equal-rational-numbers/   |   Difficulty: Hard
//
// Problem Description:
// Given two strings s and t, each of which represents a non-negative rational number, return true if and only if they represent the same number. The strings may use parentheses to denote the repeating part of the rational number.
//
// A rational number can be represented using up to three parts: <IntegerPart>, <NonRepeatingPart>, and a <RepeatingPart>. The number will be represented in one of the following three ways:
//
//
// 	<IntegerPart>
//
// 	
// 		For example, 12, 0, and 123.
// 	
// 	
// 	<IntegerPart><.><NonRepeatingPart>
// 	
// 		For example, 0.5, 1., 2.12, and 123.0001.
// 	
// 	
// 	<IntegerPart><.><NonRepeatingPart><(><RepeatingPart><)>
// 	
// 		For example, 0.1(6), 1.(9), 123.00(1212).
// 	
// 	
//
//
// The repeating portion of a decimal expansion is conventionally denoted within a pair of round brackets. For example:
//
//
// 	1/6 = 0.16666666... = 0.1(6) = 0.1666(6) = 0.166(66).
//
// Example:
// Input: s = "0.(52)", t = "0.5(25)"
// Output: true
// Explanation: Because "0.(52)" represents 0.52525252..., and "0.5(25)" represents 0.52525252525..... , the strings represent the same number.
//
// Constraints:
// Each part consists only of digits.
// 	The <IntegerPart> does not have leading zeros (except for the zero itself).
// 	1 <= <IntegerPart>.length <= 4
// 	0 <= <NonRepeatingPart>.length <= 4
// 	1 <= <RepeatingPart>.length <= 4
//

class Solution {
public:
    bool isRationalEqual(string s, string t) {
        auto parse = [](const string& str, long long& numerator, long long& denominator) {
            size_t pos = str.find('.');
            string intPart = (pos == string::npos) ? str : str.substr(0, pos);
            string fracPart = (pos == string::npos) ? "" : str.substr(pos + 1);
            
            size_t repPos = fracPart.find('(');
            string nonRepPart = (repPos == string::npos) ? fracPart : fracPart.substr(0, repPos);
            string repPart = (repPos == string::npos) ? "" : fracPart.substr(repPos + 1, fracPart.length() - repPos - 2);
            
            long long intVal = stoll(intPart);
            long long nonRepVal = nonRepPart.empty() ? 0 : stoll(nonRepPart);
            long long repVal = repPart.empty() ? 0 : stoll(repPart);
            
            long long nonRepLen = nonRepPart.length();
            long long repLen = repPart.length();
            
            if (repLen > 0) {
                denominator = pow(10, nonRepLen) * (pow(10, repLen) - 1);
                numerator = intVal * denominator + nonRepVal * (pow(10, repLen) - 1) + repVal;
            } else {
                denominator = pow(10, nonRepLen);
                numerator = intVal * denominator + nonRepVal;
            }
        };
        
        long long numS, denS, numT, denT;
        parse(s, numS, denS);
        parse(t, numT, denT);
        
        return numS * denT == numT * denS;          
    }
};
