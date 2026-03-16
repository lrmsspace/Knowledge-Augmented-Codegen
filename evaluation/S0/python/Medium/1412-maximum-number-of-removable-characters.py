# Source: https://leetcode.com/problems/maximum-number-of-removable-characters/   |   Difficulty: Medium
#
# Problem Description:
# You are given two strings s and p where p is a subsequence of s. You are also given a distinct 0-indexed integer array removable containing a subset of indices of s (s is also 0-indexed).
#
# You want to choose an integer k (0 <= k <= removable.length) such that, after removing k characters from s using the first k indices in removable, p is still a subsequence of s. More formally, you will mark the character at s[removable[i]] for each 0 <= i < k, then remove all marked characters and check if p is still a subsequence.
#
# Return the maximum k you can choose such that p is still a subsequence of s after the removals.
#
# A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
#
# Example:
# Input: s = "abcacb", p = "ab", removable = [3,1,0]
# Output: 2
# Explanation: After removing the characters at indices 3 and 1, "abcacb" becomes "accb".
# "ab" is a subsequence of "accb".
# If we remove the characters at indices 3, 1, and 0, "abcacb" becomes "ccb", and "ab" is no longer a subsequence.
# Hence, the maximum k is 2.
#
# Constraints:
# 1 <= p.length <= s.length <= 105
# 	0 <= removable.length < s.length
# 	0 <= removable[i] < s.length
# 	p is a subsequence of s.
# 	s and p both consist of lowercase English letters.
# 	The elements in removable are distinct.
#

class Solution(object):
    def maximumRemovals(self, s, p, removable):
        """
        :type s: str
        :type p: str
        :type removable: List[int]
        :rtype: int
        """
        def can_remove(k):
            removed = set(removable[:k])
            p_index = 0
            
            for i in range(len(s)):
                if i in removed:
                    continue
                if p_index < len(p) and s[i] == p[p_index]:
                    p_index += 1
                if p_index == len(p):
                    return True
            return p_index == len(p)
        
        left, right = 0, len(removable)
        answer = 0
        
        while left <= right:
            mid = (left + right) // 2
            if can_remove(mid):
                answer = mid
                left = mid + 1
            else:
                right = mid - 1
        
        return answer