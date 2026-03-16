# Source: https://leetcode.com/problems/unique-morse-code-words/   |   Difficulty: Easy
#
# Problem Description:
# International Morse Code defines a standard encoding where each letter is mapped to a series of dots and dashes, as follows:
#
#
# 	'a' maps to ".-",
# 	'b' maps to "-...",
# 	'c' maps to "-.-.", and so on.
#
#
# For convenience, the full table for the 26 letters of the English alphabet is given below:
#
#
# [".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]
#
# Given an array of strings words where each word can be written as a concatenation of the Morse code of each letter.
#
#
# 	For example, "cab" can be written as "-.-..--...", which is the concatenation of "-.-.", ".-", and "-...". We will call such a concatenation the transformation of a word.
#
#
# Return the number of different transformations among all words we have.
#
# Example:
# Input: words = ["gin","zen","gig","msg"]
# Output: 2
# Explanation: The transformation of each word is:
# "gin" -> "--...-."
# "zen" -> "--...-."
# "gig" -> "--...--."
# "msg" -> "--...--."
# There are 2 different transformations: "--...-." and "--...--.".
#
# Constraints:
# 1 <= words.length <= 100
# 	1 <= words[i].length <= 12
# 	words[i] consists of lowercase English letters.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def uniqueMorseRepresentations(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        morse_code = [".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
                      "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
                      "..-","...-",".--","-..-","-.--","--.."]

        transformations = set()

        for word in words:
            transformation = ''.join(morse_code[ord(char) - ord('a')] for char in word)
            transformations.add(transformation)

        return len(transformations)