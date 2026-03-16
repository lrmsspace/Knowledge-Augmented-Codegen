# Source: https://leetcode.com/problems/positions-of-large-groups/   |   Difficulty: Easy
#
# Problem Description:
# In a string s of lowercase letters, these letters form consecutive groups of the same character.
#
# For example, a string like s = "abbxxxxzyy" has the groups "a", "bb", "xxxx", "z", and "yy".
#
# A group is identified by an interval [start, end], where start and end denote the start and end indices (inclusive) of the group. In the above example, "xxxx" has the interval [3,6].
#
# A group is considered large if it has 3 or more characters.
#
# Return the intervals of every large group sorted in increasing order by start index.
#
# Example:
# Input: s = "abbxxxxzzy"
# Output: [[3,6]]
# Explanation: "xxxx" is the only large group with start index 3 and end index 6.
#
# Constraints:
# 1 <= s.length <= 1000
# 	s contains lowercase English letters only.
#

class Solution(object):
    def largeGroupPositions(self, s):
        """
        :type s: str
        :rtype: List[List[int]]
        """
        res = []
        n = len(s)
        i = 0
        
        while i < n:
            j = i
            while j < n and s[j] == s[i]:
                j += 1
            
            if j - i >= 3:
                res.append([i, j - 1])
            
            i = j
        
        return res