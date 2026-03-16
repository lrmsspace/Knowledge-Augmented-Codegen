# Source: https://leetcode.com/problems/candy/   |   Difficulty: Hard
#
# Problem Description:
# There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
#
# You are giving candies to these children subjected to the following requirements:
#
#
# 	Each child must have at least one candy.
# 	Children with a higher rating get more candies than their neighbors.
#
#
# Return the minimum number of candies you need to have to distribute the candies to the children.
#
# Example:
# Input: ratings = [1,0,2]
# Output: 5
# Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.
#
# Constraints:
# n == ratings.length
# 	1 <= n <= 2 * 104
# 	0 <= ratings[i] <= 2 * 104
#

class Solution(object):
    def candy(self, ratings):
        """
        :type ratings: List[int]
        :rtype: int
        """
        n = len(ratings)
        candies = [1] * n
        
        # 从左到右遍历，确保右边的孩子比左边的孩子评分高时，糖果数更多
        for i in range(1, n):
            if ratings[i] > ratings[i - 1]:
                candies[i] = candies[i - 1] + 1
        
        # 从右到左遍历，确保左边的孩子比右边的孩子评分高时，糖果数更多
        for i in range(n - 2, -1, -1):
            if ratings[i] > ratings[i + 1]:
                candies[i] = max(candies[i], candies[i + 1] + 1)
        
        return sum(candies)