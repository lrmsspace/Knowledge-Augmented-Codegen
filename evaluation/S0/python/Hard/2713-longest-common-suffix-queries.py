# Source: https://leetcode.com/problems/longest-common-suffix-queries/   |   Difficulty: Hard
#
# Problem Description:
# You are given two arrays of strings wordsContainer and wordsQuery.
#
# For each wordsQuery[i], you need to find a string from wordsContainer that has the longest common suffix with wordsQuery[i]. If there are two or more strings in wordsContainer that share the longest common suffix, find the string that is the smallest in length. If there are two or more such strings that have the same smallest length, find the one that occurred earlier in wordsContainer.
#
# Return an array of integers ans, where ans[i] is the index of the string in wordsContainer that has the longest common suffix with wordsQuery[i].
#
# Example:
# Input: wordsContainer = ["abcd","bcd","xbcd"], wordsQuery = ["cd","bcd","xyz"]
#
# Output: [1,1,1]
#
# Explanation:
#
# Let's look at each wordsQuery[i] separately:
#
#
# 	For wordsQuery[0] = "cd", strings from wordsContainer that share the longest common suffix "cd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
# 	For wordsQuery[1] = "bcd", strings from wordsContainer that share the longest common suffix "bcd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
# 	For wordsQuery[2] = "xyz", there is no string from wordsContainer that shares a common suffix. Hence the longest common suffix is "", that is shared with strings at index 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
#
# Constraints:
# 1 <= wordsContainer.length, wordsQuery.length <= 104
# 	1 <= wordsContainer[i].length <= 5 * 103
# 	1 <= wordsQuery[i].length <= 5 * 103
# 	wordsContainer[i] consists only of lowercase English letters.
# 	wordsQuery[i] consists only of lowercase English letters.
# 	Sum of wordsContainer[i].length is at most 5 * 105.
# 	Sum of wordsQuery[i].length is at most 5 * 105.
#

class Solution(object):
    def stringIndices(self, wordsContainer, wordsQuery):
        """
        :type wordsContainer: List[str]
        :type wordsQuery: List[str]
        :rtype: List[int]
        """
        from collections import defaultdict

        suffix_map = defaultdict(list)

        for index, word in enumerate(wordsContainer):
            for i in range(len(word)):
                suffix = word[i:]
                suffix_map[suffix].append((len(word), index))

        result = []

        for query in wordsQuery:
            max_suffix_length = -1
            best_index = -1

            for i in range(len(query)):
                suffix = query[i:]
                if suffix in suffix_map:
                    if len(suffix) > max_suffix_length:
                        max_suffix_length = len(suffix)
                        candidates = suffix_map[suffix]
                        candidates.sort()
                        best_index = candidates[0][1]

            if best_index == -1:
                candidates = [(len(word), idx) for idx, word in enumerate(wordsContainer)]
                candidates.sort()
                best_index = candidates[0][1]

            result.append(best_index)

        return result