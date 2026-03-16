# Source: https://leetcode.com/problems/maximum-elegance-of-a-k-length-subsequence/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed 2D integer array items of length n and an integer k.
#
# items[i] = [profiti, categoryi], where profiti and categoryi denote the profit and category of the ith item respectively.
#
# Let's define the elegance of a subsequence of items as total_profit + distinct_categories2, where total_profit is the sum of all profits in the subsequence, and distinct_categories is the number of distinct categories from all the categories in the selected subsequence.
#
# Your task is to find the maximum elegance from all subsequences of size k in items.
#
# Return an integer denoting the maximum elegance of a subsequence of items with size exactly k.
#
# Note: A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the remaining elements' relative order.
#
# Example:
# Input: items = [[3,2],[5,1],[10,1]], k = 2
# Output: 17
# Explanation: In this example, we have to select a subsequence of size 2.
# We can select items[0] = [3,2] and items[2] = [10,1].
# The total profit in this subsequence is 3 + 10 = 13, and the subsequence contains 2 distinct categories [2,1].
# Hence, the elegance is 13 + 22 = 17, and we can show that it is the maximum achievable elegance.
#
# Constraints:
# 1 <= items.length == n <= 105
# 	items[i].length == 2
# 	items[i][0] == profiti
# 	items[i][1] == categoryi
# 	1 <= profiti <= 109
# 	1 <= categoryi <= n 
# 	1 <= k <= n
#

class Solution(object):
    def findMaximumElegance(self, items, k):
        """
        :type items: List[List[int]]
        :type k: int
        :rtype: int
        """
        items.sort(key=lambda x: -x[0])
        total_profit = 0
        category_count = {}
        duplicates = []
        
        for i in range(k):
            profit, category = items[i]
            total_profit += profit
            if category in category_count:
                category_count[category] += 1
                duplicates.append(profit)
            else:
                category_count[category] = 1
        
        distinct_categories = len(category_count)
        max_elegance = total_profit + distinct_categories * distinct_categories
        
        for i in range(k, len(items)):
            profit, category = items[i]
            if category not in category_count:
                if duplicates:
                    removed_profit = duplicates.pop()
                    total_profit = total_profit - removed_profit + profit
                    category_count[category] = 1
                    distinct_categories += 1
                    current_elegance = total_profit + distinct_categories * distinct_categories
                    max_elegance = max(max_elegance, current_elegance)
        
        return max_elegance