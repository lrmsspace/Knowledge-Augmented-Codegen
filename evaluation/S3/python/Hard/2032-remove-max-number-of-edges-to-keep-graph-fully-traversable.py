# Source: https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/   |   Difficulty: Hard
#
# Problem Description:
# Alice and Bob have an undirected graph of n nodes and three types of edges:
#
#
# 	Type 1: Can be traversed by Alice only.
# 	Type 2: Can be traversed by Bob only.
# 	Type 3: Can be traversed by both Alice and Bob.
#
#
# Given an array edges where edges[i] = [typei, ui, vi] represents a bidirectional edge of type typei between nodes ui and vi, find the maximum number of edges you can remove so that after removing the edges, the graph can still be fully traversed by both Alice and Bob. The graph is fully traversed by Alice and Bob if starting from any node, they can reach all other nodes.
#
# Return the maximum number of edges you can remove, or return -1 if Alice and Bob cannot fully traverse the graph.
#
# Example:
# Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
# Output: 2
# Explanation: If we remove the 2 edges [1,1,2] and [1,1,3]. The graph will still be fully traversable by Alice and Bob. Removing any additional edge will not make it so. So the maximum number of edges we can remove is 2.
#
# Constraints:
# 1 <= n <= 105
# 	1 <= edges.length <= min(105, 3 * n * (n - 1) / 2)
# 	edges[i].length == 3
# 	1 <= typei <= 3
# 	1 <= ui < vi <= n
# 	All tuples (typei, ui, vi) are distinct.
#
# Helpful references (internal KB):
# - Disjoint Set Union (ds, tree, array, union-find)
#   • When to use: Use when you need to maintain a collection of disjoint sets and efficiently perform union operations to merge sets or find the representative of an element's set.
#   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. With path compression and union by rank/size, these operations achieve nearly constant amortized time complexity, O(alpha(N)).
#   • Invariants: Each element `v` is either a root (parent[v] == v) or has a parent pointer to another element in its set.; The `find_set` operation, after path compression, ensures that all nodes on the path from `v` to its root directly point to the root.
#   • Tips: Implement path compression in `find_set` for optimal performance.; Use union by rank or union by size to keep trees flat and balanced.
#   • Pitfalls: Forgetting path compression or union by rank/size leads to O(N) worst-case operations.; Incorrectly merging sets by only updating one root without considering the other's rank/size.
# - Disjoint Set Union (ds, linked-list, union-find, dfs)
#   • When to use: Use when you need to maintain a collection of disjoint sets and perform union operations to merge sets or find the representative of an element's set efficiently. It's suitable for problems involving dynamic connectivity or grouping elements.
#   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. It achieves nearly constant time complexity for these operations with path compression and union by rank/size optimizations.
#   • Invariants: Every element `i` belongs to exactly one set, represented by `find(i)`.; If `parent[i] == i`, then `i` is the representative (root) of its set.
#   • Tips: Implement path compression in `find` for optimal performance.; Use union by size or rank to maintain balanced trees.
#   • Pitfalls: Omitting path compression or union by rank/size can degrade performance to O(N).; Failing to correctly update auxiliary data stored at representatives during a union operation.
# - Disjoint Set Union (ds, tree, array, union-find)
#   • When to use: Use when you need to efficiently manage a collection of disjoint sets, supporting operations to merge sets and determine if two elements belong to the same set.
#   • Idea: Disjoint Set Union (DSU) is a data structure that maintains a collection of disjoint sets and supports two primary operations: union (merging two sets) and find (determining the representative of an element's set). With path compression and union by rank/size, operations achieve nearly O(1) amortized time complexity.
#   • Invariants: For any element `v`, `parent[v]` is either `v` itself (if `v` is a root) or an ancestor of `v`.; All elements belonging to the same set share a common root representative.
#   • Tips: Apply path compression during `find_set` to optimize future queries.; Utilize union by rank or size to maintain balanced trees.
#   • Pitfalls: Omitting path compression or union by rank/size results in poor performance.; Failing to correctly identify the root of a set in `find_set`.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxNumEdgesToRemove(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: int
        """
        # Disjoint Set Union (Union-Find) implementation
        class DSU:
            def __init__(self, size):
                self.parent = list(range(size))
                self.rank = [1] * size
            
            def find(self, x):
                if self.parent[x] != x:
                    self.parent[x] = self.find(self.parent[x])  # Path compression
                return self.parent[x]
            
            def union(self, x, y):
                rootX = self.find(x)
                rootY = self.find(y)
                
                if rootX != rootY:
                    # Union by rank
                    if self.rank[rootX] > self.rank[rootY]:
                        self.parent[rootY] = rootX
                    elif self.rank[rootX] < self.rank[rootY]:
                        self.parent[rootX] = rootY
                    else:
                        self.parent[rootY] = rootX
                        self.rank[rootX] += 1
                    return True
                return False
        
        alice_dsu = DSU(n)
        bob_dsu = DSU(n)
        edges_used = 0
        
        # Process type 3 edges first (shared by Alice and Bob)
        for t, u, v in edges:
            if t == 3:
                if alice_dsu.union(u - 1, v - 1):  # Use zero-based index
                    bob_dsu.union(u - 1, v - 1)  # Ensure Bob's DSU is also updated
                    edges_used += 1
        
        # Process type 1 edges (Alice only)
        for t, u, v in edges:
            if t == 1:
                if alice_dsu.union(u - 1, v - 1):
                    edges_used += 1
        
        # Process type 2 edges (Bob only)
        for t, u, v in edges:
            if t == 2:
                if bob_dsu.union(u - 1, v - 1):
                    edges_used += 1
        
        # Check if both Alice and Bob can traverse the entire graph
        alice_connected = len(set(alice_dsu.find(i) for i in range(n))) == 1
        bob_connected = len(set(bob_dsu.find(i) for i in range(n))) == 1
        
        if alice_connected and bob_connected:
            return len(edges) - edges_used
        else:
            return -