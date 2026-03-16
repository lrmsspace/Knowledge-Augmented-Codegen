# Source: https://leetcode.com/problems/x-of-a-kind-in-a-deck-of-cards/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array deck where deck[i] represents the number written on the ith card.
#
# Partition the cards into one or more groups such that:
#
#
# 	Each group has exactly x cards where x > 1, and
# 	All the cards in one group have the same integer written on them.
#
#
# Return true if such partition is possible, or false otherwise.
#
# Example:
# Input: deck = [1,2,3,4,4,3,2,1]
# Output: true
# Explanation: Possible partition [1,1],[2,2],[3,3],[4,4].
#
# Constraints:
# 1 <= deck.length <= 104
# 	0 <= deck[i] < 104
#

class Solution(object):
    def hasGroupsSizeX(self, deck):
        """
        :type deck: List[int]
        :rtype: bool
        """
        from collections import Counter
        from math import gcd
        from functools import reduce

        count = Counter(deck)
        counts = list(count.values())
        x = reduce(gcd, counts)
        return x >= 2