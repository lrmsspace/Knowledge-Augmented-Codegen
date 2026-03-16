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
# - 0-1 BFS (graph, deque, 01-bfs, bfs)
#   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
#   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
#   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
#   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
#   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
# - Depth First Search (tree, graph, dfs)
#   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
#   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
#   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
#   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
#   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
# - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
#   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
#   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
#   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
#   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
#   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
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
        parent = [-1] * n
        def dfs_bob(node, par):
            parent[node] = par
            for nei in graph[node]:
                if nei != par:
                    dfs_bob(nei, node)

        dfs_bob(0, -1)

        bob_path = []
        while bob != -1:
            bob_path.append(bob)
            bob = parent[bob]
        bob_path.reverse()

        # Step 2: Determine the time Bob reaches each node
        bob_time = {}
        for t, node in enumerate(bob_path):
            bob_time[node] = t

        # Step 3: DFS for Alice to find the most profitable path
        max_profit = float('-inf')

        def dfs_alice(node, par, time, current_profit):
            nonlocal max_profit
            # Calculate profit at this node
            if node in bob_time:
                if time < bob_time[node]:
                    current_profit += amount[node]
                elif time == bob_time[node]:
                    current_profit += amount[node] // 2
                # If time > bob_time[node], Bob has already opened the gate
            else:
                current_profit += amount[node]

            # Check if it's a leaf node
            is_leaf = True
            for nei in graph[node]:
                if nei != par:
                    is_leaf = False
                    dfs_alice(nei, node, time + 1, current_profit)

            if is_leaf:
                max_profit = max(max_profit, current_profit)

        dfs_alice(0, -1, 0, 0)
        return max_profit