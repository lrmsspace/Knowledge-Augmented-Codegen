# Source: https://leetcode.com/problems/jewels-and-stones/   |   Difficulty: Easy
#
# Problem Description:
# You're given strings jewels representing the types of stones that are jewels, and stones representing the stones you have. Each character in stones is a type of stone you have. You want to know how many of the stones you have are also jewels.
#
# Letters are case sensitive, so "a" is considered a different type of stone from "A".
#
# Example:
# Input: jewels = "aA", stones = "aAAbbbb"
# Output: 3
#
# Constraints:
# 1 <= jewels.length, stones.length <= 50
# 	jewels and stones consist of only English letters.
# 	All the characters of jewels are unique.
#

class Solution(object):
    def numJewelsInStones(self, jewels, stones):
        """
        :type jewels: str
        :type stones: str
        :rtype: int
        """
        jewel_set = set(jewels)
        count = 0
        for stone in stones:
            if stone in jewel_set:
                count += 1
        return count