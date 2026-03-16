# Source: https://leetcode.com/problems/equal-rational-numbers/   |   Difficulty: Hard
#
# Problem Description:
# Given two strings s and t, each of which represents a non-negative rational number, return true if and only if they represent the same number. The strings may use parentheses to denote the repeating part of the rational number.
#
# A rational number can be represented using up to three parts: <IntegerPart>, <NonRepeatingPart>, and a <RepeatingPart>. The number will be represented in one of the following three ways:
#
#
# 	<IntegerPart>
#
# 	
# 		For example, 12, 0, and 123.
# 	
# 	
# 	<IntegerPart><.><NonRepeatingPart>
# 	
# 		For example, 0.5, 1., 2.12, and 123.0001.
# 	
# 	
# 	<IntegerPart><.><NonRepeatingPart><(><RepeatingPart><)>
# 	
# 		For example, 0.1(6), 1.(9), 123.00(1212).
# 	
# 	
#
#
# The repeating portion of a decimal expansion is conventionally denoted within a pair of round brackets. For example:
#
#
# 	1/6 = 0.16666666... = 0.1(6) = 0.1666(6) = 0.166(66).
#
# Example:
# Input: s = "0.(52)", t = "0.5(25)"
# Output: true
# Explanation: Because "0.(52)" represents 0.52525252..., and "0.5(25)" represents 0.52525252525..... , the strings represent the same number.
#
# Constraints:
# Each part consists only of digits.
# 	The <IntegerPart> does not have leading zeros (except for the zero itself).
# 	1 <= <IntegerPart>.length <= 4
# 	0 <= <NonRepeatingPart>.length <= 4
# 	1 <= <RepeatingPart>.length <= 4
#

class Solution(object):
    def isRationalEqual(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: bool
        """
        def parse_number(num):
            if '(' in num:
                non_repeating, repeating = num.split('(')
                repeating = repeating.rstrip(')')
            else:
                non_repeating, repeating = num, ''
            
            if '.' in non_repeating:
                integer_part, fractional_part = non_repeating.split('.')
            else:
                integer_part, fractional_part = non_repeating, ''
            
            return integer_part, fractional_part, repeating
        
        def to_fraction(integer_part, fractional_part, repeating):
            if not repeating:
                numerator = int(integer_part + fractional_part)
                denominator = 10 ** len(fractional_part)
            else:
                non_repeating_len = len(fractional_part)
                repeating_len = len(repeating)
                
                full_num = integer_part + fractional_part + repeating
                non_repeating_num = integer_part + fractional_part
                
                numerator = int(full_num) - int(non_repeating_num)
                denominator = (10 ** non_repeating_len) * (10 ** repeating_len - 1)
                
                numerator += int(non_repeating_num) * (10 ** repeating_len - 1)
            
            return numerator, denominator
        
        def gcd(a, b):
            while b:
                a, b = b, a % b
            return a
        
        def simplify(numerator, denominator):
            common_divisor = gcd(numerator, denominator)
            return numerator // common_divisor, denominator // common_divisor
        
        int_s, frac_s, rep_s = parse_number(s)
        int_t, frac_t, rep_t = parse_number(t)
        
        num_s, den_s = to_fraction(int_s, frac_s, rep_s)
        num_t, den_t = to_fraction(int_t, frac_t, rep_t)
        
        num_s, den_s = simplify(num_s, den_s)
        num_t, den_t = simplify(num_t, den_t)
        
        return num_s == num_t and den_s == den_t