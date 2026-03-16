# Source: https://leetcode.com/problems/maximum-tastiness-of-candy-basket/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of positive integers price where price[i] denotes the price of the ith candy and a positive integer k.
#
# The store sells baskets of k distinct candies. The tastiness of a candy basket is the smallest absolute difference of the prices of any two candies in the basket.
#
# Return the maximum tastiness of a candy basket.
#
# Example:
# Input: price = [13,5,1,8,21,2], k = 3
# Output: 8
# Explanation: Choose the candies with the prices [13,5,21].
# The tastiness of the candy basket is: min(|13 - 5|, |13 - 21|, |5 - 21|) = min(8, 8, 16) = 8.
# It can be proven that 8 is the maximum tastiness that can be achieved.
#
# Constraints:
# 2 <= k <= price.length <= 105
# 	1 <= price[i] <= 109
#

class Solution(object):
    def maximumTastiness(self, price, k):
        """
        :type price: List[int]
        :type k: int
        :rtype: int
        """
        price.sort()

        def canAchieveTastiness(tastiness):
            count = 1
            last_price = price[0]

            for p in price[1:]:
                if p - last_price >= tastiness:
                    count += 1
                    last_price = p
                    if count == k:
                        return True
            return False

        left, right = 0, price[-1] - price[0]
        answer = 0

        while left <= right:
            mid = (left + right) // 2
            if canAchieveTastiness(mid):
                answer = mid
                left = mid + 1
            else:
                right = mid - 1

        return answer