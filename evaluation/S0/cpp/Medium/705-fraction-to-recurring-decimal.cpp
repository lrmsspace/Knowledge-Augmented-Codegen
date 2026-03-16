// Source: https://leetcode.com/problems/fraction-to-recurring-decimal/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.
//
// If the fractional part is repeating, enclose the repeating part in parentheses
//
// If multiple answers are possible, return any of them.
//
// It is guaranteed that the length of the answer string is less than 104 for all the given inputs.
//
// Note that if the fraction can be represented as a finite length string, you must return it.
//
// Example:
// Input: numerator = 1, denominator = 2
// Output: "0.5"
//
// Constraints:
// -231 <= numerator, denominator <= 231 - 1
// 	denominator != 0
//

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) return "0";
        
        string result;
        
        // Determine the sign
        if ((numerator < 0) ^ (denominator < 0)) {
            result += "-";
        }
        
        // Work with absolute values to avoid overflow
        long long num = abs((long long)numerator);
        long long den = abs((long long)denominator);
        
        // Integer part
        result += to_string(num / den);
        long long remainder = num % den;
        
        if (remainder == 0) {
            return result; // No fractional part
        }
        
        result += ".";
        
        // Map to store the position of each remainder
        unordered_map<long long, int> remainderMap;
        string fractionalPart;
        
        while (remainder != 0) {
            // If this remainder has been seen before, we have a repeating fraction
            if (remainderMap.find(remainder) != remainderMap.end()) {
                int pos = remainderMap[remainder];
                fractionalPart.insert(pos, "(");
                fractionalPart += ")";
                result += fractionalPart;
                return result;
            }
            
            // Store the position of this remainder
            remainderMap[remainder] = fractionalPart.size();
            
            remainder *= 10;
            fractionalPart += to_string(remainder / den);
            remainder %= den;
        }
        
        result += fractionalPart;
        return result;          
    }
};
