# Source: https://leetcode.com/problems/check-if-string-is-transformable-with-substring-sort-operations/   |   Difficulty: Hard
#
# Problem Description:
# Given two strings s and t, transform string s into string t using the following operation any number of times:
#
#
# 	Choose a non-empty substring in s and sort it in place so the characters are in ascending order.
#
# 	
# 		For example, applying the operation on the underlined substring in "14234" results in "12344".
# 	
# 	
#
#
# Return true if it is possible to transform s into t. Otherwise, return false.
#
# A substring is a contiguous sequence of characters within a string.
#
# Example:
# Input: s = "84532", t = "34852"
# Output: true
# Explanation: You can transform s into t using the following sort operations:
# "84532" (from index 2 to 3) -> "84352"
# "84352" (from index 0 to 2) -> "34852"
#
# Constraints:
# s.length == t.length
# 	1 <= s.length <= 105
# 	s and t consist of only digits.
#

class Solution(object):
    def isTransformable(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: bool
        """
        from collections import defaultdict, deque
        import bisect

        pos = defaultdict(deque)
        for i, c in enumerate(s):
            pos[c].append(i)

        for c in t:
            if not pos[c]:
                return False
            cur_pos = pos[c][0]
            for smaller_c in map(str, range(int(c))):
                if pos[smaller_c] and pos[smaller_c][0] < cur_pos:
                    return False
            pos[c].popleft()
        return True