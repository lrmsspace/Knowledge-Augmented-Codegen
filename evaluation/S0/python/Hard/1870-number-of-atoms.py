# Source: https://leetcode.com/problems/number-of-atoms/   |   Difficulty: Hard
#
# Problem Description:
# Given a string formula representing a chemical formula, return the count of each atom.
#
# The atomic element always starts with an uppercase character, then zero or more lowercase letters, representing the name.
#
# One or more digits representing that element's count may follow if the count is greater than 1. If the count is 1, no digits will follow.
#
#
# 	For example, "H2O" and "H2O2" are possible, but "H1O2" is impossible.
#
#
# Two formulas are concatenated together to produce another formula.
#
#
# 	For example, "H2O2He3Mg4" is also a formula.
#
#
# A formula placed in parentheses, and a count (optionally added) is also a formula.
#
#
# 	For example, "(H2O2)" and "(H2O2)3" are formulas.
#
#
# Return the count of all elements as a string in the following form: the first name (in sorted order), followed by its count (if that count is more than 1), followed by the second name (in sorted order), followed by its count (if that count is more than 1), and so on.
#
# The test cases are generated so that all the values in the output fit in a 32-bit integer.
#
# Example:
# Input: formula = "H2O"
# Output: "H2O"
# Explanation: The count of elements are {'H': 2, 'O': 1}.
#
# Constraints:
# 1 <= formula.length <= 1000
# 	formula consists of English letters, digits, '(', and ')'.
# 	formula is always valid.
#

class Solution(object):
    def countOfAtoms(self, formula):
        """
        :type formula: str
        :rtype: str
        """
        import collections
        stack = [collections.Counter()]
        i, n = 0, len(formula)
        
        while i < n:
            if formula[i] == '(':
                stack.append(collections.Counter())
                i += 1
            elif formula[i] == ')':
                top = stack.pop()
                i += 1
                i_start = i
                while i < n and formula[i].isdigit():
                    i += 1
                multiplicity = int(formula[i_start:i] or 1)
                for name, v in top.items():
                    stack[-1][name] += v * multiplicity
            else:
                i_start = i
                i += 1
                while i < n and formula[i].islower():
                    i += 1
                name = formula[i_start:i]
                i_start = i
                while i < n and formula[i].isdigit():
                    i += 1
                multiplicity = int(formula[i_start:i] or 1)
                stack[-1][name] += multiplicity
        
        ans = ""
        for name in sorted(stack[-1]):
            ans += name
            multiplicity = stack[-1][name]
            if multiplicity > 1:
                ans += str(multiplicity)
        return ans