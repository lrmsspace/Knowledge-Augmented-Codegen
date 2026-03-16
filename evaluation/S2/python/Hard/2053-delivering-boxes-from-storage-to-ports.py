# Source: https://leetcode.com/problems/delivering-boxes-from-storage-to-ports/   |   Difficulty: Hard
#
# Problem Description:
# You have the task of delivering some boxes from storage to their ports using only one ship. However, this ship has a limit on the number of boxes and the total weight that it can carry.
#
# You are given an array boxes, where boxes[i] = [ports​​i​, weighti], and three integers portsCount, maxBoxes, and maxWeight.
#
#
# 	ports​​i is the port where you need to deliver the ith box and weightsi is the weight of the ith box.
# 	portsCount is the number of ports.
# 	maxBoxes and maxWeight are the respective box and weight limits of the ship.
#
#
# The boxes need to be delivered in the order they are given. The ship will follow these steps:
#
#
# 	The ship will take some number of boxes from the boxes queue, not violating the maxBoxes and maxWeight constraints.
# 	For each loaded box in order, the ship will make a trip to the port the box needs to be delivered to and deliver it. If the ship is already at the correct port, no trip is needed, and the box can immediately be delivered.
# 	The ship then makes a return trip to storage to take more boxes from the queue.
#
#
# The ship must end at storage after all the boxes have been delivered.
#
# Return the minimum number of trips the ship needs to make to deliver all boxes to their respective ports.
#
# Example:
# Input: boxes = [[1,1],[2,1],[1,1]], portsCount = 2, maxBoxes = 3, maxWeight = 3
# Output: 4
# Explanation: The optimal strategy is as follows: 
# - The ship takes all the boxes in the queue, goes to port 1, then port 2, then port 1 again, then returns to storage. 4 trips.
# So the total number of trips is 4.
# Note that the first and third boxes cannot be delivered together because the boxes need to be delivered in order (i.e. the second box needs to be delivered at port 2 before the third box).
#
# Constraints:
# 1 <= boxes.length <= 105
# 	1 <= portsCount, maxBoxes, maxWeight <= 105
# 	1 <= ports​​i <= portsCount
# 	1 <= weightsi <= maxWeight
#
# Helpful references (internal KB):
# - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
#   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
#   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
#   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
#   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
#   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Finding Bridges Online (graph, ds, union-find, counting)
#   • When to use: Use when edges are added one by one to an initially empty graph and you need to efficiently track the number of bridges or 2-edge-connected components after each addition.
#   • Idea: This algorithm dynamically maintains the number of bridges in an undirected graph as edges are added incrementally. It leverages a Disjoint Set Union (DSU) data structure to achieve an amortized time complexity of O((N+M) log N).
#   • Invariants: Each DSU set represents a 2-edge-connected component or a collection of such components connected by bridges.; The total count of bridges accurately reflects edges whose removal increases connected components.
#   • Tips: Understand the properties of 2-edge-connected components and how they relate to bridges.; Carefully manage DSU operations, including path compression and union by rank/size, for optimal performance.
#   • Pitfalls: Incorrectly updating the bridge count after an edge addition, especially when cycles are formed.; Inefficient DSU operations leading to a higher than expected time complexity.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def boxDelivering(self, boxes, portsCount, maxBoxes, maxWeight):
        """
        :type boxes: List[List[int]]
        :type portsCount: int
        :type maxBoxes: int
        :type maxWeight: int
        :rtype: int
        """
        n = len(boxes)
        dp = [0] * (n + 1)
        j = 0
        weight = 0
        trips = 0

        for i in range(n):
            weight += boxes[i][1]
            if i - j + 1 > maxBoxes or weight > maxWeight:
                dp[i] = dp[j] + trips + 1
                while j < i and (i - j + 1 > maxBoxes or weight > maxWeight):
                    weight -= boxes[j][1]
                    if j + 1 < n and boxes[j][0] != boxes[j + 1][0]:
                        trips -= 1
                    j += 1
                trips += 1
            else:
                dp[i] = dp[i - 1]
                if i > 0 and boxes[i][0] != boxes[i - 1][0]:
                    trips += 1

        return dp[n - 1] + trips + 1