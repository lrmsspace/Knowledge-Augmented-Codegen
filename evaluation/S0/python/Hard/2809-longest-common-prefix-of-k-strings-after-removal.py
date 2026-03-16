# Source: https://leetcode.com/problems/longest-common-prefix-of-k-strings-after-removal/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array of strings words and an integer k.
#
# For each index i in the range [0, words.length - 1], find the length of the longest common prefix among any k strings (selected at distinct indices) from the remaining array after removing the ith element.
#
# Return an array answer, where answer[i] is the answer for ith element. If removing the ith element leaves the array with fewer than k strings, answer[i] is 0.
#
# Example:
# Input: words = ["jump","run","run","jump","run"], k = 2
#
# Output: [3,4,4,3,4]
#
# Explanation:
#
#
# 	Removing index 0 ("jump"):
#
# 	
# 		words becomes: ["run", "run", "jump", "run"]. "run" occurs 3 times. Choosing any two gives the longest common prefix "run" (length 3).
# 	
# 	
# 	Removing index 1 ("run"):
# 	
# 		words becomes: ["jump", "run", "jump", "run"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).
# 	
# 	
# 	Removing index 2 ("run"):
# 	
# 		words becomes: ["jump", "run", "jump", "run"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).
# 	
# 	
# 	Removing index 3 ("jump"):
# 	
# 		words becomes: ["jump", "run", "run", "run"]. "run" occurs 3 times. Choosing any two gives the longest common prefix "run" (length 3).
# 	
# 	
# 	Removing index 4 ("run"):
# 	
# 		words becomes: ["jump", "run", "run", "jump"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).
#
# Constraints:
# 1 <= k <= words.length <= 105
# 	1 <= words[i].length <= 104
# 	words[i] consists of lowercase English letters.
# 	The sum of words[i].length is smaller than or equal 105.
#

class Solution(object):
    def longestCommonPrefix(self, words, k):
        """
        :type words: List[str]
        :type k: int
        :rtype: List[int]
        """
        from collections import defaultdict, Counter

        n = len(words)
        if n < k:
            return [0] * n

        prefix_count = defaultdict(int)
        for word in words:
            for l in range(1, len(word) + 1):
                prefix_count[word[:l]] += 1

        result = []
        for i in range(n):
            temp_count = prefix_count.copy()
            word = words[i]
            for l in range(1, len(word) + 1):
                temp_count[word[:l]] -= 1

            max_len = 0
            for prefix, count in temp_count.items():
                if count >= k:
                    max_len = max(max_len, len(prefix))

            result.append(max_len)

        return result