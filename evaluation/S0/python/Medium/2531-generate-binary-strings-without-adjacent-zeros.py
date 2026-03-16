# Source: https://leetcode.com/problems/generate-binary-strings-without-adjacent-zeros/   |   Difficulty: Medium
#
# Problem Description:
# You are given a positive integer n.
#
# A binary string x is valid if all substrings of x of length 2 contain at least one "1".
#
# Return all valid strings with length n, in any order.
#
# Example:
# Input: n = 3
#
# Output: ["010","011","101","110","111"]
#
# Explanation:
#
# The valid strings of length 3 are: "010", "011", "101", "110", and "111".
#
# Constraints:
# 1 <= n <= 18
#

class Solution(object):
    def validStrings(self, n):
        """
        :type n: int
        :rtype: List[str]
        """
        result = []
        
        def backtrack(current):
            if len(current) == n:
                result.append(current)
                return
            
            # Append '1' and continue
            backtrack(current + '1')
            
            # Append '0' only if the last character is not '0'
            if not current or current[-1] != '0':
                backtrack(current + '0')
        
        backtrack('')
        return result