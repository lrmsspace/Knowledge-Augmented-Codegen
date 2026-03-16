# Source: https://leetcode.com/problems/binary-tree-coloring-game/   |   Difficulty: Medium
#
# Problem Description:
# Two players play a turn based game on a binary tree. We are given the root of this binary tree, and the number of nodes n in the tree. n is odd, and each node has a distinct value from 1 to n.
#
# Initially, the first player names a value x with 1 <= x <= n, and the second player names a value y with 1 <= y <= n and y != x. The first player colors the node with value x red, and the second player colors the node with value y blue.
#
# Then, the players take turns starting with the first player. In each turn, that player chooses a node of their color (red if player 1, blue if player 2) and colors an uncolored neighbor of the chosen node (either the left child, right child, or parent of the chosen node.)
#
# If (and only if) a player cannot choose such a node in this way, they must pass their turn. If both players pass their turn, the game ends, and the winner is the player that colored more nodes.
#
# You are the second player. If it is possible to choose such a y to ensure you win the game, return true. If it is not possible, return false.
#
# Example:
# Input: root = [1,2,3,4,5,6,7,8,9,10,11], n = 11, x = 3
# Output: true
# Explanation: The second player can choose the node with value 2.
#
# Constraints:
# The number of nodes in the tree is n.
# 	1 <= x <= n <= 100
# 	n is odd.
# 	1 <= Node.val <= n
# 	All the values of the tree are unique.
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def btreeGameWinningMove(self, root, n, x):
        """
        :type root: Optional[TreeNode]
        :type n: int
        :type x: int
        :rtype: bool
        """
        def count_nodes(node):
            if not node:
                return 0
            return 1 + count_nodes(node.left) + count_nodes(node.right)

        def find_x_and_count(node):
            if not node:
                return None, 0
            if node.val == x:
                left_count = count_nodes(node.left)
                right_count = count_nodes(node.right)
                return (left_count, right_count), 1 + left_count + right_count
            left_result, left_total = find_x_and_count(node.left)
            if left_result is not None:
                return left_result, left_total
            right_result, right_total = find_x_and_count(node.right)
            if right_result is not None:
                return right_result, right_total
            return None, 1 + left_total + right_total

        (left_size, right_size), _ = find_x_and_count(root)
        parent_size = n - (left_size + right_size + 1)

        max_region = max(left_size, right_size, parent_size)
        return max_region > n // 2