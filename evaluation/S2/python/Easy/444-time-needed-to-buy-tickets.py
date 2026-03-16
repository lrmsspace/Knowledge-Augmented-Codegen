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
# -  
# Kth order statistic in O(N) (array, enumeration)
#   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
#   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
#   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
#   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
#   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
# - Josephus Problem (number, dp-1d, recursion)
#   • When to use: Used to determine the position of the last remaining person in a circle where every k-th person is eliminated until only one remains. It models sequential removal processes in a circular arrangement.
#   • Idea: The Josephus Problem determines the position of the survivor in a circle of N people, where every K-th person is eliminated. The standard solution uses a recursive relation or dynamic programming, typically achieving O(N) time complexity.
#   • Invariants: The result J(n, k) represents the survivor's original 0-indexed position among n people.; Each recursive step J(n, k) correctly transforms the result from J(n-1, k) based on the k-th elimination.
#   • Tips: Use 0-indexing for a simpler and more elegant recursive formula.; Establish the base case for N=1 (the survivor is always 0 or 1).
#   • Pitfalls: Off-by-one errors when switching between 0-indexing and 1-indexing.; Incorrectly applying the modulo operator, especially with negative results in some languages.
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
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