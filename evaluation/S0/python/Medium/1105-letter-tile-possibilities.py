# Source: https://leetcode.com/problems/letter-tile-possibilities/   |   Difficulty: Medium
#
# Problem Description:
# You have n  tiles, where each tile has one letter tiles[i] printed on it.
#
# Return the number of possible non-empty sequences of letters you can make using the letters printed on those tiles.
#
# Example:
# Input: tiles = "AAB"
# Output: 8
# Explanation: The possible sequences are "A", "B", "AA", "AB", "BA", "AAB", "ABA", "BAA".
#
# Constraints:
# 1 <= tiles.length <= 7
# 	tiles consists of uppercase English letters.
#

class Solution(object):
    def numTilePossibilities(self, tiles):
        """
        :type tiles: str
        :rtype: int
        """
        from collections import Counter

        def backtrack(counter):
            total = 0
            for letter in counter:
                if counter[letter] > 0:
                    total += 1
                    counter[letter] -= 1
                    total += backtrack(counter)
                    counter[letter] += 1
            return total

        tile_count = Counter(tiles)
        return backtrack(tile_count)