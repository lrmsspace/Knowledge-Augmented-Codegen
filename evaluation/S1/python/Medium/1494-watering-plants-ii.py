# Source: https://leetcode.com/problems/watering-plants-ii/   |   Difficulty: Medium
#
# Problem Description:
# Alice and Bob want to water n plants in their garden. The plants are arranged in a row and are labeled from 0 to n - 1 from left to right where the ith plant is located at x = i.
#
# Each plant needs a specific amount of water. Alice and Bob have a watering can each, initially full. They water the plants in the following way:
#
#
# 	Alice waters the plants in order from left to right, starting from the 0th plant. Bob waters the plants in order from right to left, starting from the (n - 1)th plant. They begin watering the plants simultaneously.
# 	It takes the same amount of time to water each plant regardless of how much water it needs.
# 	Alice/Bob must water the plant if they have enough in their can to fully water it. Otherwise, they first refill their can (instantaneously) then water the plant.
# 	In case both Alice and Bob reach the same plant, the one with more water currently in his/her watering can should water this plant. If they have the same amount of water, then Alice should water this plant.
#
#
# Given a 0-indexed integer array plants of n integers, where plants[i] is the amount of water the ith plant needs, and two integers capacityA and capacityB representing the capacities of Alice's and Bob's watering cans respectively, return the number of times they have to refill to water all the plants.
#
# Example:
# Input: plants = [2,2,3,3], capacityA = 5, capacityB = 5
# Output: 1
# Explanation:
# - Initially, Alice and Bob have 5 units of water each in their watering cans.
# - Alice waters plant 0, Bob waters plant 3.
# - Alice and Bob now have 3 units and 2 units of water respectively.
# - Alice has enough water for plant 1, so she waters it. Bob does not have enough water for plant 2, so he refills his can then waters it.
# So, the total number of times they have to refill to water all the plants is 0 + 0 + 1 + 0 = 1.
#
# Constraints:
# n == plants.length
# 	1 <= n <= 105
# 	1 <= plants[i] <= 106
# 	max(plants[i]) <= capacityA, capacityB <= 109
#
# Helpful references (internal KB):
# - Scheduling jobs on two machines (array, greedy)
#   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
#   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
#   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
#   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
#   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
# - Linked-list implementations of collections (linked-list, queue, simulation)
#   • When to use: Use when frequent insertions or deletions at the beginning or end of a collection are required, or when the collection size is highly dynamic and unpredictable.
#   • Idea: Linked lists implement dynamic collections like queues and stacks by chaining nodes, each holding an item and a reference to the next node. Operations like adding or removing elements at the ends typically achieve O(1) time complexity, while random access is O(N).
#   • Invariants: The `first` pointer always references the head node, or is null if the list is empty.; The `last` pointer always references the tail node, or is null if the list is empty.
#   • Tips: Maintain separate `first` and `last` pointers for O(1) enqueue/dequeue operations.; Keep a `size` counter to provide O(1) size retrieval.
#   • Pitfalls: Forgetting to update `first` or `last` pointers correctly can lead to broken lists or memory leaks.; Null pointer exceptions are common when traversing or modifying an empty or partially traversed list.
# - Josephus Problem (number, recursion, counting)
#   • When to use: Use when simulating a circular elimination process with a fixed step size, especially when seeking the survivor's position. It's particularly efficient for specific step sizes like two.
#   • Idea: The Josephus Problem determines the last remaining position in a circular arrangement after elements are eliminated at fixed intervals. The recursive solution for a step size of two has a logarithmic time complexity, O(log N), due to its divide-and-conquer nature.
#   • Invariants: The number of participants N is always positive in each recursive subproblem.; The returned position is always within the valid range [0, current N-1] (or [1, current N]).
#   • Tips: Base cases are crucial for recursive solutions, typically for N=1.; Observe patterns for specific step sizes, especially k=2, which has a simpler formula.
#   • Pitfalls: Off-by-one errors when converting between 0-indexed and 1-indexed results.; Incorrectly applying the position 'shift' after elements are eliminated in subproblems.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumRefill(self, plants, capacityA, capacityB):
        """
        :type plants: List[int]
        :type capacityA: int
        :type capacityB: int
        :rtype: int
        """
        n = len(plants)
        i, j = 0, n - 1
        currA, currB = capacityA, capacityB
        refills = 0

        while i < j:
            if currA < plants[i]:
                refills += 1
                currA = capacityA
            currA -= plants[i]
            i += 1

            if currB < plants[j]:
                refills += 1
                currB = capacityB
            currB -= plants[j]
            j -= 1

        if i == j:
            if currA >= currB:
                if currA < plants[i]:
                    refills += 1
            else:
                if currB < plants[j]:
                    refills += 1

        return refills