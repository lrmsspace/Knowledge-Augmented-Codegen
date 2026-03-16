# Source: https://leetcode.com/problems/swap-for-longest-repeated-character-substring/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string text. You can swap two of the characters in the text.
#
# Return the length of the longest substring with repeated characters.
#
# Example:
# Input: text = "ababa"
# Output: 3
# Explanation: We can swap the first 'b' with the last 'a', or the last 'b' with the first 'a'. Then, the longest repeated character substring is "aaa" with length 3.
#
# Constraints:
# 1 <= text.length <= 2 * 104
# 	text consist of lowercase English characters only.
#

class Solution(object):
    def maxRepOpt1(self, text):
        """
        :type text: str
        :rtype: int
        """
        from collections import Counter

        count = Counter(text)
        max_len = 0
        n = len(text)

        i = 0
        while i < n:
            j = i
            while j < n and text[j] == text[i]:
                j += 1
            current_len = j - i

            # Check for the case where we can swap one character to extend the substring
            if current_len < count[text[i]]:
                max_len = max(max_len, current_len + 1)
            else:
                max_len = max(max_len, current_len)

            # Check for the case where there's a single different character in between
            k = j + 1
            while k < n and text[k] == text[i]:
                k += 1
            if k - j == 1:  # There's exactly one different character
                combined_len = (j - i) + (k - j - 1)
                if combined_len < count[text[i]]:
                    max_len = max(max_len, combined_len + 1)
                else:
                    max_len = max(max_len, combined_len)

            i = j

        return max_len