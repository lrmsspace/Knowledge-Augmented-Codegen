# Source: https://leetcode.com/problems/reachable-nodes-with-restrictions/   |   Difficulty: Medium
#
# Problem Description:
# There is an undirected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.
#
# You are given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree. You are also given an integer array restricted which represents restricted nodes.
#
# Return the maximum number of nodes you can reach from node 0 without visiting a restricted node.
#
# Note that node 0 will not be a restricted node.
#
# Example:
# Input: n = 7, edges = [[0,1],[1,2],[3,1],[4,0],[0,5],[5,6]], restricted = [4,5]
# Output: 4
# Explanation: The diagram above shows the tree.
# We have that [0,1,2,3] are the only nodes that can be reached from node 0 without visiting a restricted node.
#
# Constraints:
# 2 <= n <= 105
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	0 <= ai, bi < n
# 	ai != bi
# 	edges represents a valid tree.
# 	1 <= restricted.length < n
# 	1 <= restricted[i] < n
# 	All the values of restricted are unique.
#
# Helpful references (internal KB):
# - MEX (minimal excluded) of a sequence (array, enumeration)
#   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
#   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
#   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
#   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
#   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
# - Sparse Table (array, sparse-table, enumeration)
#   • When to use: Use when performing many range queries on a static array where the query operation is idempotent (e.g., min, max, GCD) to achieve O(1) query time after O(N log N) precomputation.
#   • Idea: A data structure that precomputes answers for all possible range queries of power-of-two lengths, allowing O(1) query time for idempotent operations like range minimum/maximum queries. Precomputation takes O(N log N) time and space.
#   • Invariants: The `st[k][i]` entry stores the result of the operation for the range `[i, i + 2^k - 1]`.; All ranges of length `2^k` starting at `i` are correctly computed in `st[k][i]` during precomputation.
#   • Tips: Precompute logarithms for O(1) lookup of `floor(log2(length))` during queries.; Sparse tables are most efficient for idempotent operations (min, max, GCD, OR, AND) due to overlapping segments.
#   • Pitfalls: Not suitable for dynamic arrays or scenarios requiring updates, as modifications invalidate the precomputed table.; High memory usage: requires O(N log N) space, which can be significant for large N.
# - Sqrt Tree (array, number, bitmask-dp, enumeration)
#   • When to use: Used for answering range queries on a static array by recursively decomposing it into square root sized blocks, achieving O(log log N) query time.
#   • Idea: A Sqrt Tree is a recursive data structure that decomposes an array into blocks of square root size, building a similar structure on each block. It allows for efficient range queries, typically achieving O(log log N) query time after an O(N log log N) precomputation.
#   • Invariants: Each node in the Sqrt Tree represents a contiguous segment of the original array.; A node representing a segment of length k has sqrt(k) children, each covering a block of sqrt(k) elements.
#   • Tips: Precompute answers for all possible block combinations within a node.; Handle queries spanning multiple blocks by combining precomputed prefix, suffix, and full block results.
#   • Pitfalls: High constant factors due to complex precomputation per node.; Memory usage can be significant, O(N log log N), for large N.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def reachableNodes(self, n, edges, restricted):
        """
        :type n: int
        :type edges: List[List[int]]
        :type restricted: List[int]
        :rtype: int
        """
        from collections import defaultdict, deque
        
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        restricted_set = set(restricted)
        visited = set()
        queue = deque([0])
        count = 0
        
        while queue:
            node = queue.popleft()
            if node in visited or node in restricted_set:
                continue
            visited.add(node)
            count += 1
            for neighbor in graph[node]:
                if neighbor not in visited and neighbor not in restricted_set:
                    queue.append(neighbor)
        
        return count