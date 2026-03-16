# Source: https://leetcode.com/problems/minimum-time-to-revert-word-to-initial-state-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed string word and an integer k.
#
# At every second, you must perform the following operations:
#
#
# 	Remove the first k characters of word.
# 	Add any k characters to the end of word.
#
#
# Note that you do not necessarily need to add the same characters that you removed. However, you must perform both operations at every second.
#
# Return the minimum time greater than zero required for word to revert to its initial state.
#
# Example:
# Input: word = "abacaba", k = 3
# Output: 2
# Explanation: At the 1st second, we remove characters "aba" from the prefix of word, and add characters "bac" to the end of word. Thus, word becomes equal to "cababac".
# At the 2nd second, we remove characters "cab" from the prefix of word, and add "aba" to the end of word. Thus, word becomes equal to "abacaba" and reverts to its initial state.
# It can be shown that 2 seconds is the minimum time greater than zero required for word to revert to its initial state.
#
# Constraints:
# 1 <= word.length <= 50 
# 	1 <= k <= word.length
# 	word consists only of lowercase English letters.
#

class Solution(object):
    def minimumTimeToInitialState(self, word, k):
        """
        :type word: str
        :type k: int
        :rtype: int
        """
        n = len(word)
        time = 1
        current_word = word
        
        while True:
            # Remove first k characters and add any k characters to the end
            removed_part = current_word[:k]
            current_word = current_word[k:] + removed_part[::-1]  # Adding reversed removed part for variety
            
            if current_word == word:
                return time
            
            time += 1