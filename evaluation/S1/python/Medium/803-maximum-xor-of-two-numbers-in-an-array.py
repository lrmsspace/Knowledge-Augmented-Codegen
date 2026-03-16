# Source: https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums, return the maximum result of nums[i] XOR nums[j], where 0 <= i <= j < n.
#
# Example:
# Input: nums = [3,10,5,25,2,8]
# Output: 28
# Explanation: The maximum result is 5 XOR 25 = 28.
#
# Constraints:
# 1 <= nums.length <= 2 * 105
# 	0 <= nums[i] <= 231 - 1
#
# Helpful references (internal KB):
# - Tries (trie, array, trie-match)
#   • When to use: Use when managing string keys in a symbol table and needing efficient prefix, wildcard, or longest prefix matching operations, offering flexibility beyond binary search trees and speed comparable to hashing.
#   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set or associative array where keys are typically strings. It allows for efficient retrieval of keys based on their prefixes, achieving O(L) time complexity for operations, where L is the key length.
#   • Invariants: Every path from the root to a node represents a unique prefix.; A node exists only if it is part of at least one stored key.
#   • Tips: Choose an appropriate branching factor (R) based on the alphabet size.; Represent children using arrays for fixed alphabets or hash maps for sparse ones.
#   • Pitfalls: High memory consumption for large alphabets or sparse data.; Deletion of keys can be complex, requiring careful handling of empty branches.
# - Linear Diophantine Equation (number, interval, enumeration)
#   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
#   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
#   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
#   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
#   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
# - Generating all K-combinations (bitset, enumeration)
#   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
#   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
#   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
#   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
#   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findMaximumXOR(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        class TrieNode:
            def __init__(self):
                self.children = {}
        
        class Trie:
            def __init__(self):
                self.root = TrieNode()
            
            def insert(self, num):
                node = self.root
                for i in range(31, -1, -1):
                    bit = (num >> i) & 1
                    if bit not in node.children:
                        node.children[bit] = TrieNode()
                    node = node.children[bit]
            
            def find_max_xor(self, num):
                node = self.root
                max_xor = 0
                for i in range(31, -1, -1):
                    bit = (num >> i) & 1
                    toggled_bit = 1 - bit
                    if toggled_bit in node.children:
                        max_xor |= (1 << i)
                        node = node.children[toggled_bit]
                    else:
                        node = node.children.get(bit, node)
                return max_xor
        
        trie = Trie()
        for num in nums:
            trie.insert(num)
        
        max_result = 0
        for num in nums:
            max_result = max(max_result, trie.find_max_xor(num))
        
        return max_result