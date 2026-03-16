# Source: https://leetcode.com/problems/minimum-cost-good-caption/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string caption of length n. A good caption is a string where every character appears in groups of at least 3 consecutive occurrences.
#
# For example:
#
#
# 	"aaabbb" and "aaaaccc" are good captions.
# 	"aabbb" and "ccccd" are not good captions.
#
#
# You can perform the following operation any number of times:
#
# Choose an index i (where 0 <= i < n) and change the character at that index to either:
#
#
# 	The character immediately before it in the alphabet (if caption[i] != 'a').
# 	The character immediately after it in the alphabet (if caption[i] != 'z').
#
#
# Your task is to convert the given caption into a good caption using the minimum number of operations, and return it. If there are multiple possible good captions, return the lexicographically smallest one among them. If it is impossible to create a good caption, return an empty string "".
#
# Example:
# Input: caption = "cdcd"
#
# Output: "cccc"
#
# Explanation:
#
# It can be shown that the given caption cannot be transformed into a good caption with fewer than 2 operations. The possible good captions that can be created using exactly 2 operations are:
#
#
# 	"dddd": Change caption[0] and caption[2] to their next character 'd'.
# 	"cccc": Change caption[1] and caption[3] to their previous character 'c'.
#
#
# Since "cccc" is lexicographically smaller than "dddd", return "cccc".
#
# Constraints:
# 1 <= caption.length <= 5 * 104
# 	caption consists only of lowercase English letters.
#
# Helpful references (internal KB):
# - Finding repetitions (string, array, z-function, enumeration)
#   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
#   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
#   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
#   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
#   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
# - Balanced Ternary (number, string, enumeration, simulation)
#   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
#   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
#   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
#   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
#   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
# - Data Compression (trie, array, trie-match, greedy, simulation)
#   • When to use: When needing to reduce the size of data by encoding frequently occurring patterns or symbols with shorter representations, especially for lossless compression of text or binary streams.
#   • Idea: Data compression algorithms like Huffman coding and LZW reduce data size by assigning variable-length codes based on frequency or by replacing repeated patterns with shorter references. Huffman coding typically involves O(N log N) for building the tree and O(N) for encoding/decoding, while LZW can be O(N) for both, where N is the input size.
#   • Invariants: The encoding process consistently maps input symbols or sequences to their assigned codes.; The decoding process reconstructs the original data by traversing the encoding structure using the compressed bitstream.
#   • Tips: Use a min-priority queue to efficiently build the Huffman tree from character frequencies.; Represent Huffman codes as bit strings for efficient storage and transmission.
#   • Pitfalls: Incorrectly handling edge cases like empty input or single-character input.; Off-by-one errors when reading/writing bit streams.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minCostGoodCaption(self, caption):
        """
        :type caption: str
        :rtype: str
        """
        from collections import Counter

        n = len(caption)
        if n < 3:
            return ""  # Impossible to form a good caption

        freq = Counter(caption)
        result = list(caption)

        for char, count in freq.items():
            if count < 3:
                # We need to change this character to make it appear at least 3 times
                indices = [i for i, c in enumerate(caption) if c == char]
                for idx in indices:
                    # Try changing to the previous character
                    if char > 'a':
                        prev_char = chr(ord(char) - 1)
                        result[idx] = prev_char
                    # Try changing to the next character
                    elif char < 'z':
                        next_char = chr(ord(char) + 1)
                        result[idx] = next_char

        return "".join(result)