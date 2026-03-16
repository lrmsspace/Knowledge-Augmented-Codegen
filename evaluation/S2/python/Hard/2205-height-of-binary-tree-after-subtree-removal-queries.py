# Source: https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/   |   Difficulty: Hard
#
# Problem Description:
# You are given the root of a binary tree with n nodes. Each node is assigned a unique value from 1 to n. You are also given an array queries of size m.
#
# You have to perform m independent queries on the tree where in the ith query you do the following:
#
#
# 	Remove the subtree rooted at the node with the value queries[i] from the tree. It is guaranteed that queries[i] will not be equal to the value of the root.
#
#
# Return an array answer of size m where answer[i] is the height of the tree after performing the ith query.
#
# Note:
#
#
# 	The queries are independent, so the tree returns to its initial state after each query.
# 	The height of a tree is the number of edges in the longest simple path from the root to some node in the tree.
#
# Example:
# Input: root = [1,3,4,2,null,6,5,null,null,null,null,null,7], queries = [4]
# Output: [2]
# Explanation: The diagram above shows the tree after removing the subtree rooted at node with value 4.
# The height of the tree is 2 (The path 1 -> 3 -> 2).
#
# Constraints:
# The number of nodes in the tree is n.
# 	2 <= n <= 105
# 	1 <= Node.val <= n
# 	All the values in the tree are unique.
# 	m == queries.length
# 	1 <= m <= min(n, 104)
# 	1 <= queries[i] <= n
# 	queries[i] != root.val
#
# Helpful references (internal KB):
# - Lowest Common Ancestor (tree, array, dfs)
#   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
#   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
#   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
#   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
#   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
# - Prüfer code (tree, heap, simulation, greedy)
#   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
#   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
#   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
#   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
#   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
# - Deleting from a data structure in_log_n (ds, segment-tree, dfs, recursion)
#   • When to use: Use when processing a sequence of additions, deletions, and queries offline, where elements have specific time intervals of existence. It efficiently handles dynamic data structure operations by leveraging a segment tree over time.
#   • Idea: This technique uses a segment tree over the timeline of queries to manage elements with varying lifespans. Queries are processed offline via DFS, adding elements upon entering a node and undoing additions upon exiting, achieving O(T(n) log n) deletion complexity.
#   • Invariants: When entering a segment tree node, all elements associated with that node's time range are added to the active data structure.; When exiting a segment tree node, all elements added upon entry are removed, restoring the data structure to its state before entering.
#   • Tips: Ensure the base data structure supports efficient addition and undo operations.; Carefully manage element additions and removals during DFS traversal.
#   • Pitfalls: Forgetting to undo changes when backtracking from a segment tree node.; Incorrectly mapping element lifespans to segment tree nodes.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def treeQueries(self, root, queries):
        """
        :type root: Optional[TreeNode]
        :type queries: List[int]
        :rtype: List[int]
        """
        # Step 1: DFS to compute height and depth of each node
        height = {}
        depth = {}
        
        def dfs(node, d):
            if not node:
                return -1
            depth[node.val] = d
            left_height = dfs(node.left, d + 1)
            right_height = dfs(node.right, d + 1)
            height[node.val] = max(left_height, right_height) + 1
            return height[node.val]
        
        dfs(root, 0)
        
        # Step 2: Compute the maximum height of the tree after removing each subtree
        max_height_after_removal = {}
        
        def compute_max_height(node):
            if not node:
                return -1
            
            left_max = compute_max_height(node.left)
            right_max = compute_max_height(node.right)
            
            max_height_after_removal[node.val] = max(left_max, right_max)
            
            return max(height[node.val], max(left_max, right_max) + 1)
        
        compute_max_height(root)
        
        # Step 3: Prepare the answer for each query
        answer = []
        for q in queries:
            answer.append(max_height_after_removal[q])
        
        return answer