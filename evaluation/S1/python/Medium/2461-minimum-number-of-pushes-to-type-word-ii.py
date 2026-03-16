# Source: https://leetcode.com/problems/minimum-number-of-pushes-to-type-word-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string word containing lowercase English letters.
#
# Telephone keypads have keys mapped with distinct collections of lowercase English letters, which can be used to form words by pushing them. For example, the key 2 is mapped with ["a","b","c"], we need to push the key one time to type "a", two times to type "b", and three times to type "c" .
#
# It is allowed to remap the keys numbered 2 to 9 to distinct collections of letters. The keys can be remapped to any amount of letters, but each letter must be mapped to exactly one key. You need to find the minimum number of times the keys will be pushed to type the string word.
#
# Return the minimum number of pushes needed to type word after remapping the keys.
#
# An example mapping of letters to keys on a telephone keypad is given below. Note that 1, *, #, and 0 do not map to any letters.
#
# Example:
# Input: word = "abcde"
# Output: 5
# Explanation: The remapped keypad given in the image provides the minimum cost.
# "a" -> one push on key 2
# "b" -> one push on key 3
# "c" -> one push on key 4
# "d" -> one push on key 5
# "e" -> one push on key 6
# Total cost is 1 + 1 + 1 + 1 + 1 = 5.
# It can be shown that no other mapping can provide a lower cost.
#
# Constraints:
# 1 <= word.length <= 105
# 	word consists of lowercase English letters.
#
# Helpful references (internal KB):
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
# - Data Compression (tree, heap, greedy, recursion, counting)
#   • When to use: Use when you need to losslessly compress data by assigning shorter bit sequences to more frequent symbols, aiming for the shortest possible average code length. It is effective for data with non-uniform character distributions.
#   • Idea: Huffman coding is a greedy algorithm that constructs an optimal prefix code for a given set of symbols and their frequencies. It builds a binary tree (Huffman trie) by repeatedly merging the two nodes with the smallest frequencies, resulting in an encoding with O(N + K log K) time complexity, where N is input length and K is alphabet size.
#   • Invariants: The priority queue always contains valid Huffman nodes, each representing a subtree or a leaf character.; Every internal node in the Huffman tree has exactly two children, and its frequency is the sum of its children's frequencies.
#   • Tips: Use a min-priority queue to efficiently retrieve and combine the two lowest-frequency nodes.; Represent the Huffman tree explicitly to generate codes and for decoding.
#   • Pitfalls: The overhead of storing the Huffman tree or frequency table can negate compression benefits for small inputs.; Not truly optimal for all data types; it's a statistical compression method.
# - Maximum flow - Push-relabel method improved (graph, array, greedy, bfs)
#   • When to use: Use this for maximum flow problems on graphs where an optimized push-relabel approach is required. It improves performance by prioritizing vertices with the greatest height for push and relabel operations.
#   • Idea: This algorithm is an optimized variant of the push-relabel maximum flow method, which improves efficiency by always selecting the vertex with the greatest height that has excess flow. This specific vertex selection strategy leads to a better theoretical time complexity, typically O(V^2 * sqrt(E)) or O(V^3) depending on implementation details.
#   • Invariants: For any edge (u, v) in the residual graph, h(u) <= h(v) + 1.; The total excess flow in the network is always non-negative.
#   • Tips: Always select the active vertex with the highest current height.; Maintain a data structure (e.g., buckets or lists) to quickly find highest-height vertices.
#   • Pitfalls: Incorrectly managing the list of highest-height vertices.; Failing to update residual capacities after a push operation.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumPushes(self, word):
        """
        :type word: str
        :rtype: int
        """
        from collections import Counter
        import heapq

        freq = Counter(word)
        max_heap = [-count for count in freq.values()]
        heapq.heapify(max_heap)

        total_pushes = 0
        push_count = 1
        keys_used = 0

        while max_heap:
            count = -heapq.heappop(max_heap)
            total_pushes += count * push_count
            keys_used += 1

            if keys_used == 8:  # Move to next push count after using 8 keys
                keys_used = 0
                push_count += 1

        return total_pushes