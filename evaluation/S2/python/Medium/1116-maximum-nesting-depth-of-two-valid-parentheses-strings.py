# Source: https://leetcode.com/problems/maximum-nesting-depth-of-two-valid-parentheses-strings/   |   Difficulty: Medium
#
# Problem Description:
# A string is a valid parentheses string (denoted VPS) if and only if it consists of "(" and ")" characters only, and:
#
#
# 	It is the empty string, or
# 	It can be written as AB (A concatenated with B), where A and B are VPS's, or
# 	It can be written as (A), where A is a VPS.
#
#
# We can similarly define the nesting depth depth(S) of any VPS S as follows:
#
#
# 	depth("") = 0
# 	depth(A + B) = max(depth(A), depth(B)), where A and B are VPS's
# 	depth("(" + A + ")") = 1 + depth(A), where A is a VPS.
#
#
# For example,  "", "()()", and "()(()())" are VPS's (with nesting depths 0, 1, and 2), and ")(" and "(()" are not VPS's.
#
#  
#
# Given a VPS seq, split it into two disjoint subsequences A and B, such that A and B are VPS's (and A.length + B.length = seq.length).
#
# Now choose any such A and B such that max(depth(A), depth(B)) is the minimum possible value.
#
# Return an answer array (of length seq.length) that encodes such a choice of A and B:  answer[i] = 0 if seq[i] is part of A, else answer[i] = 1.  Note that even though multiple answers may exist, you may return any of them.
#
# Example:
# Input: seq = "(()())"
# Output: [0,1,1,1,1,0]
#
# Constraints:
# 1 <= seq.size <= 10000
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxDepthAfterSplit(self, seq):
        """
        :type seq: str
        :rtype: List[int]
        """
        answer = []
        depth = 0

        for char in seq:
            if char == '(':
                depth += 1
                answer.append(depth % 2)  # 奇数深度分配给 A (0)，偶数深度分配给 B (1)
            else:
                answer.append(depth % 2)  # 奇数深度分配给 A (0)，偶数深度分配给 B (1)
                depth -= 1

        return answer