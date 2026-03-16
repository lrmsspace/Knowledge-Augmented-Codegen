# Source: https://leetcode.com/problems/find-maximum-number-of-non-intersecting-substrings/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string word.
#
# Return the maximum number of non-intersecting substrings of word that are at least four characters long and start and end with the same letter.
#
# Example:
# Input: word = "abcdeafdef"
#
# Output: 2
#
# Explanation:
#
# The two substrings are "abcdea" and "fdef".
#
# Constraints:
# 1 <= word.length <= 2 * 105
# 	word consists only of lowercase English letters.
#

class Solution(object):
    def maxSubstrings(self, word):
        """
        :type word: str
        :rtype: int
        """
        n = len(word)
        intervals = []
        
        # Find all valid substrings
        for i in range(n):
            for j in range(i + 3, n):
                if word[i] == word[j]:
                    intervals.append((i, j))
        
        # Sort intervals by their ending index
        intervals.sort(key=lambda x: x[1])
        
        count = 0
        last_end = -1
        
        # Select non-intersecting substrings using a greedy approach
        for start, end in intervals:
            if start > last_end:
                count += 1
                last_end = end
        
        return count