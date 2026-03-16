# Source: https://leetcode.com/problems/probability-of-a-two-boxes-having-the-same-number-of-distinct-balls/   |   Difficulty: Hard
#
# Problem Description:
# Given 2n balls of k distinct colors. You will be given an integer array balls of size k where balls[i] is the number of balls of color i.
#
# All the balls will be shuffled uniformly at random, then we will distribute the first n balls to the first box and the remaining n balls to the other box (Please read the explanation of the second example carefully).
#
# Please note that the two boxes are considered different. For example, if we have two balls of colors a and b, and two boxes [] and (), then the distribution [a] (b) is considered different than the distribution [b] (a) (Please read the explanation of the first example carefully).
#
# Return the probability that the two boxes have the same number of distinct balls. Answers within 10-5 of the actual value will be accepted as correct.
#
# Example:
# Input: balls = [1,1]
# Output: 1.00000
# Explanation: Only 2 ways to divide the balls equally:
# - A ball of color 1 to box 1 and a ball of color 2 to box 2
# - A ball of color 2 to box 1 and a ball of color 1 to box 2
# In both ways, the number of distinct colors in each box is equal. The probability is 2/2 = 1
#
# Constraints:
# 1 <= balls.length <= 8
# 	1 <= balls[i] <= 6
# 	sum(balls) is even.
#

class Solution(object):
    def getProbability(self, balls):
        """
        :type balls: List[int]
        :rtype: float
        """
        from math import comb

        k = len(balls)
        n = sum(balls) // 2
        total_ways = 0
        valid_ways = 0

        def backtrack(i, box1_count, box2_count, box1_distinct, box2_distinct, ways):
            nonlocal total_ways, valid_ways
            if i == k:
                if box1_count == n and box2_count == n:
                    total_ways += ways
                    if box1_distinct == box2_distinct:
                        valid_ways += ways
                return

            for b in range(balls[i] + 1):
                new_box1_count = box1_count + b
                new_box2_count = box2_count + (balls[i] - b)
                if new_box1_count <= n and new_box2_count <= n:
                    new_box1_distinct = box1_distinct + (1 if b > 0 else 0)
                    new_box2_distinct = box2_distinct + (1 if balls[i] - b > 0 else 0)
                    new_ways = ways * comb(balls[i], b)
                    backtrack(i + 1, new_box1_count, new_box2_count, new_box1_distinct, new_box2_distinct, new_ways)

        backtrack(0, 0, 0, 0, 0, 1)
        return valid_ways / total_ways if total_ways > 0 else 0.0