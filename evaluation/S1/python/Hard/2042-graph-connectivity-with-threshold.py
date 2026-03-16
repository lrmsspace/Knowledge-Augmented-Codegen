# Source: https://leetcode.com/problems/graph-connectivity-with-threshold/   |   Difficulty: Hard
#
# Problem Description:
# We have n cities labeled from 1 to n. Two different cities with labels x and y are directly connected by a bidirectional road if and only if x and y share a common divisor strictly greater than some threshold. More formally, cities with labels x and y have a road between them if there exists an integer z such that all of the following are true:
#
#
# 	x % z == 0,
# 	y % z == 0, and
# 	z > threshold.
#
#
# Given the two integers, n and threshold, and an array of queries, you must determine for each queries[i] = [ai, bi] if cities ai and bi are connected directly or indirectly. (i.e. there is some path between them).
#
# Return an array answer, where answer.length == queries.length and answer[i] is true if for the ith query, there is a path between ai and bi, or answer[i] is false if there is no path.
#
# Example:
# Input: n = 6, threshold = 2, queries = [[1,4],[2,5],[3,6]]
# Output: [false,false,true]
# Explanation: The divisors for each number:
# 1:   1
# 2:   1, 2
# 3:   1, 3
# 4:   1, 2, 4
# 5:   1, 5
# 6:   1, 2, 3, 6
# Using the underlined divisors above the threshold, only cities 3 and 6 share a common divisor, so they are the
# only ones directly connected. The result of each query:
# [1,4]   1 is not connected to 4
# [2,5]   2 is not connected to 5
# [3,6]   3 is connected to 6 through path 3--6
#
# Constraints:
# 2 <= n <= 104
# 	0 <= threshold <= n
# 	1 <= queries.length <= 105
# 	queries[i].length == 2
# 	1 <= ai, bi <= cities
# 	ai != bi
#
# Helpful references (internal KB):
# - Disjoint Set Union (ds, tree, array, union-find)
#   • When to use: Use when you need to maintain a collection of disjoint sets and efficiently perform union operations to merge sets or find the representative of an element's set.
#   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. With path compression and union by rank/size, these operations achieve nearly constant amortized time complexity, O(alpha(N)).
#   • Invariants: Each element `v` is either a root (parent[v] == v) or has a parent pointer to another element in its set.; The `find_set` operation, after path compression, ensures that all nodes on the path from `v` to its root directly point to the root.
#   • Tips: Implement path compression in `find_set` for optimal performance.; Use union by rank or union by size to keep trees flat and balanced.
#   • Pitfalls: Forgetting path compression or union by rank/size leads to O(N) worst-case operations.; Incorrectly merging sets by only updating one root without considering the other's rank/size.
# - Continued fractions (number, enumeration, gcd)
#   • When to use: Use when seeking the best rational approximations of real numbers or solving certain Diophantine equations. It's also applied in number theory for analyzing properties of irrational numbers.
#   • Idea: Continued fractions represent a real number as a sum of an integer and the reciprocal of another number, recursively. This iterative process, based on the Euclidean algorithm, generates a sequence of best rational approximations.
#   • Invariants: The current convergent p_k / q_k is the best rational approximation for its denominator size.; The sequence of partial quotients a_i are integers, with a_i >= 1 for i > 0.
#   • Tips: Understand the relationship with the Euclidean algorithm for rational numbers.; Convergents provide the best rational approximations for a given denominator size.
#   • Pitfalls: Floating-point precision issues can significantly affect accuracy for real numbers.; Misinterpreting 'best approximation' as globally best, rather than best for a given denominator bound.
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
    def areConnected(self, n, threshold, queries):
        """
        :type n: int
        :type threshold: int
        :type queries: List[List[int]]
        :rtype: List[bool]
        """
        # DSU implementation
        parent = list(range(n + 1))
        rank = [1] * (n + 1)

        def find_set(v):
            if parent[v] != v:
                parent[v] = find_set(parent[v])  # Path compression
            return parent[v]

        def union_sets(a, b):
            a = find_set(a)
            b = find_set(b)
            if a != b:
                if rank[a] < rank[b]:
                    a, b = b, a
                parent[b] = a
                if rank[a] == rank[b]:
                    rank[a] += 1

        # Connect cities based on common divisors greater than threshold
        for i in range(threshold + 1, n + 1):
            for j in range(2 * i, n + 1, i):
                union_sets(i, j)

        # Process queries
        result = []
        for ai, bi in queries:
            result.append(find_set(ai) == find_set(bi))

        return result