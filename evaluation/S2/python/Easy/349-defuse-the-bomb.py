# Source: https://leetcode.com/problems/defuse-the-bomb/   |   Difficulty: Easy
#
# Problem Description:
# You have a bomb to defuse, and your time is running out! Your informer will provide you with a circular array code of length of n and a key k.
#
# To decrypt the code, you must replace every number. All the numbers are replaced simultaneously.
#
#
# 	If k > 0, replace the ith number with the sum of the next k numbers.
# 	If k < 0, replace the ith number with the sum of the previous k numbers.
# 	If k == 0, replace the ith number with 0.
#
#
# As code is circular, the next element of code[n-1] is code[0], and the previous element of code[0] is code[n-1].
#
# Given the circular array code and an integer key k, return the decrypted code to defuse the bomb!
#
# Example:
# Input: code = [5,7,1,4], k = 3
# Output: [12,10,16,13]
# Explanation: Each number is replaced by the sum of the next 3 numbers. The decrypted code is [7+1+4, 1+4+5, 4+5+7, 5+7+1]. Notice that the numbers wrap around.
#
# Constraints:
# n == code.length
# 	1 <= n <= 100
# 	1 <= code[i] <= 100
# 	-(n - 1) <= k <= n - 1
#
# Helpful references (internal KB):
# - Operations on polynomials and series (array, recursion)
#   • When to use: Apply when multiplying polynomials or combining two sequences where the resulting element's index is the sum of indices from the original sequences. This is typically for enumerative counting problems.
#   • Idea: Convolution computes the coefficients of the product of two polynomials or series by summing products of coefficients whose indices add up to the target index. A direct computation has a time complexity of O(N*M).
#   • Invariants: For any k, c_k correctly represents the coefficient of x^k in the product polynomial.; The sum i + (k-i) always equals k for each term contributing to c_k.
#   • Tips: Understand the index relationship: c_k = sum(a_i * b_{k-i}) for all valid i.; Handle array bounds carefully for both input sequences and the result.
#   • Pitfalls: Off-by-one errors in loop bounds for indices i and k-i.; Incorrectly determining the size of the result array (should be n+m+1 elements for degrees n and m).
# - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
#   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
#   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
#   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
#   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
#   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
# - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
#   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
#   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
#   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
#   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
#   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def decrypt(self, code, k):
        """
        :type code: List[int]
        :type k: int
        :rtype: List[int]
        """
        n = len(code)
        if k == 0:
            return [0] * n
        
        result = [0] * n
        for i in range(n):
            if k > 0:
                result[i] = sum(code[(i + j) % n] for j in range(1, k + 1))
            else:
                result[i] = sum(code[(i + j) % n] for j in range(k, 0))
        
        return result