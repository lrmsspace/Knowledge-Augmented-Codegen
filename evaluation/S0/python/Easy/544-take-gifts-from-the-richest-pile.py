# Source: https://leetcode.com/problems/take-gifts-from-the-richest-pile/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array gifts denoting the number of gifts in various piles. Every second, you do the following:
#
#
# 	Choose the pile with the maximum number of gifts.
# 	If there is more than one pile with the maximum number of gifts, choose any.
# 	Reduce the number of gifts in the pile to the floor of the square root of the original number of gifts in the pile.
#
#
# Return the number of gifts remaining after k seconds.
#
# Example:
# Input: gifts = [25,64,9,4,100], k = 4
# Output: 29
# Explanation: 
# The gifts are taken in the following way:
# - In the first second, the last pile is chosen and 10 gifts are left behind.
# - Then the second pile is chosen and 8 gifts are left behind.
# - After that the first pile is chosen and 5 gifts are left behind.
# - Finally, the last pile is chosen again and 3 gifts are left behind.
# The final remaining gifts are [5,8,9,4,3], so the total number of gifts remaining is 29.
#
# Constraints:
# 1 <= gifts.length <= 103
# 	1 <= gifts[i] <= 109
# 	1 <= k <= 103
#

class Solution(object):
    def pickGifts(self, gifts, k):
        """
        :type gifts: List[int]
        :type k: int
        :rtype: int
        """
        import heapq
        # 使用最大堆来存储礼物堆
        max_heap = [-gift for gift in gifts]
        heapq.heapify(max_heap)
        
        for _ in range(k):
            # 取出最大堆的堆顶元素（即最大的礼物数）
            max_gift = -heapq.heappop(max_heap)
            # 计算平方根并向下取整
            new_gift = int(max_gift ** 0.5)
            # 将新的礼物数重新放入最大堆
            heapq.heappush(max_heap, -new_gift)
        
        # 计算剩余礼物的总数
        return -sum(max_heap)