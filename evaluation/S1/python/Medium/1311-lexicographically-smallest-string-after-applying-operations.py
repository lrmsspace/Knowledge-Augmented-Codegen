# Source: https://leetcode.com/problems/lexicographically-smallest-string-after-applying-operations/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s of even length consisting of digits from 0 to 9, and two integers a and b.
#
# You can apply either of the following two operations any number of times and in any order on s:
#
#
# 	Add a to all odd indices of s (0-indexed). Digits post 9 are cycled back to 0. For example, if s = "3456" and a = 5, s becomes "3951".
# 	Rotate s to the right by b positions. For example, if s = "3456" and b = 1, s becomes "6345".
#
#
# Return the lexicographically smallest string you can obtain by applying the above operations any number of times on s.
#
# A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b. For example, "0158" is lexicographically smaller than "0190" because the first position they differ is at the third letter, and '5' comes before '9'.
#
# Example:
# Input: s = "5525", a = 9, b = 2
# Output: "2050"
# Explanation: We can apply the following operations:
# Start:  "5525"
# Rotate: "2555"
# Add:    "2454"
# Add:    "2353"
# Rotate: "5323"
# Add:    "5222"
# Add:    "5121"
# Rotate: "2151"
# Add:    "2050"​​​​​
# There is no way to obtain a string that is lexicographically smaller than "2050".
#
# Constraints:
# 2 <= s.length <= 100
# 	s.length is even.
# 	s consists of digits from 0 to 9 only.
# 	1 <= a <= 9
# 	1 <= b <= s.length - 1
#
# Helpful references (internal KB):
# - Breadth-first search (graph, queue, array, bfs)
#   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
#   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
#   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
#   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
# - Suffix Automaton (string, simulation)
#   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
#   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
#   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
#   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
#   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
# - Extended Euclidean Algorithm (number, gcd, simulation)
#   • When to use: Use this algorithm to find integer coefficients x and y that satisfy Bézout's identity (ax + by = gcd(a,b)). It is also essential for computing modular multiplicative inverses and solving linear Diophantine equations.
#   • Idea: The Extended Euclidean Algorithm computes the greatest common divisor (GCD) of two integers 'a' and 'b', and simultaneously finds integer coefficients 'x' and 'y' such that 'ax + by = gcd(a,b)'. It operates in O(log(min(a,b))) time complexity.
#   • Invariants: x * (initial a) + y * (initial b) = current_a_value; x_1 * (initial a) + y_1 * (initial b) = current_b_value
#   • Tips: Can be implemented using either a recursive or an iterative approach.; The algorithm correctly handles negative integer inputs.
#   • Pitfalls: Incorrectly defining base cases in recursive implementations can lead to errors.; Potential for integer overflow if coefficients x or y become extremely large, though uncommon.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findLexSmallestString(self, s, a, b):
        """
        :type s: str
        :type a: int
        :type b: int
        :rtype: str
        """
        from collections import deque

        def add_operation(s, a):
            s_list = list(s)
            for i in range(1, len(s_list), 2):
                s_list[i] = str((int(s_list[i]) + a) % 10)
            return ''.join(s_list)

        def rotate_operation(s, b):
            return s[-b:] + s[:-b]

        visited = set()
        queue = deque([s])
        smallest = s

        while queue:
            current = queue.popleft()
            if current in visited:
                continue
            visited.add(current)

            if current < smallest:
                smallest = current

            added = add_operation(current, a)
            rotated = rotate_operation(current, b)

            if added not in visited:
                queue.append(added)
            if rotated not in visited:
                queue.append(rotated)

        return smallest