# Source: https://leetcode.com/problems/additive-number/   |   Difficulty: Medium
#
# Problem Description:
# An additive number is a string whose digits can form an additive sequence.
#
# A valid additive sequence should contain at least three numbers. Except for the first two numbers, each subsequent number in the sequence must be the sum of the preceding two.
#
# Given a string containing only digits, return true if it is an additive number or false otherwise.
#
# Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.
#
# Example:
# Input: "112358"
# Output: true
# Explanation: 
# The digits can form an additive sequence: 1, 1, 2, 3, 5, 8. 
# 1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
#
# Constraints:
# 1 <= num.length <= 35
# 	num consists only of digits.
#
#
#  
# Follow up: How would you handle overflow for very large input integers?
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
#   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
#   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
#   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
#   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
#   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
# - palindrome-partitioning (string, array, backtracking, recursion)
#   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
#   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
#   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
#   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
#   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
# - Linear Diophantine Equation (number, interval, enumeration)
#   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
#   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
#   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
#   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
#   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def isAdditiveNumber(self, num):
        """
        :type num: str
        :rtype: bool
        """
        n = len(num)
        
        # Helper function to check if the remaining string can form a valid additive sequence
        def is_valid_sequence(first, second, start):
            while start < n:
                next_num = first + second
                next_num_str = str(next_num)
                next_len = len(next_num_str)
                
                if num.startswith(next_num_str, start):
                    start += next_len
                    first, second = second, next_num
                else:
                    return False
            return True
        
        # Try all possible splits for the first two numbers
        for i in range(1, n):
            for j in range(i + 1, n):
                first_str = num[:i]
                second_str = num[i:j]
                
                # Skip if numbers have leading zeros
                if (first_str.startswith('0') and len(first_str) > 1) or (second_str.startswith('0') and len(second_str) > 1):
                    continue
                
                first = int(first_str)
                second = int(second_str)
                
                if is_valid_sequence(first, second, j):
                    return True
        
        return False