# Source: https://leetcode.com/problems/swap-adjacent-in-lr-string/   |   Difficulty: Medium
#
# Problem Description:
# In a string composed of 'L', 'R', and 'X' characters, like "RXXLRXRXL", a move consists of either replacing one occurrence of "XL" with "LX", or replacing one occurrence of "RX" with "XR". Given the starting string start and the ending string result, return True if and only if there exists a sequence of moves to transform start to result.
#
# Example:
# Input: start = "RXXLRXRXL", result = "XRLXXRRLX"
# Output: true
# Explanation: We can transform start to result following these steps:
# RXXLRXRXL ->
# XRXLRXRXL ->
# XRLXRXRXL ->
# XRLXXRRXL ->
# XRLXXRRLX
#
# Constraints:
# 1 <= start.length <= 104
# 	start.length == result.length
# 	Both start and result will only consist of characters in 'L', 'R', and 'X'.
#

class Solution(object):
    def canTransform(self, start, result):
        """
        :type start: str
        :type result: str
        :rtype: bool
        """
        s1 = start.replace('X', '')
        s2 = result.replace('X', '')
        
        if s1 != s2:
            return False
        
        i, j = 0, 0
        n = len(start)
        
        while i < n and j < n:
            while i < n and start[i] == 'X':
                i += 1
            while j < n and result[j] == 'X':
                j += 1
            
            if i < n and j < n:
                if start[i] != result[j]:
                    return False
                
                if start[i] == 'L' and i < j:
                    return False
                
                if start[i] == 'R' and i > j:
                    return False
                
                i += 1
                j += 1
        
        return True