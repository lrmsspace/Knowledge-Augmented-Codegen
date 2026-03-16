# Source: https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer n, find a sequence with elements in the range [1, n] that satisfies all of the following:
#
#
# 	The integer 1 occurs once in the sequence.
# 	Each integer between 2 and n occurs twice in the sequence.
# 	For every integer i between 2 and n, the distance between the two occurrences of i is exactly i.
#
#
# The distance between two numbers on the sequence, a[i] and a[j], is the absolute difference of their indices, |j - i|.
#
# Return the lexicographically largest sequence. It is guaranteed that under the given constraints, there is always a solution. 
#
# A sequence a is lexicographically larger than a sequence b (of the same length) if in the first position where a and b differ, sequence a has a number greater than the corresponding number in b. For example, [0,1,9,0] is lexicographically larger than [0,1,5,6] because the first position they differ is at the third number, and 9 is greater than 5.
#
# Example:
# Input: n = 3
# Output: [3,1,2,3,2]
# Explanation: [2,3,2,1,3] is also a valid sequence, but [3,1,2,3,2] is the lexicographically largest valid sequence.
#
# Constraints:
# 1 <= n <= 20
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
    def constructDistancedSequence(self, n):
        """
        :type n: int
        :rtype: List[int]
        """
        def backtrack(pos):
            if pos == len(res):
                return True
            if res[pos] != 0:
                return backtrack(pos + 1)

            for num in range(n, 1, -1):
                if used[num]:
                    continue
                if pos + num < len(res) and res[pos + num] == 0:
                    res[pos] = num
                    res[pos + num] = num
                    used[num] = True
                    if backtrack(pos + 1):
                        return True
                    res[pos] = 0
                    res[pos + num] = 0
                    used[num] = False

            if not used[1]:
                res[pos] = 1
                used[1] = True
                if backtrack(pos + 1):
                    return True
                res[pos] = 0
                used[1] = False

            return False

        res = [0] * (2 * n - 1)
        used = [False] * (n + 1)
        backtrack(0)
        return res