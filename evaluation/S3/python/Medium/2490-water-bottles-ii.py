# Source: https://leetcode.com/problems/water-bottles-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integers numBottles and numExchange.
#
# numBottles represents the number of full water bottles that you initially have. In one operation, you can perform one of the following operations:
#
#
# 	Drink any number of full water bottles turning them into empty bottles.
# 	Exchange numExchange empty bottles with one full water bottle. Then, increase numExchange by one.
#
#
# Note that you cannot exchange multiple batches of empty bottles for the same value of numExchange. For example, if numBottles == 3 and numExchange == 1, you cannot exchange 3 empty water bottles for 3 full bottles.
#
# Return the maximum number of water bottles you can drink.
#
# Example:
# Input: numBottles = 13, numExchange = 6
# Output: 15
# Explanation: The table above shows the number of full water bottles, empty water bottles, the value of numExchange, and the number of bottles drunk.
#
# Constraints:
# 1 <= numBottles <= 100 
# 	1 <= numExchange <= 100
#
# Helpful references (internal KB):
# - Extended Euclidean Algorithm (number, gcd, simulation)
#   • When to use: Use this algorithm to find integer coefficients x and y that satisfy Bézout's identity (ax + by = gcd(a,b)). It is also essential for computing modular multiplicative inverses and solving linear Diophantine equations.
#   • Idea: The Extended Euclidean Algorithm computes the greatest common divisor (GCD) of two integers 'a' and 'b', and simultaneously finds integer coefficients 'x' and 'y' such that 'ax + by = gcd(a,b)'. It operates in O(log(min(a,b))) time complexity.
#   • Invariants: x * (initial a) + y * (initial b) = current_a_value; x_1 * (initial a) + y_1 * (initial b) = current_b_value
#   • Tips: Can be implemented using either a recursive or an iterative approach.; The algorithm correctly handles negative integer inputs.
#   • Pitfalls: Incorrectly defining base cases in recursive implementations can lead to errors.; Potential for integer overflow if coefficients x or y become extremely large, though uncommon.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Maximum flow - Push-relabel algorithm (graph, number, simulation)
#   • When to use: Use when finding the maximum flow in a network, particularly for dense graphs or when the Ford-Fulkerson method is too slow due to many augmenting paths.
#   • Idea: The Push-relabel algorithm computes maximum flow by maintaining a preflow and a height function, iteratively pushing excess flow from higher to lower nodes and relabeling nodes until all excess is pushed to the sink. It is a highly efficient polynomial-time algorithm for various graph structures.
#   • Invariants: For any vertex v (not source or sink), the total incoming flow minus total outgoing flow is non-negative (excess flow).; For any edge (u, v) in the residual graph with positive capacity, the height of u is at most h(v) + 1.
#   • Tips: Understand the concepts of preflow and excess flow.; Correctly implement push and relabel operations.
#   • Pitfalls: Incorrectly updating residual capacities after a push.; Failing to maintain the height function property (h(u) <= h(v) + 1).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxBottlesDrunk(self, numBottles, numExchange):
        """
        :type numBottles: int
        :type numExchange: int
        :rtype: int
        """
        total_drunk = numBottles
        empty_bottles = numBottles

        while empty_bottles >= numExchange:
            new_full = empty_bottles // numExchange
            total_drunk += new_full
            empty_bottles = empty_bottles % numExchange + new_full
            numExchange += 1

        return total_drunk