# Source: https://leetcode.com/problems/masking-personal-information/   |   Difficulty: Medium
#
# Problem Description:
# You are given a personal information string s, representing either an email address or a phone number. Return the masked personal information using the below rules.
#
# Email address:
#
# An email address is:
#
#
# 	A name consisting of uppercase and lowercase English letters, followed by
# 	The '@' symbol, followed by
# 	The domain consisting of uppercase and lowercase English letters with a dot '.' somewhere in the middle (not the first or last character).
#
#
# To mask an email:
#
#
# 	The uppercase letters in the name and domain must be converted to lowercase letters.
# 	The middle letters of the name (i.e., all but the first and last letters) must be replaced by 5 asterisks "*****".
#
#
# Phone number:
#
# A phone number is formatted as follows:
#
#
# 	The phone number contains 10-13 digits.
# 	The last 10 digits make up the local number.
# 	The remaining 0-3 digits, in the beginning, make up the country code.
# 	Separation characters from the set {'+', '-', '(', ')', ' '} separate the above digits in some way.
#
#
# To mask a phone number:
#
#
# 	Remove all separation characters.
# 	The masked phone number should have the form:
# 	
# 		"***-***-XXXX" if the country code has 0 digits.
# 		"+*-***-***-XXXX" if the country code has 1 digit.
# 		"+**-***-***-XXXX" if the country code has 2 digits.
# 		"+***-***-***-XXXX" if the country code has 3 digits.
# 	
# 	
# 	"XXXX" is the last 4 digits of the local number.
#
# Example:
# Input: s = "LeetCode@LeetCode.com"
# Output: "l*****e@leetcode.com"
# Explanation: s is an email address.
# The name and domain are converted to lowercase, and the middle of the name is replaced by 5 asterisks.
#
# Constraints:
# s is either a valid email or a phone number.
# 	If s is an email:
# 	
# 		8 <= s.length <= 40
# 		s consists of uppercase and lowercase English letters and exactly one '@' symbol and '.' symbol.
# 	
# 	
# 	If s is a phone number:
# 	
# 		10 <= s.length <= 20
# 		s consists of digits, spaces, and the symbols '(', ')', '-', and '+'.
#
# Helpful references (internal KB):
# - Suffix Automaton (graph, string, simulation)
#   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
#   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
#   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
#   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
#   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
# - Linear Diophantine Equation (number, interval, enumeration)
#   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
#   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
#   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
#   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
#   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
# - Balanced Ternary (number, string, enumeration, simulation)
#   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
#   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
#   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
#   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
#   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maskPII(self, s):
        """
        :type s: str
        :rtype: str
        """
        if "@" in s:
            # It's an email
            name, domain = s.split("@")
            name = name.lower()
            domain = domain.lower()
            masked_name = name[0] + "*****" + name[-1]
            return masked_name + "@" + domain
        else:
            # It's a phone number
            digits = [c for c in s if c.isdigit()]
            local_number = "".join(digits[-10:])
            country_code_length = len(digits) - 10
            if country_code_length == 0:
                return "***-***-" + local_number[-4:]
            else:
                country_code = "+" + "*" * country_code_length
                return country_code + "-***-***-" + local_number[-4:]