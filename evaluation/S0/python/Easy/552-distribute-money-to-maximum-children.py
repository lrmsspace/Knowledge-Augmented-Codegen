# Source: https://leetcode.com/problems/distribute-money-to-maximum-children/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer money denoting the amount of money (in dollars) that you have and another integer children denoting the number of children that you must distribute the money to.
#
# You have to distribute the money according to the following rules:
#
#
# 	All money must be distributed.
# 	Everyone must receive at least 1 dollar.
# 	Nobody receives 4 dollars.
#
#
# Return the maximum number of children who may receive exactly 8 dollars if you distribute the money according to the aforementioned rules. If there is no way to distribute the money, return -1.
#
# Example:
# Input: money = 20, children = 3
# Output: 1
# Explanation: 
# The maximum number of children with 8 dollars will be 1. One of the ways to distribute the money is:
# - 8 dollars to the first child.
# - 9 dollars to the second child. 
# - 3 dollars to the third child.
# It can be proven that no distribution exists such that number of children getting 8 dollars is greater than 1.
#
# Constraints:
# 1 <= money <= 200
# 	2 <= children <= 30
#

class Solution(object):
    def distMoney(self, money, children):
        """
        :type money: int
        :type children: int
        :rtype: int
        """
        if money < children:
            return -1
        
        max_eight = money // 8
        if max_eight >= children:
            if money - children * 8 == 4:
                return children - 1
            return children
        
        remaining_money = money - max_eight * 8
        remaining_children = children - max_eight
        
        if remaining_money == remaining_children * 4:
            return max_eight - 1
        
        return max_eight