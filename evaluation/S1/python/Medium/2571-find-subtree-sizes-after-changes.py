# Source: https://leetcode.com/problems/find-subtree-sizes-after-changes/   |   Difficulty: Medium
#
# Problem Description:
# You are given a tree rooted at node 0 that consists of n nodes numbered from 0 to n - 1. The tree is represented by an array parent of size n, where parent[i] is the parent of node i. Since node 0 is the root, parent[0] == -1.
#
# You are also given a string s of length n, where s[i] is the character assigned to node i.
#
# We make the following changes on the tree one time simultaneously for all nodes x from 1 to n - 1:
#
#
# 	Find the closest node y to node x such that y is an ancestor of x, and s[x] == s[y].
# 	If node y does not exist, do nothing.
# 	Otherwise, remove the edge between x and its current parent and make node y the new parent of x by adding an edge between them.
#
#
# Return an array answer of size n where answer[i] is the size of the subtree rooted at node i in the final tree.
#
# Example:
# Input: parent = [-1,0,0,1,1,1], s = "abaabc"
#
# Output: [6,3,1,1,1,1]
#
# Explanation:
#
# The parent of node 3 will change from node 1 to node 0.
#
# Constraints:
# n == parent.length == s.length
# 	1 <= n <= 105
# 	0 <= parent[i] <= n - 1 for all i >= 1.
# 	parent[0] == -1
# 	parent represents a valid tree.
# 	s consists only of lowercase English letters.
#
# Helpful references (internal KB):
# - Lowest Common Ancestor (tree, array, dfs)
#   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
#   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
#   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
#   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
#   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
# - Depth First Search (tree, graph, dfs)
#   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
#   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
#   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
#   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
#   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
# - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
#   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
#   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
#   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
#   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
#   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findSubtreeSizes(self, parent, s):
        """
        :type parent: List[int]
        :type s: str
        :rtype: List[int]
        """
        from collections import defaultdict, Counter
        
        n = len(parent)
        tree = defaultdict(list)
        for child in range(1, n):
            tree[parent[child]].append(child)
        
        result = [0] * n
        
        def dfs(node):
            count = Counter()
            count[s[node]] += 1
            
            for child in tree[node]:
                child_count = dfs(child)
                
                for char, freq in child_count.items():
                    if char == s[node]:
                        continue
                    count[char] += freq
            
            result[node] = sum(count.values())
            return count
        
        dfs(0)
        return result