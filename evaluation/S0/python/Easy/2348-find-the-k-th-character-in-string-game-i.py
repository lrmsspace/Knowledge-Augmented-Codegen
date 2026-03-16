# Source: https://leetcode.com/problems/find-the-k-th-character-in-string-game-i/   |   Difficulty: Easy
#
# Problem Description:
# Alice and Bob are playing a game. Initially, Alice has a string word = "a".
#
# You are given a positive integer k.
#
# Now Bob will ask Alice to perform the following operation forever:
#
#
# 	Generate a new string by changing each character in word to its next character in the English alphabet, and append it to the original word.
#
#
# For example, performing the operation on "c" generates "cd" and performing the operation on "zb" generates "zbac".
#
# Return the value of the kth character in word, after enough operations have been done for word to have at least k characters.
#
# Example:
# Input: k = 5
#
# Output: "b"
#
# Explanation:
#
# Initially, word = "a". We need to do the operation three times:
#
#
# 	Generated string is "b", word becomes "ab".
# 	Generated string is "bc", word becomes "abbc".
# 	Generated string is "bccd", word becomes "abbcbccd".
#
# Constraints:
# 1 <= k <= 500
#

class Solution(object):
    def kthCharacter(self, k):
        """
        :type k: int
        :rtype: str
        """
        word = "a"
        while len(word) < k:
            next_part = ''.join(chr(((ord(c) - ord('a') + 1) % 26) + ord('a')) for c in word)
            word += next_part
        return word[k - 1]