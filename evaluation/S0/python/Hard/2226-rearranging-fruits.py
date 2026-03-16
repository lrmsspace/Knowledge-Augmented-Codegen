# Source: https://leetcode.com/problems/rearranging-fruits/   |   Difficulty: Hard
#
# Problem Description:
# You have two fruit baskets containing n fruits each. You are given two 0-indexed integer arrays basket1 and basket2 representing the cost of fruit in each basket. You want to make both baskets equal. To do so, you can use the following operation as many times as you want:
#
#
# 	Choose two indices i and j, and swap the ith fruit of basket1 with the jth fruit of basket2.
# 	The cost of the swap is min(basket1[i], basket2[j]).
#
#
# Two baskets are considered equal if sorting them according to the fruit cost makes them exactly the same baskets.
#
# Return the minimum cost to make both the baskets equal or -1 if impossible.
#
# Example:
# Input: basket1 = [4,2,2,2], basket2 = [1,4,1,2]
# Output: 1
# Explanation: Swap index 1 of basket1 with index 0 of basket2, which has cost 1. Now basket1 = [4,1,2,2] and basket2 = [2,4,1,2]. Rearranging both the arrays makes them equal.
#
# Constraints:
# basket1.length == basket2.length
# 	1 <= basket1.length <= 105
# 	1 <= basket1[i], basket2[i] <= 109
#

class Solution(object):
    def minCost(self, basket1, basket2):
        """
        :type basket1: List[int]
        :type basket2: List[int]
        :rtype: int
        """
        from collections import Counter
        count = Counter()
        for fruit in basket1:
            count[fruit] += 1
        for fruit in basket2:
            count[fruit] -= 1
        
        # Check if it's possible to make both baskets equal
        for freq in count.values():
            if freq % 2 != 0:
                return -1
        
        # Prepare for swaps
        to_swap = []
        for fruit, freq in count.items():
            if freq > 0:
                to_swap.extend([fruit] * (freq // 2))
        
        to_swap.sort()
        min_fruit = min(count.keys())
        
        total_cost = 0
        for i in range(len(to_swap) // 2):
            cost_direct = to_swap[i]
            cost_via_min = 2 * min_fruit
            total_cost += min(cost_direct, cost_via_min)
        
        return total_cost