# Source: https://leetcode.com/problems/decode-the-message/   |   Difficulty: Easy
#
# Problem Description:
# You are given the strings key and message, which represent a cipher key and a secret message, respectively. The steps to decode message are as follows:
#
#
# 	Use the first appearance of all 26 lowercase English letters in key as the order of the substitution table.
# 	Align the substitution table with the regular English alphabet.
# 	Each letter in message is then substituted using the table.
# 	Spaces ' ' are transformed to themselves.
#
#
#
# 	For example, given key = "happy boy" (actual key would have at least one instance of each letter in the alphabet), we have the partial substitution table of ('h' -> 'a', 'a' -> 'b', 'p' -> 'c', 'y' -> 'd', 'b' -> 'e', 'o' -> 'f').
#
#
# Return the decoded message.
#
# Example:
# Input: key = "the quick brown fox jumps over the lazy dog", message = "vkbs bs t suepuv"
# Output: "this is a secret"
# Explanation: The diagram above shows the substitution table.
# It is obtained by taking the first appearance of each letter in "the quick brown fox jumps over the lazy dog".
#
# Constraints:
# 26 <= key.length <= 2000
# 	key consists of lowercase English letters and ' '.
# 	key contains every letter in the English alphabet ('a' to 'z') at least once.
# 	1 <= message.length <= 2000
# 	message consists of lowercase English letters and ' '.
#

class Solution(object):
    def decodeMessage(self, key, message):
        """
        :type key: str
        :type message: str
        :rtype: str
        """
        mapping = {}
        current_char = 'a'
        
        for char in key:
            if char != ' ' and char not in mapping:
                mapping[char] = current_char
                current_char = chr(ord(current_char) + 1)
        
        decoded_message = []
        for char in message:
            if char == ' ':
                decoded_message.append(' ')
            else:
                decoded_message.append(mapping[char])
        
        return ''.join(decoded_message)