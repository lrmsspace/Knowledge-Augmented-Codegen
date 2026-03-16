# Source: https://leetcode.com/problems/two-city-scheduling/   |   Difficulty: Medium
#
# Problem Description:
# A company is planning to interview 2n people. Given the array costs where costs[i] = [aCosti, bCosti], the cost of flying the ith person to city a is aCosti, and the cost of flying the ith person to city b is bCosti.
#
# Return the minimum cost to fly every person to a city such that exactly n people arrive in each city.
#
# Example:
# Input: costs = [[10,20],[30,200],[400,50],[30,20]]
# Output: 110
# Explanation: 
# The first person goes to city A for a cost of 10.
# The second person goes to city A for a cost of 30.
# The third person goes to city B for a cost of 50.
# The fourth person goes to city B for a cost of 20.
#
# The total minimum cost is 10 + 30 + 50 + 20 = 110 to have half the people interviewing in each city.
#
# Constraints:
# 2 * n == costs.length
# 	2 <= costs.length <= 100
# 	costs.length is even.
# 	1 <= aCosti, bCosti <= 1000
#

class Solution(object):
    def twoCitySchedCost(self, costs):
        """
        :type costs: List[List[int]]
        :rtype: int
        """
        # Sort the costs based on the difference between flying to city A and city B
        costs.sort(key=lambda x: x[0] - x[1])
        
        total_cost = 0
        n = len(costs) // 2
        
        # Send first n people to city A and the rest to city B
        for i in range(n):
            total_cost += costs[i][0]  # Cost for city A
        for i in range(n, 2 * n):
            total_cost += costs[i][1]  # Cost for city B
        
        return total_cost