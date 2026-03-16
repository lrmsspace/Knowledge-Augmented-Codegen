# Source: https://leetcode.com/problems/find-all-possible-recipes-from-given-supplies/   |   Difficulty: Medium
#
# Problem Description:
# You have information about n different recipes. You are given a string array recipes and a 2D string array ingredients. The ith recipe has the name recipes[i], and you can create it if you have all the needed ingredients from ingredients[i]. A recipe can also be an ingredient for other recipes, i.e., ingredients[i] may contain a string that is in recipes.
#
# You are also given a string array supplies containing all the ingredients that you initially have, and you have an infinite supply of all of them.
#
# Return a list of all the recipes that you can create. You may return the answer in any order.
#
# Note that two recipes may contain each other in their ingredients.
#
# Example:
# Input: recipes = ["bread"], ingredients = [["yeast","flour"]], supplies = ["yeast","flour","corn"]
# Output: ["bread"]
# Explanation:
# We can create "bread" since we have the ingredients "yeast" and "flour".
#
# Constraints:
# n == recipes.length == ingredients.length
# 	1 <= n <= 100
# 	1 <= ingredients[i].length, supplies.length <= 100
# 	1 <= recipes[i].length, ingredients[i][j].length, supplies[k].length <= 10
# 	recipes[i], ingredients[i][j], and supplies[k] consist only of lowercase English letters.
# 	All the values of recipes and supplies combined are unique.
# 	Each ingredients[i] does not contain any duplicate values.
#
# Helpful references (internal KB):
# - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
#   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
#   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
#   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
#   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
#   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
# - Aho-Corasick Algorithm for Pattern Searching (string, trie, aho-corasick, simulation)
#   • When to use: Use when you need to find all occurrences of a fixed set of patterns within a larger text efficiently. It's particularly effective for scenarios involving many patterns and potential overlaps.
#   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses it to find all occurrences of these patterns in a text in a single pass. It operates in O(N + M + K) time, where N is text length, M is total pattern length, and K is total matches.
#   • Invariants: All patterns in the dictionary are correctly represented in the trie (goto function).; The failure link `f[u]` for any state `u` points to the state representing the longest proper suffix of the string corresponding to `u` that is also a prefix of some pattern.
#   • Tips: Build the trie (goto function) first from all patterns.; Construct failure links using a BFS-like approach to ensure correct shortest suffix matching.
#   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to propagate output matches through failure links can miss valid pattern occurrences.
# - Multi source BFS (queue, graph, multi-source-bfs, bfs)
#   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
#   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
#   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
#   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
#   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findAllRecipes(self, recipes, ingredients, supplies):
        """
        :type recipes: List[str]
        :type ingredients: List[List[str]]
        :type supplies: List[str]
        :rtype: List[str]
        """
        from collections import defaultdict, deque

        # Build the graph and in-degree count
        graph = defaultdict(list)
        in_degree = {recipe: 0 for recipe in recipes}

        for recipe, ing_list in zip(recipes, ingredients):
            for ing in ing_list:
                graph[ing].append(recipe)
                in_degree[recipe] += 1

        # Initialize the queue with supplies (initially available ingredients)
        queue = deque(supplies)
        result = []

        while queue:
            current = queue.popleft()
            if current in in_degree:
                result.append(current)  # Current is a recipe we can make
                for neighbor in graph[current]:
                    in_degree[neighbor] -= 1
                    if in_degree[neighbor] == 0:
                        queue.append(neighbor)

        return result