# Source: https://leetcode.com/problems/water-bottles-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integers numBottles and numExchange.
#
# numBottles represents the number of full water bottles that you initially have. In one operation, you can perform one of the following operations:
#
#
# 	Drink any number of full water bottles turning them into empty bottles.
# 	Exchange numExchange empty bottles with one full water bottle. Then, increase numExchange by one.
#
#
# Note that you cannot exchange multiple batches of empty bottles for the same value of numExchange. For example, if numBottles == 3 and numExchange == 1, you cannot exchange 3 empty water bottles for 3 full bottles.
#
# Return the maximum number of water bottles you can drink.
#
# Example:
# Input: numBottles = 13, numExchange = 6
# Output: 15
# Explanation: The table above shows the number of full water bottles, empty water bottles, the value of numExchange, and the number of bottles drunk.
#
# Constraints:
# 1 <= numBottles <= 100 
# 	1 <= numExchange <= 100
#

class Solution(object):
    def maxBottlesDrunk(self, numBottles, numExchange):
        """
        :type numBottles: int
        :type numExchange: int
        :rtype: int
        """
        total_drunk = 0
        empty_bottles = 0
        exchange_rate = numExchange

        while numBottles > 0:
            # Drink all full bottles
            total_drunk += numBottles
            empty_bottles += numBottles
            numBottles = 0

            # Exchange empty bottles for full ones
            while empty_bottles >= exchange_rate:
                new_full = empty_bottles // exchange_rate
                numBottles += new_full
                empty_bottles -= new_full * exchange_rate
                exchange_rate += 1

        return total_drunk