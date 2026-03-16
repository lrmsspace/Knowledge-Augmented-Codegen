# Source: https://leetcode.com/problems/amount-of-time-for-binary-tree-to-be-infected/   |   Difficulty: Medium
#
# Problem Description:
# You are given the root of a binary tree with unique values, and an integer start. At minute 0, an infection starts from the node with value start.
#
# Each minute, a node becomes infected if:
#
#
# 	The node is currently uninfected.
# 	The node is adjacent to an infected node.
#
#
# Return the number of minutes needed for the entire tree to be infected.
#
# Example:
# Input: root = [1,5,3,null,4,10,6,9,2], start = 3
# Output: 4
# Explanation: The following nodes are infected during:
# - Minute 0: Node 3
# - Minute 1: Nodes 1, 10 and 6
# - Minute 2: Node 5
# - Minute 3: Node 4
# - Minute 4: Nodes 9 and 2
# It takes 4 minutes for the whole tree to be infected so we return 4.
#
# Constraints:
# The number of nodes in the tree is in the range [1, 105].
# 	1 <= Node.val <= 105
# 	Each node has a unique value.
# 	A node with a value of start exists in the tree.
#

# Definition for a binary tree node.
# class TreeNode(object):
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution(object):
    def amountOfTime(self, root, start):
        """
        :type root: Optional[TreeNode]
        :type start: int
        :rtype: int
        """
        from collections import defaultdict, deque

        graph = defaultdict(list)

        def build_graph(node):
            if not node:
                return
            if node.left:
                graph[node.val].append(node.left.val)
                graph[node.left.val].append(node.val)
                build_graph(node.left)
            if node.right:
                graph[node.val].append(node.right.val)
                graph[node.right.val].append(node.val)
                build_graph(node.right)

        build_graph(root)

        visited = set()
        queue = deque([start])
        visited.add(start)
        time = -1

        while queue:
            time += 1
            for _ in range(len(queue)):
                current = queue.popleft()
                for neighbor in graph[current]:
                    if neighbor not in visited:
                        visited.add(neighbor)
                        queue.append(neighbor)

        return time