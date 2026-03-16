# Source: https://leetcode.com/problems/k-th-largest-perfect-subtree-size-in-binary-tree/   |   Difficulty: Medium
#
# Problem Description:
# You are given the root of a binary tree and an integer k.
#
# Return an integer denoting the size of the kth largest perfect binary subtree, or -1 if it doesn't exist.
#
# A perfect binary tree is a tree where all leaves are on the same level, and every parent has two children.
#
# Example:
# Input: root = [5,3,6,5,2,5,7,1,8,null,null,6,8], k = 2
#
# Output: 3
#
# Explanation:
#
#
#
# The roots of the perfect binary subtrees are highlighted in black. Their sizes, in non-increasing order are [3, 3, 1, 1, 1, 1, 1, 1].
# The 2nd largest size is 3.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 2000].
# 	1 <= Node.val <= 2000
# 	1 <= k <= 1024
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def kthLargestPerfectSubtree(self, root, k):
        """
        :type root: Optional[TreeNode]
        :type k: int
        :rtype: int
        """
        perfect_sizes = []

        def dfs(node):
            if not node:
                return 0, True

            left_size, is_left_perfect = dfs(node.left)
            right_size, is_right_perfect = dfs(node.right)

            if is_left_perfect and is_right_perfect and left_size == right_size:
                curr_size = left_size + right_size + 1
                perfect_sizes.append(curr_size)
                return curr_size, True
            else:
                return 0, False

        dfs(root)
        perfect_sizes.sort(reverse=True)

        if k <= len(perfect_sizes):
            return perfect_sizes[k - 1]
        else:
            return -1