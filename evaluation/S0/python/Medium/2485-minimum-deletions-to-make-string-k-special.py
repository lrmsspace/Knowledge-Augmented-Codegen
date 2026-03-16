# Source: https://leetcode.com/problems/minimum-deletions-to-make-string-k-special/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string word and an integer k.
#
# We consider word to be k-special if |freq(word[i]) - freq(word[j])| <= k for all indices i and j in the string.
#
# Here, freq(x) denotes the frequency of the character x in word, and |y| denotes the absolute value of y.
#
# Return the minimum number of characters you need to delete to make word k-special.
#
# Example:
# Input: word = "aabcaba", k = 0
#
# Output: 3
#
# Explanation: We can make word 0-special by deleting 2 occurrences of "a" and 1 occurrence of "c". Therefore, word becomes equal to "baba" where freq('a') == freq('b') == 2.
#
# Constraints:
# 1 <= word.length <= 105
# 	0 <= k <= 105
# 	word consists only of lowercase English letters.
#

class Solution(object):
    def minimumDeletions(self, word, k):
        """
        :type word: str
        :type k: int
        :rtype: int
        """
        from collections import Counter
        freq = Counter(word)
        freq_values = list(freq.values())
        max_freq = max(freq_values)
        min_deletions = float('inf')

        for target_freq in range(1, max_freq + 1):
            deletions = 0
            for f in freq_values:
                if abs(f - target_freq) > k:
                    if f > target_freq:
                        deletions += f - (target_freq + k)
                    else:
                        deletions += f
            min_deletions = min(min_deletions, deletions)

        return min_deletions