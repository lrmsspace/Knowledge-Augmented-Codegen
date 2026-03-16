# Source: https://leetcode.com/problems/utf-8-validation/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array data representing the data, return whether it is a valid UTF-8 encoding (i.e. it translates to a sequence of valid UTF-8 encoded characters).
#
# A character in UTF8 can be from 1 to 4 bytes long, subjected to the following rules:
#
#
# 	For a 1-byte character, the first bit is a 0, followed by its Unicode code.
# 	For an n-bytes character, the first n bits are all one's, the n + 1 bit is 0, followed by n - 1 bytes with the most significant 2 bits being 10.
#
#
# This is how the UTF-8 encoding would work:
#
#
#      Number of Bytes   |        UTF-8 Octet Sequence
#                        |              (binary)
#    --------------------+-----------------------------------------
#             1          |   0xxxxxxx
#             2          |   110xxxxx 10xxxxxx
#             3          |   1110xxxx 10xxxxxx 10xxxxxx
#             4          |   11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
#
#
# x denotes a bit in the binary form of a byte that may be either 0 or 1.
#
# Note: The input is an array of integers. Only the least significant 8 bits of each integer is used to store the data. This means each integer represents only 1 byte of data.
#
# Example:
# Input: data = [197,130,1]
# Output: true
# Explanation: data represents the octet sequence: 11000101 10000010 00000001.
# It is a valid utf-8 encoding for a 2-bytes character followed by a 1-byte character.
#
# Constraints:
# 1 <= data.length <= 2 * 104
# 	0 <= data[i] <= 255
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Data Compression (trie, array, trie-match, greedy, simulation)
#   • When to use: When needing to reduce the size of data by encoding frequently occurring patterns or symbols with shorter representations, especially for lossless compression of text or binary streams.
#   • Idea: Data compression algorithms like Huffman coding and LZW reduce data size by assigning variable-length codes based on frequency or by replacing repeated patterns with shorter references. Huffman coding typically involves O(N log N) for building the tree and O(N) for encoding/decoding, while LZW can be O(N) for both, where N is the input size.
#   • Invariants: The encoding process consistently maps input symbols or sequences to their assigned codes.; The decoding process reconstructs the original data by traversing the encoding structure using the compressed bitstream.
#   • Tips: Use a min-priority queue to efficiently build the Huffman tree from character frequencies.; Represent Huffman codes as bit strings for efficient storage and transmission.
#   • Pitfalls: Incorrectly handling edge cases like empty input or single-character input.; Off-by-one errors when reading/writing bit streams.
# - Fenwick Tree (array, bit-fenwick, difference-array)
#   • When to use: Use when an array requires frequent point updates and efficient retrieval of prefix sums or range sums. It offers logarithmic time complexity for both operations.
#   • Idea: A Fenwick Tree, or Binary Indexed Tree (BIT), is a data structure that efficiently supports point updates and prefix sum queries on an array in O(log N) time.
#   • Invariants: Each `bit[i]` stores the sum of a contiguous range of elements from the original array.; The range length represented by `bit[i]` is determined by `i & -i` (the least significant bit).
#   • Tips: Use 1-based indexing for simpler bitwise operations (`i & -i`).; Initialize with an existing array in O(N) time using a linear construction method.
#   • Pitfalls: Directly finding range minimum/maximum is not efficient or generally supported.; Operations must be associative and preferably invertible for general range queries.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def validUtf8(self, data):
        """
        :type data: List[int]
        :rtype: bool
        """
        n_bytes = 0

        for num in data:
            byte = num & 0xFF

            if n_bytes == 0:
                if (byte >> 5) == 0b110:
                    n_bytes = 1
                elif (byte >> 4) == 0b1110:
                    n_bytes = 2
                elif (byte >> 3) == 0b11110:
                    n_bytes = 3
                elif (byte >> 7) != 0:
                    return False
            else:
                if (byte >> 6) != 0b10:
                    return False
                n_bytes -= 1

        return n_bytes == 0