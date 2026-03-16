# Source: https://leetcode.com/problems/minimum-number-of-changes-to-make-binary-string-beautiful/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed binary string s having an even length.
#
# A string is beautiful if it's possible to partition it into one or more substrings such that:
#
#
# 	Each substring has an even length.
# 	Each substring contains only 1's or only 0's.
#
#
# You can change any character in s to 0 or 1.
#
# Return the minimum number of changes required to make the string s beautiful.
#
# Example:
# Input: s = "1001"
# Output: 2
# Explanation: We change s[1] to 1 and s[3] to 0 to get string "1100".
# It can be seen that the string "1100" is beautiful because we can partition it into "11|00".
# It can be proven that 2 is the minimum number of changes needed to make the string beautiful.
#
# Constraints:
# 2 <= s.length <= 105
# 	s has an even length.
# 	s[i] is either '0' or '1'.
#

class Solution(object):
    def minChanges(self, s):
        """
        :type s: str
        :rtype: int
        """
        count0_even = 0
        count0_odd = 0
        count1_even = 0
        count1_odd = 0
        
        for i in range(len(s)):
            if i % 2 == 0:
                if s[i] == '0':
                    count0_even += 1
                else:
                    count1_even += 1
            else:
                if s[i] == '0':
                    count0_odd += 1
                else:
                    count1_odd += 1
        
        changes_case1 = (len(s) // 2 - count0_even) + (len(s) // 2 - count1_odd)
        changes_case2 = (len(s) // 2 - count1_even) + (len(s) // 2 - count0_odd)
        
        return min(changes_case1, changes_case2)