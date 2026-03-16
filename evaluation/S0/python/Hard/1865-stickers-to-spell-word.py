# Source: https://leetcode.com/problems/stickers-to-spell-word/   |   Difficulty: Hard
#
# Problem Description:
# We are given n different types of stickers. Each sticker has a lowercase English word on it.
#
# You would like to spell out the given string target by cutting individual letters from your collection of stickers and rearranging them. You can use each sticker more than once if you want, and you have infinite quantities of each sticker.
#
# Return the minimum number of stickers that you need to spell out target. If the task is impossible, return -1.
#
# Note: In all test cases, all words were chosen randomly from the 1000 most common US English words, and target was chosen as a concatenation of two random words.
#
# Example:
# Input: stickers = ["with","example","science"], target = "thehat"
# Output: 3
# Explanation:
# We can use 2 "with" stickers, and 1 "example" sticker.
# After cutting and rearrange the letters of those stickers, we can form the target "thehat".
# Also, this is the minimum number of stickers necessary to form the target string.
#
# Constraints:
# n == stickers.length
# 	1 <= n <= 50
# 	1 <= stickers[i].length <= 10
# 	1 <= target.length <= 15
# 	stickers[i] and target consist of lowercase English letters.
#

class Solution(object):
    def minStickers(self, stickers, target):
        """
        :type stickers: List[str]
        :type target: str
        :rtype: int
        """
        from collections import Counter
        m = len(stickers)
        sticker_counts = [Counter(sticker) for sticker in stickers]
        memo = {}

        def dp(remaining):
            if remaining in memo:
                return memo[remaining]
            if not remaining:
                return 0

            remaining_count = Counter(remaining)
            min_stickers = float('inf')

            for sticker_count in sticker_counts:
                if sticker_count[remaining[0]] == 0:
                    continue

                new_remaining = []
                for char in remaining_count:
                    if remaining_count[char] > sticker_count[char]:
                        new_remaining.append(char * (remaining_count[char] - sticker_count[char]))
                new_remaining_str = ''.join(new_remaining)

                stickers_needed = dp(new_remaining_str)
                if stickers_needed != -1:
                    min_stickers = min(min_stickers, 1 + stickers_needed)

            memo[remaining] = -1 if min_stickers == float('inf') else min_stickers
            return memo[remaining]

        return dp(target)