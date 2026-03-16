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
    public String fractionToDecimal(int numerator, int denominator) {
        if (numerator == 0) return "0";

        StringBuilder sb = new StringBuilder();

        // Handle sign
        if ((numerator < 0) ^ (denominator < 0)) {
            sb.append("-");
        }

        // Convert to long to avoid overflow
        long num = Math.abs((long) numerator);
        long den = Math.abs((long) denominator);

        // Integer part
        sb.append(num / den);
        num %= den;

        // If no fractional part
        if (num == 0) {
            return sb.toString();
        }

        sb.append(".");

        // Map to store the position of each remainder
        Map<Long, Integer> map = new HashMap<>();
        while (num != 0) {
            // If the remainder is already seen, we have a repeating fraction
            if (map.containsKey(num)) {
                int index = map.get(num);
                sb.insert(index, "(");
                sb.append(")");
                break;
            }

            // Store the position of this remainder
            map.put(num, sb.length());

            num *= 10;
            sb.append(num / den);
            num %= den;
        }

        return sb.toString();           
    }
}
