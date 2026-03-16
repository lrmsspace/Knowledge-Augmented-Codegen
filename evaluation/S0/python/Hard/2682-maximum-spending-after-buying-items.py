# Source: https://leetcode.com/problems/maximum-spending-after-buying-items/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed m * n integer matrix values, representing the values of m * n different items in m different shops. Each shop has n items where the jth item in the ith shop has a value of values[i][j]. Additionally, the items in the ith shop are sorted in non-increasing order of value. That is, values[i][j] >= values[i][j + 1] for all 0 <= j < n - 1.
#
# On each day, you would like to buy a single item from one of the shops. Specifically, On the dth day you can:
#
#
# 	Pick any shop i.
# 	Buy the rightmost available item j for the price of values[i][j] * d. That is, find the greatest index j such that item j was never bought before, and buy it for the price of values[i][j] * d.
#
#
# Note that all items are pairwise different. For example, if you have bought item 0 from shop 1, you can still buy item 0 from any other shop.
#
# Return the maximum amount of money that can be spent on buying all  m * n products.
#
# Example:
# Input: values = [[8,5,2],[6,4,1],[9,7,3]]
# Output: 285
# Explanation: On the first day, we buy product 2 from shop 1 for a price of values[1][2] * 1 = 1.
# On the second day, we buy product 2 from shop 0 for a price of values[0][2] * 2 = 4.
# On the third day, we buy product 2 from shop 2 for a price of values[2][2] * 3 = 9.
# On the fourth day, we buy product 1 from shop 1 for a price of values[1][1] * 4 = 16.
# On the fifth day, we buy product 1 from shop 0 for a price of values[0][1] * 5 = 25.
# On the sixth day, we buy product 0 from shop 1 for a price of values[1][0] * 6 = 36.
# On the seventh day, we buy product 1 from shop 2 for a price of values[2][1] * 7 = 49.
# On the eighth day, we buy product 0 from shop 0 for a price of values[0][0] * 8 = 64.
# On the ninth day, we buy product 0 from shop 2 for a price of values[2][0] * 9 = 81.
# Hence, our total spending is equal to 285.
# It can be shown that 285 is the maximum amount of money that can be spent buying all m * n products.
#
# Constraints:
# 1 <= m == values.length <= 10
# 	1 <= n == values[i].length <= 104
# 	1 <= values[i][j] <= 106
# 	values[i] are sorted in non-increasing order.
#

class Solution(object):
    def maxSpending(self, values):
        """
        :type values: List[List[int]]
        :rtype: int
        """
        import heapq

        m, n = len(values), len(values[0])
        max_heap = []
        
        # Initialize the heap with the rightmost items from each shop
        for i in range(m):
            heapq.heappush(max_heap, (-values[i][n-1], i, n-1))
        
        total_spending = 0
        day = 1
        
        while max_heap:
            value, shop, index = heapq.heappop(max_heap)
            total_spending += -value * day
            
            # If there are more items in the same shop, add the next rightmost item to the heap
            if index > 0:
                heapq.heappush(max_heap, (-values[shop][index-1], shop, index-1))
            
            day += 1
        
        return total_spending