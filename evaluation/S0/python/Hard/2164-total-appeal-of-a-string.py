# Source: https://leetcode.com/problems/total-appeal-of-a-string/   |   Difficulty: Hard
#
# Problem Description:
# The appeal of a string is the number of distinct characters found in the string.
#
#
# 	For example, the appeal of "abbca" is 3 because it has 3 distinct characters: 'a', 'b', and 'c'.
#
#
# Given a string s, return the total appeal of all of its substrings.
#
# A substring is a contiguous sequence of characters within a string.
#
# Example:
# Input: s = "abbca"
# Output: 28
# Explanation: The following are the substrings of "abbca":
# - Substrings of length 1: "a", "b", "b", "c", "a" have an appeal of 1, 1, 1, 1, and 1 respectively. The sum is 5.
# - Substrings of length 2: "ab", "bb", "bc", "ca" have an appeal of 2, 1, 2, and 2 respectively. The sum is 7.
# - Substrings of length 3: "abb", "bbc", "bca" have an appeal of 2, 2, and 3 respectively. The sum is 7.
# - Substrings of length 4: "abbc", "bbca" have an appeal of 3 and 3 respectively. The sum is 6.
# - Substrings of length 5: "abbca" has an appeal of 3. The sum is 3.
# The total sum is 5 + 7 + 7 + 6 + 3 = 28.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of lowercase English letters.
#

class Solution(object):
    def appealSum(self, s):
        """
        :type s: str
        :rtype: int
        """
        last_occurrence = {}
        total_appeal = 0
        current_appeal = 0
        
        for i, char in enumerate(s):
            if char in last_occurrence:
                prev_index = last_occurrence[char]
                current_appeal += (i - prev_index)
            else:
                current_appeal += (i + 1)
            
            total_appeal += current_appeal
            last_occurrence[char] = i
        
        return total_appeal