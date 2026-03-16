# Source: https://leetcode.com/problems/total-distance-traveled/   |   Difficulty: Easy
#
# Problem Description:
# A truck has two fuel tanks. You are given two integers, mainTank representing the fuel present in the main tank in liters and additionalTank representing the fuel present in the additional tank in liters.
#
# The truck has a mileage of 10 km per liter. Whenever 5 liters of fuel get used up in the main tank, if the additional tank has at least 1 liters of fuel, 1 liters of fuel will be transferred from the additional tank to the main tank.
#
# Return the maximum distance which can be traveled.
#
# Note: Injection from the additional tank is not continuous. It happens suddenly and immediately for every 5 liters consumed.
#
# Example:
# Input: mainTank = 5, additionalTank = 10
# Output: 60
# Explanation: 
# After spending 5 litre of fuel, fuel remaining is (5 - 5 + 1) = 1 litre and distance traveled is 50km.
# After spending another 1 litre of fuel, no fuel gets injected in the main tank and the main tank becomes empty.
# Total distance traveled is 60km.
#
# Constraints:
# 1 <= mainTank, additionalTank <= 100
#
# Helpful references (internal KB):
# - Maximum flow - Push-relabel algorithm (graph, number, simulation)
#   • When to use: Use when finding the maximum flow in a network, particularly for dense graphs or when the Ford-Fulkerson method is too slow due to many augmenting paths.
#   • Idea: The Push-relabel algorithm computes maximum flow by maintaining a preflow and a height function, iteratively pushing excess flow from higher to lower nodes and relabeling nodes until all excess is pushed to the sink. It is a highly efficient polynomial-time algorithm for various graph structures.
#   • Invariants: For any vertex v (not source or sink), the total incoming flow minus total outgoing flow is non-negative (excess flow).; For any edge (u, v) in the residual graph with positive capacity, the height of u is at most h(v) + 1.
#   • Tips: Understand the concepts of preflow and excess flow.; Correctly implement push and relabel operations.
#   • Pitfalls: Incorrectly updating residual capacities after a push.; Failing to maintain the height function property (h(u) <= h(v) + 1).
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Maximum flow - Push-relabel algorithm (graph, number, simulation)
#   • When to use: Use when computing the maximum flow in a network, especially for dense graphs where its O(V^2 E) complexity can be competitive. It's an alternative to augmenting path algorithms.
#   • Idea: The Push-relabel algorithm computes maximum flow by maintaining a preflow and a height function, iteratively pushing excess flow from vertices and relabeling them until a valid flow is achieved. It typically runs in O(V^2 E) time.
#   • Invariants: For any edge (u, v) in the residual graph with positive capacity, h(u) <= h(v) + 1.; Excess flow at the source (s) is always non-negative, and at the sink (t) is always non-positive.
#   • Tips: Initialize the graph with a valid preflow and height function.; Prioritize pushing excess from vertices with the highest labels.
#   • Pitfalls: Incorrectly updating residual capacities after a push operation.; Violating the height function validity condition (h(u) <= h(v) + 1).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def distanceTraveled(self, mainTank, additionalTank):
        """
        :type mainTank: int
        :type additionalTank: int
        :rtype: int
        """
        distance = 0
        
        while mainTank > 0:
            # Calculate the distance traveled with the current fuel
            distance += mainTank * 10
            
            # Calculate how many times we can transfer fuel from the additional tank
            transfers = mainTank // 5
            
            # Check if we have enough fuel in the additional tank for the transfers
            if additionalTank >= transfers:
                additionalTank -= transfers
                mainTank += transfers  # Transfer fuel to the main tank
            else:
                mainTank += additionalTank  # Transfer all remaining fuel from the additional tank
                additionalTank = 0
            mainTank -= 5 * transfers  # Consume fuel for the distance traveled
        return distance