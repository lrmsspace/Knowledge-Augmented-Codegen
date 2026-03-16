# Source: https://leetcode.com/problems/closest-nodes-queries-in-a-binary-search-tree/   |   Difficulty: Medium
#
# Problem Description:
# You are given the root of a binary search tree and an array queries of size n consisting of positive integers.
#
# Find a 2D array answer of size n where answer[i] = [mini, maxi]:
#
#
# 	mini is the largest value in the tree that is smaller than or equal to queries[i]. If a such value does not exist, add -1 instead.
# 	maxi is the smallest value in the tree that is greater than or equal to queries[i]. If a such value does not exist, add -1 instead.
#
#
# Return the array answer.
#
# Example:
# Input: root = [6,2,13,1,4,9,15,null,null,null,null,null,null,14], queries = [2,5,16]
# Output: [[2,2],[4,6],[15,-1]]
# Explanation: We answer the queries in the following way:
# - The largest number that is smaller or equal than 2 in the tree is 2, and the smallest number that is greater or equal than 2 is still 2. So the answer for the first query is [2,2].
# - The largest number that is smaller or equal than 5 in the tree is 4, and the smallest number that is greater or equal than 5 is 6. So the answer for the second query is [4,6].
# - The largest number that is smaller or equal than 16 in the tree is 15, and the smallest number that is greater or equal than 16 does not exist. So the answer for the third query is [15,-1].
#
# Constraints:
# The number of nodes in the tree is in the range [2, 105].
# 	1 <= Node.val <= 106
# 	n == queries.length
# 	1 <= n <= 105
# 	1 <= queries[i] <= 106
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def closestNodes(self, root, queries):
        """
        :type root: Optional[TreeNode]
        :type queries: List[int]
        :rtype: List[List[int]]
        """
        sorted_vals = []
        
        def inorder_traversal(node):
            if not node:
                return
            inorder_traversal(node.left)
            sorted_vals.append(node.val)
            inorder_traversal(node.right)
        
        inorder_traversal(root)
        
        import bisect
        result = []
        
        for query in queries:
            idx = bisect.bisect_left(sorted_vals, query)
            
            # Find mini
            if idx > 0 and sorted_vals[idx - 1] <= query:
                mini = sorted_vals[idx - 1]
            else:
                mini = -1
            
            # Find maxi
            if idx < len(sorted_vals) and sorted_vals[idx] >= query:
                maxi = sorted_vals[idx]
            else:
                maxi = -1
            
            result.append([mini, maxi])
        
        return result