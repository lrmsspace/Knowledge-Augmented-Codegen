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
# - Balanced bracket sequences (number, counting)
#   • When to use: Use this when verifying if a sequence of delimiters is correctly nested and balanced. It is also applicable for counting or generating all possible valid sequences of a given length.
#   • Idea: This algorithm involves checking if a sequence of opening and closing delimiters is properly matched and nested, or enumerating such sequences. Validation typically uses a stack in O(N) time, while generation often involves backtracking with O(Catalan(N)) complexity.
#   • Invariants: The stack contains only opening delimiters that are yet to be matched.; The balance counter (open - close) is never negative at any point during traversal.
#   • Tips: Use a stack to track unmatched opening delimiters for validation.; Maintain a balance counter (increment for open, decrement for close) for a simpler check.
#   • Pitfalls: Forgetting to check if the stack is empty after processing the entire sequence.; Allowing a closing delimiter when no matching opening delimiter is available (empty stack or mismatch).
# - Prüfer code (tree, array, simulation, two-pointers)
#   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
#   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
#   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
#   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
#   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
# - Prüfer code (tree, array, simulation, two-pointers)
#   • When to use: Use when needing to uniquely encode or decode a labeled tree into a sequence of numbers, or to count the number of spanning trees for a complete graph. It's also useful for problems involving tree properties like degree sequences.
#   • Idea: Prüfer code is a unique sequence representing a labeled tree, allowing conversion between a tree and a sequence of numbers. Its generation and decoding typically involve an iterative process of finding and removing leaves, achieving O(N log N) or O(N) complexity with optimized leaf finding.
#   • Invariants: The Prüfer sequence always has N-2 elements for an N-vertex tree.; Each vertex's degree is correctly maintained throughout the process.
#   • Tips: Maintain a degree array to efficiently find leaves.; Use a min-priority queue or a two-pointer approach for finding the smallest leaf.
#   • Pitfalls: Off-by-one errors in sequence length or vertex indexing.; Incorrectly handling the last two vertices during decoding.
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
        depth = 0
        result = []
        
        for char in seq:
            if char == '(':
                depth += 1
                result.append(depth % 2)  # Assign to group A (0) or B (1) based on current depth
            else:
                result.append(depth % 2)  # Assign to group A (0) or B (1) based on current depth
                depth -= 1
        
        return result