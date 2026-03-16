# Source: https://leetcode.com/problems/construct-string-with-minimum-cost/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string target, an array of strings words, and an integer array costs, both arrays of the same length.
#
# Imagine an empty string s.
#
# You can perform the following operation any number of times (including zero):
#
#
# 	Choose an index i in the range [0, words.length - 1].
# 	Append words[i] to s.
# 	The cost of operation is costs[i].
#
#
# Return the minimum cost to make s equal to target. If it's not possible, return -1.
#
# Example:
# Input: target = "abcdef", words = ["abdef","abc","d","def","ef"], costs = [100,1,1,10,5]
#
# Output: 7
#
# Explanation:
#
# The minimum cost can be achieved by performing the following operations:
#
#
# 	Select index 1 and append "abc" to s at a cost of 1, resulting in s = "abc".
# 	Select index 2 and append "d" to s at a cost of 1, resulting in s = "abcd".
# 	Select index 4 and append "ef" to s at a cost of 5, resulting in s = "abcdef".
#
# Constraints:
# 1 <= target.length <= 5 * 104
# 	1 <= words.length == costs.length <= 5 * 104
# 	1 <= words[i].length <= target.length
# 	The total sum of words[i].length is less than or equal to 5 * 104.
# 	target and words[i] consist only of lowercase English letters.
# 	1 <= costs[i] <= 104
#

class Solution(object):
    def minimumCost(self, target, words, costs):
        """
        :type target: str
        :type words: List[str]
        :type costs: List[int]
        :rtype: int
        """
        n = len(target)
        dp = [float('inf')] * (n + 1)
        dp[0] = 0

        word_cost_map = {}
        for word, cost in zip(words, costs):
            if word not in word_cost_map or cost < word_cost_map[word]:
                word_cost_map[word] = cost

        for i in range(1, n + 1):
            for word, cost in word_cost_map.items():
                word_len = len(word)
                if i >= word_len and target[i - word_len:i] == word:
                    dp[i] = min(dp[i], dp[i - word_len] + cost)

        return dp[n] if dp[n] != float('inf') else -1