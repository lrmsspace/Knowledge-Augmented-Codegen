# Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-x-and-y-equal/   |   Difficulty: Medium
#
# Problem Description:
# You are given two positive integers x and y.
#
# In one operation, you can do one of the four following operations:
#
#
# 	Divide x by 11 if x is a multiple of 11.
# 	Divide x by 5 if x is a multiple of 5.
# 	Decrement x by 1.
# 	Increment x by 1.
#
#
# Return the minimum number of operations required to make  x and y equal.
#
# Example:
# Input: x = 26, y = 1
# Output: 3
# Explanation: We can make 26 equal to 1 by applying the following operations: 
# 1. Decrement x by 1
# 2. Divide x by 5
# 3. Divide x by 5
# It can be shown that 3 is the minimum number of operations required to make 26 equal to 1.
#
# Constraints:
# 1 <= x, y <= 104
#
# Helpful references (internal KB):
# - Breadth-first search (graph, queue, array, bfs)
#   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
#   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
#   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
#   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
# - Minimum stack / Minimum queue (stack, simulation)
#   • When to use: When you need to perform standard stack operations (push, pop) and also query the minimum element currently in the stack, all in constant time.
#   • Idea: Augments a standard stack by storing each element along with the minimum value encountered up to that point in the stack. This allows O(1) retrieval of the current minimum, while push and pop operations also remain O(1).
#   • Invariants: The top element's second component (minimum_so_far) always represents the minimum value currently in the entire stack.; For any element (value, min_so_far) in the stack, min_so_far is the minimum of 'value' and all elements below it.
#   • Tips: Store elements as pairs: (actual_value, minimum_at_this_level).; When pushing, the new minimum_at_this_level is min(new_value, stack.top().second) if stack is not empty, else new_value.
#   • Pitfalls: Forgetting to handle the empty stack case when calculating the minimum for a new element.; Incorrectly assuming the minimum can be tracked with a single auxiliary variable without considering pops.
# - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
#   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
#   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
#   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
#   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
#   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumOperationsToMakeEqual(self, x, y):
        """
        :type x: int
        :type y: int
        :rtype: int
        """
        from collections import deque

        if x == y:
            return 0

        queue = deque([(x, 0)])  # (current value, operations count)
        visited = set([x])

        while queue:
            current, ops = queue.popleft()

            for next_val in (current // 11 if current % 11 == 0 else None,
                             current // 5 if current % 5 == 0 else None,
                             current - 1,
                             current + 1):
                if next_val is not None and next_val not in visited:
                    if next_val == y:
                        return ops + 1
                    visited.add(next_val)
                    queue.append((next_val, ops + 1))

        return -1  # Should never reach here for valid inputs