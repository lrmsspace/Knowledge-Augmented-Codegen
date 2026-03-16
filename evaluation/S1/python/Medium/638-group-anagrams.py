# Source: https://leetcode.com/problems/group-anagrams/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of strings strs, group the anagrams together. You can return the answer in any order.
#
# Example:
# Input: strs = ["eat","tea","tan","ate","nat","bat"]
#
# Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
#
# Explanation:
#
#
# 	There is no string in strs that can be rearranged to form "bat".
# 	The strings "nat" and "tan" are anagrams as they can be rearranged to form each other.
# 	The strings "ate", "eat", and "tea" are anagrams as they can be rearranged to form each other.
#
# Constraints:
# 1 <= strs.length <= 104
# 	0 <= strs[i].length <= 100
# 	strs[i] consists of lowercase English letters.
#
# Helpful references (internal KB):
# - String Hashing (string, array, hashing, enumeration)
#   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
#   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
#   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
#   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
#   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
# - String Sorts (array, string, number, radix-sort, counting-sort)
#   • When to use: Use when sorting a large collection of fixed-length strings or integers, especially when the key range (alphabet size) is small. It is efficient for data with uniform key lengths.
#   • Idea: LSD Radix Sort sorts elements by processing digits or characters from the least significant to the most significant, using a stable counting sort for each position. It achieves a time complexity of O(W * (N + R)), where W is the key length, N is the number of items, and R is the radix.
#   • Invariants: After each pass 'd' (from 'w-1' down to '0'), the array 'a' is stably sorted based on characters from position 'd' to 'w-1'.; The 'count' array accurately reflects the frequency of each character at the current digit 'd' before cumulation.
#   • Tips: Utilize counting sort as the stable inner sorting algorithm for each digit pass.; Process characters or digits from right to left (least significant to most significant).
#   • Pitfalls: Inefficient for variable-length strings without proper padding or specialized handling.; Can be slower than comparison sorts for small input sizes or very large radix (R).
# - Ordered Set - Python (ds, hashing)
#   • When to use: When you need a collection of unique items where the order of insertion must be preserved, allowing for efficient membership testing and iteration in that specific order.
#   • Idea: An ordered set stores unique elements while maintaining their original insertion order. It provides O(1) average time complexity for additions, deletions, and membership checks, typically implemented using a hash table combined with a linked list.
#   • Invariants: Every element within the set is unique.; The sequence of elements during iteration strictly follows their initial insertion order.
#   • Tips: In Python 3.7+, standard `dict`s maintain insertion order, effectively serving as ordered sets.; Use `collections.OrderedDict` for older Python versions or explicit semantic clarity.
#   • Pitfalls: Order is based on insertion, not value-based sorting; do not confuse the two.; Modifying an element's hash value while it's in the set can lead to undefined behavior.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def groupAnagrams(self, strs):
        """
        :type strs: List[str]
        :rtype: List[List[str]]
        """
        from collections import defaultdict

        anagram_map = defaultdict(list)

        for s in strs:
            # Sort the string to get the anagram key
            key = ''.join(sorted(s))
            anagram_map[key].append(s)

        return list(anagram_map.values())