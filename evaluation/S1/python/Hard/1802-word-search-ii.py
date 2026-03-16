# Source: https://leetcode.com/problems/word-search-ii/   |   Difficulty: Hard
#
# Problem Description:
# Given an m x n board of characters and a list of strings words, return all words on the board.
#
# Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
#
# Example:
# Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], words = ["oath","pea","eat","rain"]
# Output: ["eat","oath"]
#
# Constraints:
# m == board.length
# 	n == board[i].length
# 	1 <= m, n <= 12
# 	board[i][j] is a lowercase English letter.
# 	1 <= words.length <= 3 * 104
# 	1 <= words[i].length <= 10
# 	words[i] consists of lowercase English letters.
# 	All the strings of words are unique.
#
# Helpful references (internal KB):
# - Tries (trie, tree, trie-match)
#   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
#   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
#   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
#   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
#   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
# - Depth-first search (graph, array, stack, dfs)
#   • When to use: Use when you need to explore all reachable vertices from a starting point or systematically visit all nodes in a graph or tree. It's suitable for problems requiring full exploration of a branch before backtracking.
#   • Idea: Depth-first search is an algorithm for traversing or searching tree or graph data structures. It explores as far as possible along each branch before backtracking, typically using a stack (explicit or implicit via recursion).
#   • Invariants: Every node `v` in the graph is either visited or not yet visited.; The recursion stack (or explicit stack) always contains a path from the source node to the current node being explored.
#   • Tips: Use a `visited` array or set to prevent cycles and redundant work.; Recursion is often cleaner for implementation, but iterative DFS with an explicit stack avoids recursion depth limits.
#   • Pitfalls: Stack overflow can occur with deep recursion on large graphs.; Forgetting to mark nodes as visited leads to infinite loops in cyclic graphs.
# - Suffix array (array, string, suffix-array, divide-and-conquer, recursion)
#   • When to use: Use when you need to efficiently perform various string operations like pattern searching, finding repeated substrings, or comparing suffixes lexicographically on a given text. It is a fundamental data structure for advanced string algorithms.
#   • Idea: A suffix array is a sorted array of all suffixes of a given string. It allows for efficient string operations, with construction typically achievable in O(N log N) or O(N) time for advanced algorithms.
#   • Invariants: The suffix array SA[i] stores the starting index of the i-th lexicographically smallest suffix.; All suffixes of the input string are present exactly once in the suffix array.
#   • Tips: Consider using SA-IS for optimal O(N) construction time and space complexity.; Pair the suffix array with an LCP array for enhanced functionality, such as finding longest common substrings.
#   • Pitfalls: Naive O(N^2 log N) construction is too slow for large input strings.; Implementing linear-time algorithms like SA-IS or DC3 can be complex and error-prone.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findWords(self, board, words):
        """
        :type board: List[List[str]]
        :type words: List[str]
        :rtype: List[str]
        """
        # Step 1: Build a trie from the list of words
        trie = {}
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
            node['#'] = True  # Mark the end of a word

        # Step 2: Perform DFS on the board to find words in the trie
        rows, cols = len(board), len(board[0])
        found_words = set()

        def dfs(r, c, node, path):
            if '#' in node:
                found_words.add(path)  # Found a complete word

            if r < 0 or r >= rows or c < 0 or c >= cols or board[r][c] not in node:
                return

            char = board[r][c]
            board[r][c] = '#'  # Mark as visited
            dfs(r + 1, c, node[char], path + char)
            dfs(r - 1, c, node[char], path + char)
            dfs(r, c + 1, node[char], path + char)
            dfs(r, c - 1, node[char], path + char)
            board[r][c] = char  # Unmark

        for i in range(rows):
            for j in range(cols):
                dfs(i, j, trie, "")

        return list(found_words)