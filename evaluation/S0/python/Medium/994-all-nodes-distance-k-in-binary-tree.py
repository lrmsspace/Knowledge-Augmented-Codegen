# Source: https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/   |   Difficulty: Medium
#
# Problem Description:
# Given the root of a binary tree, the value of a target node target, and an integer k, return an array of the values of all nodes that have a distance k from the target node.
#
# You can return the answer in any order.
#
# Example:
# Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
# Output: [7,4,1]
# Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 500].
# 	0 <= Node.val <= 500
# 	All the values Node.val are unique.
# 	target is the value of one of the nodes in the tree.
# 	0 <= k <= 1000
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution(object):
    def distanceK(self, root, target, k):
        """
        :type root: TreeNode
        :type target: TreeNode
        :type k: int
        :rtype: List[int]
        """
        from collections import defaultdict, deque

        graph = defaultdict(list)

        def build_graph(node, parent):
            if node:
                if parent:
                    graph[node.val].append(parent.val)
                    graph[parent.val].append(node.val)
                build_graph(node.left, node)
                build_graph(node.right, node)

        build_graph(root, None)

        result = []
        visited = set()
        queue = deque([(target.val, 0)])
        visited.add(target.val)

        while queue:
            current_node, current_distance = queue.popleft()

            if current_distance == k:
                result.append(current_node)

            for neighbor in graph[current_node]:
                if neighbor not in visited:
                    visited.add(neighbor)
                    queue.append((neighbor, current_distance + 1))

        return result