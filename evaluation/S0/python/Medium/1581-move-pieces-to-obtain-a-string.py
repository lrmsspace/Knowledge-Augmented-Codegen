# Source: https://leetcode.com/problems/move-pieces-to-obtain-a-string/   |   Difficulty: Medium
#
# Problem Description:
# You are given two strings start and target, both of length n. Each string consists only of the characters 'L', 'R', and '_' where:
#
#
# 	The characters 'L' and 'R' represent pieces, where a piece 'L' can move to the left only if there is a blank space directly to its left, and a piece 'R' can move to the right only if there is a blank space directly to its right.
# 	The character '_' represents a blank space that can be occupied by any of the 'L' or 'R' pieces.
#
#
# Return true if it is possible to obtain the string target by moving the pieces of the string start any number of times. Otherwise, return false.
#
# Example:
# Input: start = "_L__R__R_", target = "L______RR"
# Output: true
# Explanation: We can obtain the string target from start by doing the following moves:
# - Move the first piece one step to the left, start becomes equal to "L___R__R_".
# - Move the last piece one step to the right, start becomes equal to "L___R___R".
# - Move the second piece three steps to the right, start becomes equal to "L______RR".
# Since it is possible to get the string target from start, we return true.
#
# Constraints:
# n == start.length == target.length
# 	1 <= n <= 105
# 	start and target consist of the characters 'L', 'R', and '_'.
#

class Solution(object):
    def canChange(self, start, target):
        """
        :type start: str
        :type target: str
        :rtype: bool
        """
        s_ptr, t_ptr = 0, 0
        n = len(start)
        
        while s_ptr < n or t_ptr < n:
            while s_ptr < n and start[s_ptr] == '_':
                s_ptr += 1
            while t_ptr < n and target[t_ptr] == '_':
                t_ptr += 1
            
            if s_ptr == n and t_ptr == n:
                return True
            if s_ptr == n or t_ptr == n:
                return False
            
            if start[s_ptr] != target[t_ptr]:
                return False
            
            if start[s_ptr] == 'L' and s_ptr < t_ptr:
                return False
            if start[s_ptr] == 'R' and s_ptr > t_ptr:
                return False
            
            s_ptr += 1
            t_ptr += 1
        
        return True