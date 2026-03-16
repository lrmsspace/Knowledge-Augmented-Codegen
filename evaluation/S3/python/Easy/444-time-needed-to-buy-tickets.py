# Source: https://leetcode.com/problems/time-needed-to-buy-tickets/   |   Difficulty: Easy
#
# Problem Description:
# There are n people in a line queuing to buy tickets, where the 0th person is at the front of the line and the (n - 1)th person is at the back of the line.
#
# You are given a 0-indexed integer array tickets of length n where the number of tickets that the ith person would like to buy is tickets[i].
#
# Each person takes exactly 1 second to buy a ticket. A person can only buy 1 ticket at a time and has to go back to the end of the line (which happens instantaneously) in order to buy more tickets. If a person does not have any tickets left to buy, the person will leave the line.
#
# Return the time taken for the person initially at position k (0-indexed) to finish buying tickets.
#
# Example:
# Input: tickets = [2,3,2], k = 2
#
# Output: 6
#
# Explanation:
#
#
# 	The queue starts as [2,3,2], where the kth person is underlined.
# 	After the person at the front has bought a ticket, the queue becomes [3,2,1] at 1 second.
# 	Continuing this process, the queue becomes [2,1,2] at 2 seconds.
# 	Continuing this process, the queue becomes [1,2,1] at 3 seconds.
# 	Continuing this process, the queue becomes [2,1] at 4 seconds. Note: the person at the front left the queue.
# 	Continuing this process, the queue becomes [1,1] at 5 seconds.
# 	Continuing this process, the queue becomes [1] at 6 seconds. The kth person has bought all their tickets, so return 6.
#
# Constraints:
# n == tickets.length
# 	1 <= n <= 100
# 	1 <= tickets[i] <= 100
# 	0 <= k < n
#
# Helpful references (internal KB):
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# -  
# Kth order statistic in O(N) (array, enumeration)
#   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
#   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
#   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
#   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
#   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
# - Josephus Problem (number, simulation, recursion)
#   • When to use: Use when determining the survivor's position in a circular game where every k-th person is eliminated, especially for large N where direct simulation is too slow.
#   • Idea: This algorithm finds the position of the last remaining person in the Josephus problem by iteratively reducing the problem size using a recursive formula and modulo arithmetic. It achieves an optimized time complexity of O(k log n).
#   • Invariants: The number of remaining elements decreases in each recursive step.; The relative order of the remaining elements is preserved throughout the process.
#   • Tips: Handle the base case where n < k separately to avoid infinite loops or incorrect calculations.; Use 0-indexing for simpler modulo arithmetic in the recursive formulas.
#   • Pitfalls: Incorrectly handling index shifts after elements are removed can lead to wrong results.; Forgetting the base case n < k can lead to infinite recursion or incorrect behavior.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def timeRequiredToBuy(self, tickets, k):
        """
        :type tickets: List[int]
        :type k: int
        :rtype: int
        """
        time = 0
        n = len(tickets)
        
        while tickets[k] > 0:
            for i in range(n):
                if tickets[i] > 0:
                    tickets[i] -= 1
                    time += 1
                if tickets[k] == 0:
                    break
        
        return time