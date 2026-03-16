# Source: https://leetcode.com/problems/closest-dessert-cost/   |   Difficulty: Medium
#
# Problem Description:
# You would like to make dessert and are preparing to buy the ingredients. You have n ice cream base flavors and m types of toppings to choose from. You must follow these rules when making your dessert:
#
#
# 	There must be exactly one ice cream base.
# 	You can add one or more types of topping or have no toppings at all.
# 	There are at most two of each type of topping.
#
#
# You are given three inputs:
#
#
# 	baseCosts, an integer array of length n, where each baseCosts[i] represents the price of the ith ice cream base flavor.
# 	toppingCosts, an integer array of length m, where each toppingCosts[i] is the price of one of the ith topping.
# 	target, an integer representing your target price for dessert.
#
#
# You want to make a dessert with a total cost as close to target as possible.
#
# Return the closest possible cost of the dessert to target. If there are multiple, return the lower one.
#
# Example:
# Input: baseCosts = [1,7], toppingCosts = [3,4], target = 10
# Output: 10
# Explanation: Consider the following combination (all 0-indexed):
# - Choose base 1: cost 7
# - Take 1 of topping 0: cost 1 x 3 = 3
# - Take 0 of topping 1: cost 0 x 4 = 0
# Total: 7 + 3 + 0 = 10.
#
# Constraints:
# n == baseCosts.length
# 	m == toppingCosts.length
# 	1 <= n, m <= 10
# 	1 <= baseCosts[i], toppingCosts[i] <= 104
# 	1 <= target <= 104
#

class Solution(object):
    def closestCost(self, baseCosts, toppingCosts, target):
        """
        :type baseCosts: List[int]
        :type toppingCosts: List[int]
        :type target: int
        :rtype: int
        """
        possible_costs = set()

        def backtrack(topping_index, current_cost):
            if topping_index == len(toppingCosts):
                possible_costs.add(current_cost)
                return

            # 0 of this topping
            backtrack(topping_index + 1, current_cost)

            # 1 of this topping
            backtrack(topping_index + 1, current_cost + toppingCosts[topping_index])

            # 2 of this topping
            backtrack(topping_index + 1, current_cost + 2 * toppingCosts[topping_index])

        for base in baseCosts:
            backtrack(0, base)

        closest = None
        for cost in possible_costs:
            if closest is None or abs(cost - target) < abs(closest - target) or (abs(cost - target) == abs(closest - target) and cost < closest):
                closest = cost

        return closest