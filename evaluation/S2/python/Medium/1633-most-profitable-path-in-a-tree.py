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
# - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
#   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
#   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
#   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
#   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
#   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
# - Games on arbitrary graphs (graph, array, dfs, game-theory)
#   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
#   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
#   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
#   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
#   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
# - Check whether a graph is bipartite (graph, queue, bfs)
#   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
#   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
#   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
#   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
#   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
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

        # Step 1: Find Bob's path to the root (node 0)
        bob_path = []
        visited = [False] * n
        def dfs(node):
            visited[node] = True
            bob_path.append(node)
            if node == 0:
                return True
            for neighbor in graph[node]:
                if not visited[neighbor]:
                    if dfs(neighbor):
                        return True
            bob_path.pop()
            return False
        
        dfs(bob)

        # Step 2: Create a map of Bob's arrival times at each node
        bob_time = {node: i for i, node in enumerate(bob_path)}

        # Step 3: DFS to find the maximum profit for Alice
        max_profit = float('-inf')
        visited = [False] * n

        def dfs_alice(node, time, profit):
            nonlocal max_profit
            visited[node] = True
            
            # Calculate profit at this node considering Bob's presence
            if node in bob_time:
                if time < bob_time[node]:  # Alice arrives before Bob
                    profit += amount[node]
                elif time == bob_time[node]:  # Alice and Bob arrive simultaneously
                    profit += amount[node] // 2
            
            # Check if it's a leaf node (no unvisited neighbors)
            is_leaf = True
            for neighbor in graph[node]:
                if not visited[neighbor]:
                    is_leaf = False
                    dfs_alice(neighbor, time + 1, profit)
            
            if is_leaf:
                max_profit = max(max_profit, profit)

            visited[node] = False

        dfs_alice(0, 0, 0)
        
        return max_profit