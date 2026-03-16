# Source: https://leetcode.com/problems/most-profitable-path-in-a-tree/   |   Difficulty: Medium
#
# Problem Description:
# There is an undirected tree with n nodes labeled from 0 to n - 1, rooted at node 0. You are given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
#
# At every node i, there is a gate. You are also given an array of even integers amount, where amount[i] represents:
#
#
# 	the price needed to open the gate at node i, if amount[i] is negative, or,
# 	the cash reward obtained on opening the gate at node i, otherwise.
#
#
# The game goes on as follows:
#
#
# 	Initially, Alice is at node 0 and Bob is at node bob.
# 	At every second, Alice and Bob each move to an adjacent node. Alice moves towards some leaf node, while Bob moves towards node 0.
# 	For every node along their path, Alice and Bob either spend money to open the gate at that node, or accept the reward. Note that:
# 	
# 		If the gate is already open, no price will be required, nor will there be any cash reward.
# 		If Alice and Bob reach the node simultaneously, they share the price/reward for opening the gate there. In other words, if the price to open the gate is c, then both Alice and Bob pay c / 2 each. Similarly, if the reward at the gate is c, both of them receive c / 2 each.
# 	
# 	
# 	If Alice reaches a leaf node, she stops moving. Similarly, if Bob reaches node 0, he stops moving. Note that these events are independent of each other.
#
#
# Return the maximum net income Alice can have if she travels towards the optimal leaf node.
#
# Example:
# Input: edges = [[0,1],[1,2],[1,3],[3,4]], bob = 3, amount = [-2,4,2,-4,6]
# Output: 6
# Explanation: 
# The above diagram represents the given tree. The game goes as follows:
# - Alice is initially on node 0, Bob on node 3. They open the gates of their respective nodes.
#   Alice's net income is now -2.
# - Both Alice and Bob move to node 1. 
#   Since they reach here simultaneously, they open the gate together and share the reward.
#   Alice's net income becomes -2 + (4 / 2) = 0.
# - Alice moves on to node 3. Since Bob already opened its gate, Alice's income remains unchanged.
#   Bob moves on to node 0, and stops moving.
# - Alice moves on to node 4 and opens the gate there. Her net income becomes 0 + 6 = 6.
# Now, neither Alice nor Bob can make any further moves, and the game ends.
# It is not possible for Alice to get a higher net income.
#
# Constraints:
# 2 <= n <= 105
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	0 <= ai, bi < n
# 	ai != bi
# 	edges represents a valid tree.
# 	1 <= bob < n
# 	amount.length == n
# 	amount[i] is an even integer in the range [-104, 104].
#
# Helpful references (internal KB):
# - Breadth-first search (graph, deque, array, 01-bfs)
#   • When to use: When finding the shortest path in a graph where edge weights are restricted to 0 or 1, or when minimizing operations where some operations are 'free' (cost 0) and others have a unit cost (cost 1).
#   • Idea: A graph traversal algorithm that finds the shortest path from a source to all reachable nodes in a graph where edge weights are either 0 or 1. It uses a deque to prioritize 0-cost edges, achieving an optimal O(V + E) time complexity.
#   • Invariants: Nodes are added to the front of the deque if the edge weight is 0, and to the back if 1.; The distance `dist[u]` for any node `u` in the deque is either `k` or `k+1` for some integer `k`.
#   • Tips: Use a deque: push 0-cost edges to the front, 1-cost edges to the back.; Mark nodes visited to avoid cycles and redundant processing.
#   • Pitfalls: Incorrectly handling visited states can lead to infinite loops or incorrect paths.; Forgetting to initialize distances properly before starting the traversal.
# - 0-1 BFS (graph, array, dijkstra, bfs)
#   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
#   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
#   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
#   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
#   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
# - Breadth-first search (graph, array, bfs)
#   • When to use: Use when finding the shortest path or minimum number of edges between nodes in an unweighted graph, or to explore a graph layer by layer. It is also suitable for finding shortest cycles or identifying all components of shortest paths.
#   • Idea: Breadth-first search systematically explores a graph level by level, ensuring the shortest path in terms of edges is found from a source node to all reachable nodes. It operates in O(V + E) time complexity for adjacency list representation.
#   • Invariants: All nodes currently in the queue are at depth `k` or `k+1` from the source.; The distance recorded for any visited node is its shortest path length from the source.
#   • Tips: Run multiple BFS from different sources to find global properties like shortest cycles.; Maintain a distance array to record the shortest path length from the source to each node.
#   • Pitfalls: Applying BFS directly to weighted graphs will not yield shortest paths.; Failing to mark visited nodes can lead to infinite loops in cyclic graphs or incorrect path lengths.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def mostProfitablePath(self, edges, bob, amount):
        """
        :type edges: List[List[int]]
        :type bob: int
        :type amount: List[int]
        :rtype: int
        """
        from collections import defaultdict, deque

        n = len(amount)
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        # Step 1: Find Bob's path to the root (node 0) using BFS
        bob_path = [-1] * n
        bob_path[bob] = bob
        queue = deque([bob])
        while queue:
            node = queue.popleft()
            for neighbor in graph[node]:
                if bob_path[neighbor] == -1:
                    bob_path[neighbor] = node
                    queue.append(neighbor)

        # Step 2: Calculate Alice's net income for each node on Bob's path
        alice_income = [0] * n
        for i in range(n):
            if bob_path[i] != -1:
                alice_income[i] = amount[i] // 2  # Shared income if Bob is on the path
            else:
                alice_income[i] = amount[i]

        # Step 3: Use DFS to find the maximum net income for Alice from root to any leaf
        def dfs(node, parent):
            max_income = float('-inf')
            is_leaf = True
            for neighbor in graph[node]:
                if neighbor != parent:
                    is_leaf = False
                    max_income = max(max_income, dfs(neighbor, node))
            return alice_income[node] + (max_income if not is_leaf else 0)

        return dfs(0, -1)