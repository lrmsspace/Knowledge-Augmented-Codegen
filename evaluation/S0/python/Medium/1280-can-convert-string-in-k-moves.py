# Source: https://leetcode.com/problems/can-convert-string-in-k-moves/   |   Difficulty: Medium
#
# Problem Description:
# Given two strings s and t, your goal is to convert s into t in k moves or less.
#
# During the ith (1 <= i <= k) move you can:
#
#
# 	Choose any index j (1-indexed) from s, such that 1 <= j <= s.length and j has not been chosen in any previous move, and shift the character at that index i times.
# 	Do nothing.
#
#
# Shifting a character means replacing it by the next letter in the alphabet (wrapping around so that 'z' becomes 'a'). Shifting a character by i means applying the shift operations i times.
#
# Remember that any index j can be picked at most once.
#
# Return true if it's possible to convert s into t in no more than k moves, otherwise return false.
#
# Example:
# Input: s = "input", t = "ouput", k = 9
# Output: true
# Explanation: In the 6th move, we shift 'i' 6 times to get 'o'. And in the 7th move we shift 'n' to get 'u'.
#
# Constraints:
# 1 <= s.length, t.length <= 10^5
# 	0 <= k <= 10^9
# 	s, t contain only lowercase English letters.
#

class Solution(object):
    def canConvertString(self, s, t, k):
        """
        :type s: str
        :type t: str
        :type k: int
        :rtype: bool
        """
        if len(s) != len(t):
            return False
        
        shifts = {}
        
        for i in range(len(s)):
            diff = (ord(t[i]) - ord(s[i])) % 26
            if diff != 0:
                if diff not in shifts:
                    shifts[diff] = diff
                else:
                    shifts[diff] += 26
        
        for shift in shifts.values():
            if shift > k:
                return False
        
        return True