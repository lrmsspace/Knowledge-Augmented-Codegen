# Source: https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/   |   Difficulty: Medium
#
# Problem Description:
# Given the string s, return the size of the longest substring containing each vowel an even number of times. That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.
#
# Example:
# Input: s = "eleetminicoworoep"
# Output: 13
# Explanation: The longest substring is "leetminicowor" which contains two each of the vowels: e, i and o and zero of the vowels: a and u.
#
# Constraints:
# 1 <= s.length <= 5 x 10^5
# 	s contains only lowercase English letters.
#

class Solution(object):
    def findTheLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        vowel_to_bit = {'a': 1, 'e': 2, 'i': 4, 'o': 8, 'u': 16}
        state = 0
        state_to_index = {0: -1}
        max_length = 0
        
        for i, char in enumerate(s):
            if char in vowel_to_bit:
                state ^= vowel_to_bit[char]
            
            if state in state_to_index:
                max_length = max(max_length, i - state_to_index[state])
            else:
                state_to_index[state] = i
        
        return max_length