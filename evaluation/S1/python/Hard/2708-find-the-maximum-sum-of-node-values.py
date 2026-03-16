# Source: https://leetcode.com/problems/find-the-maximum-sum-of-node-values/   |   Difficulty: Hard
#
# Problem Description:
# There exists an undirected tree with n nodes numbered 0 to n - 1. You are given a 0-indexed 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the tree. You are also given a positive integer k, and a 0-indexed array of non-negative integers nums of length n, where nums[i] represents the value of the node numbered i.
#
# Alice wants the sum of values of tree nodes to be maximum, for which Alice can perform the following operation any number of times (including zero) on the tree:
#
#
# 	Choose any edge [u, v] connecting the nodes u and v, and update their values as follows:
#
# 	
# 		nums[u] = nums[u] XOR k
# 		nums[v] = nums[v] XOR k
# 	
# 	
#
#
# Return the maximum possible sum of the values Alice can achieve by performing the operation any number of times.
#
# Example:
# Input: nums = [1,2,1], k = 3, edges = [[0,1],[0,2]]
# Output: 6
# Explanation: Alice can achieve the maximum sum of 6 using a single operation:
# - Choose the edge [0,2]. nums[0] and nums[2] become: 1 XOR 3 = 2, and the array nums becomes: [1,2,1] -> [2,2,2].
# The total sum of values is 2 + 2 + 2 = 6.
# It can be shown that 6 is the maximum achievable sum of values.
#
# Constraints:
# 2 <= n == nums.length <= 2 * 104
# 	1 <= k <= 109
# 	0 <= nums[i] <= 109
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	0 <= edges[i][0], edges[i][1] <= n - 1
# 	The input is generated such that edges represent a valid tree.
#
# Helpful references (internal KB):
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Minimum Spanning Trees (graph, greedy)
#   • When to use: When you need to find a subset of edges in a connected, edge-weighted graph that connects all vertices with the minimum possible total edge weight. Useful for network design problems where minimizing connection costs is crucial.
#   • Idea: A Minimum Spanning Tree (MST) algorithm finds a subset of edges in an edge-weighted graph that connects all vertices with the minimum possible total weight, forming a tree. This is typically solved using greedy approaches with a time complexity often involving sorting edges or using a priority queue.
#   • Invariants: The set of edges selected so far always forms a forest.; Each connected component formed by the chosen edges is a valid subtree of some Minimum Spanning Tree.
#   • Tips: Greedy approaches often work by iteratively adding the cheapest valid edge or expanding from a starting vertex.; The cut property and cycle property are fundamental for proving correctness of MST algorithms.
#   • Pitfalls: Assuming the graph is always connected; disconnected graphs require finding a minimum spanning forest.; Incorrectly applying the greedy choice without ensuring it maintains the MST property (e.g., creating a cycle).
# - Fibonacci Numbers (number, greedy, enumeration)
#   • When to use: When you need a unique, non-ambiguous binary representation of positive integers based on Fibonacci numbers, ensuring no two consecutive Fibonacci numbers are used in the sum.
#   • Idea: This algorithm encodes a positive integer into a unique binary string by greedily finding its Zeckendorf representation (sum of non-consecutive Fibonacci numbers). The encoding process typically involves iterating through Fibonacci numbers, resulting in a logarithmic time complexity relative to the input number's magnitude.
#   • Invariants: The remaining value 'n' to be encoded is always non-negative.; The partial binary code constructed so far represents a valid Zeckendorf sum of non-consecutive Fibonacci numbers.
#   • Tips: Precompute Fibonacci numbers up to a certain limit to optimize lookups.; Always start with the largest Fibonacci number less than or equal to the target value.
#   • Pitfalls: Incorrectly handling the base cases for small numbers like 1 or 2.; Forgetting to append the mandatory final '1' bit to the codeword.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumValueSum(self, nums, k, edges):
        """
        :type nums: List[int]
        :type k: int
        :type edges: List[List[int]]
        :rtype: int
        """
        # Step 1: Build the adjacency list for the tree
        from collections import defaultdict, deque
        
        n = len(nums)
        graph = defaultdict(list)
        
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        # Step 2: Use a queue to perform BFS and determine the levels of the tree
        queue = deque([0])  # Start BFS from node 0
        visited = [False] * n
        visited[0] = True
        level = 0
        
        while queue:
            size = len(queue)
            for _ in range(size):
                node = queue.popleft()
                for neighbor in graph[node]:
                    if not visited[neighbor]:
                        visited[neighbor] = True
                        queue.append(neighbor)
            level += 1
        
        # Step 3: Calculate the maximum sum based on the levels of the tree
        max_sum = sum(nums)  # Initial sum of all node values
        
        # If k is 0, we cannot change any values, so return the initial sum
        if k == 0:
            return max_sum
        
        # We can flip values at even levels (0-based) to maximize the sum
        for i in range(n):
            if (i % 2 == 0):  # Even level nodes can be flipped
                flipped_value = nums[i] ^ k
                if flipped_value > nums[i]:  # Only flip if it increases the value
                    max_sum += (flipped_value - nums[i])
        
        return max_sum