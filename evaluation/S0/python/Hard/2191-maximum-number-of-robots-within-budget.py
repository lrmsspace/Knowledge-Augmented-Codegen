# Source: https://leetcode.com/problems/maximum-number-of-robots-within-budget/   |   Difficulty: Hard
#
# Problem Description:
# You have n robots. You are given two 0-indexed integer arrays, chargeTimes and runningCosts, both of length n. The ith robot costs chargeTimes[i] units to charge and costs runningCosts[i] units to run. You are also given an integer budget.
#
# The total cost of running k chosen robots is equal to max(chargeTimes) + k * sum(runningCosts), where max(chargeTimes) is the largest charge cost among the k robots and sum(runningCosts) is the sum of running costs among the k robots.
#
# Return the maximum number of consecutive robots you can run such that the total cost does not exceed budget.
#
# Example:
# Input: chargeTimes = [3,6,1,3,4], runningCosts = [2,1,3,4,5], budget = 25
# Output: 3
# Explanation: 
# It is possible to run all individual and consecutive pairs of robots within budget.
# To obtain answer 3, consider the first 3 robots. The total cost will be max(3,6,1) + 3 * sum(2,1,3) = 6 + 3 * 6 = 24 which is less than 25.
# It can be shown that it is not possible to run more than 3 consecutive robots within budget, so we return 3.
#
# Constraints:
# chargeTimes.length == runningCosts.length == n
# 	1 <= n <= 5 * 104
# 	1 <= chargeTimes[i], runningCosts[i] <= 105
# 	1 <= budget <= 1015
#

class Solution(object):
    def maximumRobots(self, chargeTimes, runningCosts, budget):
        """
        :type chargeTimes: List[int]
        :type runningCosts: List[int]
        :type budget: int
        :rtype: int
        """
        from collections import deque

        left = 0
        total_running_cost = 0
        max_robots = 0
        max_charge_deque = deque()

        for right in range(len(chargeTimes)):
            total_running_cost += runningCosts[right]

            while max_charge_deque and chargeTimes[max_charge_deque[-1]] <= chargeTimes[right]:
                max_charge_deque.pop()
            max_charge_deque.append(right)

            while max_charge_deque and (chargeTimes[max_charge_deque[0]] + (right - left + 1) * total_running_cost) > budget:
                total_running_cost -= runningCosts[left]
                if max_charge_deque[0] == left:
                    max_charge_deque.popleft()
                left += 1

            max_robots = max(max_robots, right - left + 1)

        return max_robots