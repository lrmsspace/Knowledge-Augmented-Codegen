# Source: https://leetcode.com/problems/shift-distance-between-two-strings/   |   Difficulty: Medium
#
# Problem Description:
# You are given two strings s and t of the same length, and two integer arrays nextCost and previousCost.
#
# In one operation, you can pick any index i of s, and perform either one of the following actions:
#
#
# 	Shift s[i] to the next letter in the alphabet. If s[i] == 'z', you should replace it with 'a'. This operation costs nextCost[j] where j is the index of s[i] in the alphabet.
# 	Shift s[i] to the previous letter in the alphabet. If s[i] == 'a', you should replace it with 'z'. This operation costs previousCost[j] where j is the index of s[i] in the alphabet.
#
#
# The shift distance is the minimum total cost of operations required to transform s into t.
#
# Return the shift distance from s to t.
#
# Example:
# Input: s = "abab", t = "baba", nextCost = [100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0], previousCost = [1,100,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
#
# Output: 2
#
# Explanation:
#
#
# 	We choose index i = 0 and shift s[0] 25 times to the previous character for a total cost of 1.
# 	We choose index i = 1 and shift s[1] 25 times to the next character for a total cost of 0.
# 	We choose index i = 2 and shift s[2] 25 times to the previous character for a total cost of 1.
# 	We choose index i = 3 and shift s[3] 25 times to the next character for a total cost of 0.
#
# Constraints:
# 1 <= s.length == t.length <= 105
# 	s and t consist only of lowercase English letters.
# 	nextCost.length == previousCost.length == 26
# 	0 <= nextCost[i], previousCost[i] <= 109
#

class Solution(object):
    def shiftDistance(self, s, t, nextCost, previousCost):
        """
        :type s: str
        :type t: str
        :type nextCost: List[int]
        :type previousCost: List[int]
        :rtype: int
        """
        total_cost = 0
        n = len(s)
        
        for i in range(n):
            if s[i] == t[i]:
                continue
            
            cost_forward = 0
            cost_backward = 0
            
            # Calculate cost for shifting forward
            current_char = s[i]
            while current_char != t[i]:
                next_char = chr((ord(current_char) - ord('a') + 1) % 26 + ord('a'))
                cost_forward += nextCost[ord(current_char) - ord('a')]
                current_char = next_char
            
            # Calculate cost for shifting backward
            current_char = s[i]
            while current_char != t[i]:
                prev_char = chr((ord(current_char) - ord('a') - 1) % 26 + ord('a'))
                cost_backward += previousCost[ord(current_char) - ord('a')]
                current_char = prev_char
            
            total_cost += min(cost_forward, cost_backward)
        
        return total_cost