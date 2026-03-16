# Source: https://leetcode.com/problems/minimum-insertions-to-balance-a-parentheses-string/   |   Difficulty: Medium
#
# Problem Description:
# Given a parentheses string s containing only the characters '(' and ')'. A parentheses string is balanced if:
#
#
# 	Any left parenthesis '(' must have a corresponding two consecutive right parenthesis '))'.
# 	Left parenthesis '(' must go before the corresponding two consecutive right parenthesis '))'.
#
#
# In other words, we treat '(' as an opening parenthesis and '))' as a closing parenthesis.
#
#
# 	For example, "())", "())(())))" and "(())())))" are balanced, ")()", "()))" and "(()))" are not balanced.
#
#
# You can insert the characters '(' and ')' at any position of the string to balance it if needed.
#
# Return the minimum number of insertions needed to make s balanced.
#
# Example:
# Input: s = "(()))"
# Output: 1
# Explanation: The second '(' has two matching '))', but the first '(' has only ')' matching. We need to add one more ')' at the end of the string to be "(())))" which is balanced.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of '(' and ')' only.
#

class Solution(object):
    def minInsertions(self, s):
        """
        :type s: str
        :rtype: int
        """
        insertions = 0
        balance = 0
        i = 0
        
        while i < len(s):
            if s[i] == '(':
                balance += 2
            else:
                balance -= 1
                if i + 1 < len(s) and s[i + 1] == ')':
                    i += 1
                    balance -= 1
            
            if balance < 0:
                insertions += -balance
                balance = 0
            
            i += 1
        
        insertions += balance
        return insertions