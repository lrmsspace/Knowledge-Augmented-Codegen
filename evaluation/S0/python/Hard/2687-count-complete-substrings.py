# Source: https://leetcode.com/problems/count-complete-substrings/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string word and an integer k.
#
# A substring s of word is complete if:
#
#
# 	Each character in s occurs exactly k times.
# 	The difference between two adjacent characters is at most 2. That is, for any two adjacent characters c1 and c2 in s, the absolute difference in their positions in the alphabet is at most 2.
#
#
# Return the number of complete substrings of word.
#
# A substring is a non-empty contiguous sequence of characters in a string.
#
# Example:
# Input: word = "igigee", k = 2
# Output: 3
# Explanation: The complete substrings where each character appears exactly twice and the difference between adjacent characters is at most 2 are: igigee, igigee, igigee.
#
# Constraints:
# 1 <= word.length <= 105
# 	word consists only of lowercase English letters.
# 	1 <= k <= word.length
#

class Solution(object):
    def countCompleteSubstrings(self, word, k):
        """
        :type word: str
        :type k: int
        :rtype: int
        """
        from collections import defaultdict

        n = len(word)
        result = 0

        for i in range(n):
            freq = defaultdict(int)
            max_char = word[i]
            min_char = word[i]

            for j in range(i, n):
                freq[word[j]] += 1
                max_char = max(max_char, word[j])
                min_char = min(min_char, word[j])

                if max_char > chr(ord(min_char) + 2):
                    break

                if all(count == k for count in freq.values()):
                    result += 1

        return result