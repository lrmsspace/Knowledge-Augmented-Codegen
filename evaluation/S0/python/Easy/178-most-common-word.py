# Source: https://leetcode.com/problems/most-common-word/   |   Difficulty: Easy
#
# Problem Description:
# Given a string paragraph and a string array of the banned words banned, return the most frequent word that is not banned. It is guaranteed there is at least one word that is not banned, and that the answer is unique.
#
# The words in paragraph are case-insensitive and the answer should be returned in lowercase.
#
# Note that words can not contain punctuation symbols.
#
# Example:
# Input: paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.", banned = ["hit"]
# Output: "ball"
# Explanation: 
# "hit" occurs 3 times, but it is a banned word.
# "ball" occurs twice (and no other word does), so it is the most frequent non-banned word in the paragraph. 
# Note that words in the paragraph are not case sensitive,
# that punctuation is ignored (even if adjacent to words, such as "ball,"), 
# and that "hit" isn't the answer even though it occurs more because it is banned.
#
# Constraints:
# 1 <= paragraph.length <= 1000
# 	paragraph consists of English letters, space ' ', or one of the symbols: "!?',;.".
# 	0 <= banned.length <= 100
# 	1 <= banned[i].length <= 10
# 	banned[i] consists of only lowercase English letters.
#

class Solution(object):
    def mostCommonWord(self, paragraph, banned):
        """
        :type paragraph: str
        :type banned: List[str]
        :rtype: str
        """
        import re
        from collections import Counter

        # Normalize the paragraph to lowercase and split into words
        words = re.findall(r'\w+', paragraph.lower())

        # Create a set of banned words for faster lookup
        banned_set = set(banned)

        # Count the frequency of each word that is not banned
        word_count = Counter(word for word in words if word not in banned_set)

        # Return the most common word
        return word_count.most_common(1)[0][0]