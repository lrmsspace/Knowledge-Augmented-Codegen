# Source: https://leetcode.com/problems/compare-strings-by-frequency-of-the-smallest-character/   |   Difficulty: Medium
#
# Problem Description:
# Let the function f(s) be the frequency of the lexicographically smallest character in a non-empty string s. For example, if s = "dcce" then f(s) = 2 because the lexicographically smallest character is 'c', which has a frequency of 2.
#
# You are given an array of strings words and another array of query strings queries. For each query queries[i], count the number of words in words such that f(queries[i]) < f(W) for each W in words.
#
# Return an integer array answer, where each answer[i] is the answer to the ith query.
#
# Example:
# Input: queries = ["cbd"], words = ["zaaaz"]
# Output: [1]
# Explanation: On the first query we have f("cbd") = 1, f("zaaaz") = 3 so f("cbd") < f("zaaaz").
#
# Constraints:
# 1 <= queries.length <= 2000
# 	1 <= words.length <= 2000
# 	1 <= queries[i].length, words[i].length <= 10
# 	queries[i][j], words[i][j] consist of lowercase English letters.
#

class Solution(object):
    def numSmallerByFrequency(self, queries, words):
        """
        :type queries: List[str]
        :type words: List[str]
        :rtype: List[int]
        """
        def f(s):
            smallest_char = min(s)
            return s.count(smallest_char)

        word_freqs = sorted([f(word) for word in words])
        result = []

        for query in queries:
            query_freq = f(query)
            count = 0
            for word_freq in word_freqs:
                if query_freq < word_freq:
                    count += 1
            result.append(count)

        return result