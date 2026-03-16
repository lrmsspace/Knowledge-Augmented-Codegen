# Source: https://leetcode.com/problems/plates-between-candles/   |   Difficulty: Medium
#
# Problem Description:
# There is a long table with a line of plates and candles arranged on top of it. You are given a 0-indexed string s consisting of characters '*' and '|' only, where a '*' represents a plate and a '|' represents a candle.
#
# You are also given a 0-indexed 2D integer array queries where queries[i] = [lefti, righti] denotes the substring s[lefti...righti] (inclusive). For each query, you need to find the number of plates between candles that are in the substring. A plate is considered between candles if there is at least one candle to its left and at least one candle to its right in the substring.
#
#
# 	For example, s = "||**||**|*", and a query [3, 8] denotes the substring "*||**|". The number of plates between candles in this substring is 2, as each of the two plates has at least one candle in the substring to its left and right.
#
#
# Return an integer array answer where answer[i] is the answer to the ith query.
#
# Example:
# Input: s = "**|**|***|", queries = [[2,5],[5,9]]
# Output: [2,3]
# Explanation:
# - queries[0] has two plates between candles.
# - queries[1] has three plates between candles.
#
# Constraints:
# 3 <= s.length <= 105
# 	s consists of '*' and '|' characters.
# 	1 <= queries.length <= 105
# 	queries[i].length == 2
# 	0 <= lefti <= righti < s.length
#

class Solution(object):
    def platesBetweenCandles(self, s, queries):
        """
        :type s: str
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        n = len(s)
        prefix = [0] * (n + 1)
        left_candle = [-1] * n
        right_candle = [-1] * n

        count = 0
        last_candle = -1
        for i in range(n):
            if s[i] == '|':
                last_candle = i
            else:
                count += 1
            prefix[i + 1] = count
            left_candle[i] = last_candle

        last_candle = -1
        for i in range(n - 1, -1, -1):
            if s[i] == '|':
                last_candle = i
            right_candle[i] = last_candle

        result = []
        for left, right in queries:
            left_bound = right_candle[left]
            right_bound = left_candle[right]
            if left_bound != -1 and right_bound != -1 and left_bound < right_bound:
                result.append(prefix[right_bound + 1] - prefix[left_bound + 1])
            else:
                result.append(0)

        return result