# Source: https://leetcode.com/problems/sell-diminishing-valued-colored-balls/   |   Difficulty: Medium
#
# Problem Description:
# You have an inventory of different colored balls, and there is a customer that wants orders balls of any color.
#
# The customer weirdly values the colored balls. Each colored ball's value is the number of balls of that color you currently have in your inventory. For example, if you own 6 yellow balls, the customer would pay 6 for the first yellow ball. After the transaction, there are only 5 yellow balls left, so the next yellow ball is then valued at 5 (i.e., the value of the balls decreases as you sell more to the customer).
#
# You are given an integer array, inventory, where inventory[i] represents the number of balls of the ith color that you initially own. You are also given an integer orders, which represents the total number of balls that the customer wants. You can sell the balls in any order.
#
# Return the maximum total value that you can attain after selling orders colored balls. As the answer may be too large, return it modulo 109 + 7.
#
# Example:
# Input: inventory = [2,5], orders = 4
# Output: 14
# Explanation: Sell the 1st color 1 time (2) and the 2nd color 3 times (5 + 4 + 3).
# The maximum total value is 2 + 5 + 4 + 3 = 14.
#
# Constraints:
# 1 <= inventory.length <= 105
# 	1 <= inventory[i] <= 109
# 	1 <= orders <= min(sum(inventory[i]), 109)
#
# Helpful references (internal KB):
# - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
#   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
#   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
#   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
#   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
#   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
# - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
#   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
#   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
#   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
#   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
#   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
# -  
# Kth order statistic in O(N) (array, enumeration)
#   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
#   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
#   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
#   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
#   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxProfit(self, inventory, orders):
        """
        :type inventory: List[int]
        :type orders: int
        :rtype: int
        """
        import heapq
        
        # Use a max-heap to always sell the most valuable ball first
        max_heap = [-x for x in inventory]
        heapq.heapify(max_heap)
        
        total_profit = 0
        mod = 10**9 + 7
        
        while orders > 0:
            # Get the most valuable ball
            current_value = -heapq.heappop(max_heap)
            next_value = -max_heap[0] if max_heap else 0
            
            # Calculate how many balls we can sell at the current value
            count = min(orders, (current_value - next_value) * (len(max_heap) + 1))
            
            # Calculate profit for selling these balls
            full_rows = count // (len(max_heap) + 1)
            remainder = count % (len(max_heap) + 1)
            
            total_profit += (full_rows * (current_value + current_value - full_rows + 1) // 2) * (len(max_heap) + 1)
            total_profit += remainder * (current_value - full_rows)
            total_profit %= mod
            
            # Update the heap with the new value of the balls after selling
            if current_value - full_rows > next_value:
                heapq.heappush(max_heap, -(current_value - full_rows))
        
        return total_profit