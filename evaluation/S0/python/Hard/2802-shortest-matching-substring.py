# Source: https://leetcode.com/problems/shortest-matching-substring/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s and a pattern string p, where p contains exactly two '*' characters.
#
# The '*' in p matches any sequence of zero or more characters.
#
# Return the length of the shortest substring in s that matches p. If there is no such substring, return -1.
# Note: The empty substring is considered valid.
#
# Example:
# Input: s = "abaacbaecebce", p = "ba*c*ce"
#
# Output: 8
#
# Explanation:
#
# The shortest matching substring of p in s is "baecebce".
#
# Constraints:
# 1 <= s.length <= 105
# 	2 <= p.length <= 105
# 	s contains only lowercase English letters.
# 	p contains only lowercase English letters and exactly two '*'.
#

class Solution(object):
    def shortestMatchingSubstring(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: int
        """
        n = len(s)
        parts = p.split('*')
        if len(parts) != 3:
            return -1  # Invalid pattern

        left, mid, right = parts
        len_left, len_mid, len_right = len(left), len(mid), len(right)

        min_length = float('inf')

        # Precompute the positions of left and right parts
        left_positions = []
        right_positions = [ -1 ] * n

        # Find all occurrences of left part
        for i in range(n - len_left + 1):
            if s[i:i + len_left] == left:
                left_positions.append(i)

        # Find all occurrences of right part from the end
        for i in range(n - len_right, -1, -1):
            if s[i:i + len_right] == right:
                right_positions[i] = i
            elif i + 1 < n:
                right_positions[i] = right_positions[i + 1]

        # Check for each left position
        for start in left_positions:
            mid_start = start + len_left
            if mid_start + len_mid > n:
                continue

            # Find mid part
            mid_index = s.find(mid, mid_start)
            if mid_index == -1:
                continue

            # Find right part after mid
            right_index = right_positions[mid_index + len_mid]
            if right_index != -1:
                total_length = (right_index + len_right) - start
                min_length = min(min_length, total_length)

        return min_length if min_length != float('inf') else -1