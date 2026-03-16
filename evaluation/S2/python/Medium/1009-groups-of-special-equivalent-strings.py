# Source: https://leetcode.com/problems/groups-of-special-equivalent-strings/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of strings of the same length words.
#
# In one move, you can swap any two even indexed characters or any two odd indexed characters of a string words[i].
#
# Two strings words[i] and words[j] are special-equivalent if after any number of moves, words[i] == words[j].
#
#
# 	For example, words[i] = "zzxy" and words[j] = "xyzz" are special-equivalent because we may make the moves "zzxy" -> "xzzy" -> "xyzz".
#
#
# A group of special-equivalent strings from words is a non-empty subset of words such that:
#
#
# 	Every pair of strings in the group are special equivalent, and
# 	The group is the largest size possible (i.e., there is not a string words[i] not in the group such that words[i] is special-equivalent to every string in the group).
#
#
# Return the number of groups of special-equivalent strings from words.
#
# Example:
# Input: words = ["abcd","cdab","cbad","xyzz","zzxy","zzyx"]
# Output: 3
# Explanation: 
# One group is ["abcd", "cdab", "cbad"], since they are all pairwise special equivalent, and none of the other strings is all pairwise special equivalent to these.
# The other two groups are ["xyzz", "zzxy"] and ["zzyx"].
# Note that in particular, "zzxy" is not special equivalent to "zzyx".
#
# Constraints:
# 1 <= words.length <= 1000
# 	1 <= words[i].length <= 20
# 	words[i] consist of lowercase English letters.
# 	All the strings are of the same length.
#
# Helpful references (internal KB):
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
# - Check whether a graph is bipartite (graph, queue, bfs)
#   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
#   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
#   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
#   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
#   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
# - Placing Bishops on a Chessboard (array, counting, dp-2d)
#   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
#   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
#   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
#   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
#   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numSpecialEquivGroups(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        # The key idea is to create a unique signature for each group of special-equivalent strings.
        # We can do this by counting the frequency of characters at even and odd indices separately.
        # Since the strings consist of lowercase English letters, we can use a fixed-size array of length 26 for each.

        def get_signature(word):
            even_count = [0] * 26
            odd_count = [0] * 26
            
            for i, char in enumerate(word):
                if i % 2 == 0:
                    even_count[ord(char) - ord('a')] += 1
                else:
                    odd_count[ord(char) - ord('a')] += 1
            
            # Combine the counts into a tuple to create a unique signature
            return tuple(even_count) + tuple(odd_count)

        signatures = set()
        
        for word in words:
            signatures.add(get_signature(word))
        
        return len(signatures)