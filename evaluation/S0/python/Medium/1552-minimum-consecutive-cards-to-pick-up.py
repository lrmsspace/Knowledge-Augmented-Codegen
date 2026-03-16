# Source: https://leetcode.com/problems/minimum-consecutive-cards-to-pick-up/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array cards where cards[i] represents the value of the ith card. A pair of cards are matching if the cards have the same value.
#
# Return the minimum number of consecutive cards you have to pick up to have a pair of matching cards among the picked cards. If it is impossible to have matching cards, return -1.
#
# Example:
# Input: cards = [3,4,2,3,4,7]
# Output: 4
# Explanation: We can pick up the cards [3,4,2,3] which contain a matching pair of cards with value 3. Note that picking up the cards [4,2,3,4] is also optimal.
#
# Constraints:
# 1 <= cards.length <= 105
# 	0 <= cards[i] <= 106
#

class Solution(object):
    def minimumCardPickup(self, cards):
        """
        :type cards: List[int]
        :rtype: int
        """
        index_map = {}
        min_length = float('inf')

        for i, card in enumerate(cards):
            if card in index_map:
                prev_index = index_map[card]
                current_length = i - prev_index + 1
                min_length = min(min_length, current_length)
            index_map[card] = i

        return min_length if min_length != float('inf') else -1