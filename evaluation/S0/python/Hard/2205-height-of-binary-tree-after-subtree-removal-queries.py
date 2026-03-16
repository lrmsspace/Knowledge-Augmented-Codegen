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
        from collections import defaultdict
        
        depth = dict()
        height = dict()
        parent = dict()
        children = defaultdict(list)
        
        def dfs(node, d):
            if not node:
                return -1
            depth[node.val] = d
            left_h = dfs(node.left, d + 1)
            right_h = dfs(node.right, d + 1)
            height[node.val] = 1 + max(left_h, right_h)
            if node.left:
                parent[node.left.val] = node.val
                children[node.val].append(node.left.val)
            if node.right:
                parent[node.right.val] = node.val
                children[node.val].append(node.right.val)
            return height[node.val]
        
        dfs(root, 0)
        
        max_height_at_depth = defaultdict(list)
        for val in depth:
            d = depth[val]
            h = height[val]
            max_height_at_depth[d].append((h, val))
        
        for d in max_height_at_depth:
            max_height_at_depth[d].sort(reverse=True)
        
        result = []
        for q in queries:
            d = depth[q]
            hq = height[q]
            if len(max_height_at_depth[d]) == 1:
                result.append(d - 1)
            else:
                if max_height_at_depth[d][0][1] != q:
                    result.append(depth[root.val] + max_height_at_depth[d][0][0])
                else:
                    result.append(depth[root.val] + max_height_at_depth[d][1][0])
        
        return result