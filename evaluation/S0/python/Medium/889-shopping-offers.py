# Source: https://leetcode.com/problems/shopping-offers/   |   Difficulty: Medium
#
# Problem Description:
# In LeetCode Store, there are n items to sell. Each item has a price. However, there are some special offers, and a special offer consists of one or more different kinds of items with a sale price.
#
# You are given an integer array price where price[i] is the price of the ith item, and an integer array needs where needs[i] is the number of pieces of the ith item you want to buy.
#
# You are also given an array special where special[i] is of size n + 1 where special[i][j] is the number of pieces of the jth item in the ith offer and special[i][n] (i.e., the last integer in the array) is the price of the ith offer.
#
# Return the lowest price you have to pay for exactly certain items as given, where you could make optimal use of the special offers. You are not allowed to buy more items than you want, even if that would lower the overall price. You could use any of the special offers as many times as you want.
#
# Example:
# Input: price = [2,5], special = [[3,0,5],[1,2,10]], needs = [3,2]
# Output: 14
# Explanation: There are two kinds of items, A and B. Their prices are $2 and $5 respectively. 
# In special offer 1, you can pay $5 for 3A and 0B
# In special offer 2, you can pay $10 for 1A and 2B. 
# You need to buy 3A and 2B, so you may pay $10 for 1A and 2B (special offer #2), and $4 for 2A.
#
# Constraints:
# n == price.length == needs.length
# 	1 <= n <= 6
# 	0 <= price[i], needs[i] <= 10
# 	1 <= special.length <= 100
# 	special[i].length == n + 1
# 	0 <= special[i][j] <= 50
# 	The input is generated that at least one of special[i][j] is non-zero for 0 <= j <= n - 1.
#

class Solution(object):
    def shoppingOffers(self, price, special, needs):
        """
        :type price: List[int]
        :type special: List[List[int]]
        :type needs: List[int]
        :rtype: int
        """
        from functools import lru_cache

        n = len(price)

        @lru_cache(None)
        def dfs(remaining):
            # Calculate the cost without any special offers
            cost = sum(remaining[i] * price[i] for i in range(n))

            # Try each special offer
            for offer in special:
                new_remaining = []
                for i in range(n):
                    if remaining[i] < offer[i]:
                        break
                    new_remaining.append(remaining[i] - offer[i])
                else:
                    # If the offer can be applied, calculate the cost recursively
                    cost = min(cost, offer[-1] + dfs(tuple(new_remaining)))

            return cost

        return dfs(tuple(needs))