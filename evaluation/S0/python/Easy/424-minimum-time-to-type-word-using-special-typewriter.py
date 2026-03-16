# Source: https://leetcode.com/problems/minimum-time-to-type-word-using-special-typewriter/   |   Difficulty: Easy
#
# Problem Description:
# There is a special typewriter with lowercase English letters 'a' to 'z' arranged in a circle with a pointer. A character can only be typed if the pointer is pointing to that character. The pointer is initially pointing to the character 'a'.
#
# Each second, you may perform one of the following operations:
#
#
# 	Move the pointer one character counterclockwise or clockwise.
# 	Type the character the pointer is currently on.
#
#
# Given a string word, return the minimum number of seconds to type out the characters in word.
#
# Example:
# Input: word = "abc"
# Output: 5
# Explanation: 
# The characters are printed as follows:
# - Type the character 'a' in 1 second since the pointer is initially on 'a'.
# - Move the pointer clockwise to 'b' in 1 second.
# - Type the character 'b' in 1 second.
# - Move the pointer clockwise to 'c' in 1 second.
# - Type the character 'c' in 1 second.
#
# Constraints:
# 1 <= word.length <= 100
# 	word consists of lowercase English letters.
#

class Solution(object):
    def minTimeToType(self, word):
        """
        :type word: str
        :rtype: int
        """
        total_time = 0
        current_pos = ord('a')

        for char in word:
            target_pos = ord(char)
            clockwise_dist = abs(target_pos - current_pos)
            counterclockwise_dist = 26 - clockwise_dist
            total_time += min(clockwise_dist, counterclockwise_dist) + 1  # +1 for typing the character
            current_pos = target_pos

        return total_time