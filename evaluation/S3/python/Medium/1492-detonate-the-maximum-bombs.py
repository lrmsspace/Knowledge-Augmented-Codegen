# Source: https://leetcode.com/problems/detonate-the-maximum-bombs/   |   Difficulty: Medium
#
# Problem Description:
# You are given a list of bombs. The range of a bomb is defined as the area where its effect can be felt. This area is in the shape of a circle with the center as the location of the bomb.
#
# The bombs are represented by a 0-indexed 2D integer array bombs where bombs[i] = [xi, yi, ri]. xi and yi denote the X-coordinate and Y-coordinate of the location of the ith bomb, whereas ri denotes the radius of its range.
#
# You may choose to detonate a single bomb. When a bomb is detonated, it will detonate all bombs that lie in its range. These bombs will further detonate the bombs that lie in their ranges.
#
# Given the list of bombs, return the maximum number of bombs that can be detonated if you are allowed to detonate only one bomb.
#
# Example:
# Input: bombs = [[2,1,3],[6,1,4]]
# Output: 2
# Explanation:
# The above figure shows the positions and ranges of the 2 bombs.
# If we detonate the left bomb, the right bomb will not be affected.
# But if we detonate the right bomb, both bombs will be detonated.
# So the maximum bombs that can be detonated is max(1, 2) = 2.
#
# Constraints:
# 1 <= bombs.length <= 100
# 	bombs[i].length == 3
# 	1 <= xi, yi, ri <= 105
#
# Helpful references (internal KB):
# - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
#   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
#   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
#   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
#   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
#   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
# - Directed Graphs (graph, array, dfs, bfs)
#   • When to use: Use when modeling relationships with a specific flow direction between entities. It is ideal for determining reachability or finding paths from one or more sources.
#   • Idea: Directed graphs represent connections where edges have a specific direction, often implemented using adjacency lists. Depth-first search (DFS) and breadth-first search (BFS) are fundamental algorithms for traversing these graphs to find paths and determine reachability in O(V+E) time.
#   • Invariants: The 'visited' set accurately reflects all nodes for which traversal has been initiated.; For DFS, all nodes reachable from the current node via unvisited paths will eventually be explored.
#   • Tips: Always use a 'visited' set or array to prevent infinite loops in cycles and redundant processing.; Adjacency list representation is generally preferred for sparse graphs due to better space and time complexity for traversal.
#   • Pitfalls: Forgetting to handle cycles can lead to infinite loops or stack overflows in DFS.; Incorrectly applying algorithms designed for undirected graphs to directed graphs without modification.
# - Strongly connected components and the condensation graph (graph, enumeration)
#   • When to use: When you need to identify maximal subgraphs where all vertices are mutually reachable, or to simplify a directed graph into a Directed Acyclic Graph (DAG) of components for further processing.
#   • Idea: This concept defines SCCs as maximal vertex subsets in a directed graph where all pairs are mutually reachable. It also introduces the condensation graph, which represents SCCs as nodes and forms a DAG, typically found in O(V+E) time.
#   • Invariants: Every vertex belongs to exactly one strongly connected component.; Within any SCC, a path exists from any vertex u to any other vertex v, and vice-versa.
#   • Tips: Understand that SCCs partition the graph's vertices.; The condensation graph is always a Directed Acyclic Graph (DAG).
#   • Pitfalls: Confusing SCCs with simple cycles or connected components in undirected graphs.; Incorrectly assuming the condensation graph has cycles.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maximumDetonation(self, bombs):
        """
        :type bombs: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict

        n = len(bombs)
        graph = defaultdict(list)

        # Build the directed graph based on bomb ranges
        for i in range(n):
            x1, y1, r1 = bombs[i]
            for j in range(n):
                if i != j:
                    x2, y2, _ = bombs[j]
                    if (x1 - x2) ** 2 + (y1 - y2) ** 2 <= r1 ** 2:
                        graph[i].append(j)

        def dfs(node, visited):
            visited.add(node)
            count = 1
            for neighbor in graph[node]:
                if neighbor not in visited:
                    count += dfs(neighbor, visited)
            return count

        max_detonations = 0
        for i in range(n):
            visited = set()
            max_detonations = max(max_detonations, dfs(i, visited))

        return max_detonations