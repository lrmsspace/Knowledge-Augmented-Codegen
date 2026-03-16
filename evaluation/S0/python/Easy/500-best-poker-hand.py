# Source: https://leetcode.com/problems/best-poker-hand/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array ranks and a character array suits. You have 5 cards where the ith card has a rank of ranks[i] and a suit of suits[i].
#
# The following are the types of poker hands you can make from best to worst:
#
#
# 	"Flush": Five cards of the same suit.
# 	"Three of a Kind": Three cards of the same rank.
# 	"Pair": Two cards of the same rank.
# 	"High Card": Any single card.
#
#
# Return a string representing the best type of poker hand you can make with the given cards.
#
# Note that the return values are case-sensitive.
#
# Example:
# Input: ranks = [13,2,3,1,9], suits = ["a","a","a","a","a"]
# Output: "Flush"
# Explanation: The hand with all the cards consists of 5 cards with the same suit, so we have a "Flush".
#
# Constraints:
# ranks.length == suits.length == 5
# 	1 <= ranks[i] <= 13
# 	'a' <= suits[i] <= 'd'
# 	No two cards have the same rank and suit.
#

class Solution(object):
    def bestHand(self, ranks, suits):
        """
        :type ranks: List[int]
        :type suits: List[str]
        :rtype: str
        """
        if len(set(suits)) == 1:
            return "Flush"
        
        rank_count = {}
        for rank in ranks:
            rank_count[rank] = rank_count.get(rank, 0) + 1
        
        if any(count >= 3 for count in rank_count.values()):
            return "Three of a Kind"
        
        if any(count == 2 for count in rank_count.values()):
            return "Pair"
        
        return "High Card"