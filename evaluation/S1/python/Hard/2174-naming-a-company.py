# Source: https://leetcode.com/problems/naming-a-company/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array of strings ideas that represents a list of names to be used in the process of naming a company. The process of naming a company is as follows:
#
#
# 	Choose 2 distinct names from ideas, call them ideaA and ideaB.
# 	Swap the first letters of ideaA and ideaB with each other.
# 	If both of the new names are not found in the original ideas, then the name ideaA ideaB (the concatenation of ideaA and ideaB, separated by a space) is a valid company name.
# 	Otherwise, it is not a valid name.
#
#
# Return the number of distinct valid names for the company.
#
# Example:
# Input: ideas = ["coffee","donuts","time","toffee"]
# Output: 6
# Explanation: The following selections are valid:
# - ("coffee", "donuts"): The company name created is "doffee conuts".
# - ("donuts", "coffee"): The company name created is "conuts doffee".
# - ("donuts", "time"): The company name created is "tonuts dime".
# - ("donuts", "toffee"): The company name created is "tonuts doffee".
# - ("time", "donuts"): The company name created is "dime tonuts".
# - ("toffee", "donuts"): The company name created is "doffee tonuts".
# Therefore, there are a total of 6 distinct company names.
#
# The following are some examples of invalid selections:
# - ("coffee", "time"): The name "toffee" formed after swapping already exists in the original array.
# - ("time", "toffee"): Both names are still the same after swapping and exist in the original array.
# - ("coffee", "toffee"): Both names formed after swapping already exist in the original array.
#
# Constraints:
# 2 <= ideas.length <= 5 * 104
# 	1 <= ideas[i].length <= 10
# 	ideas[i] consists of lowercase English letters.
# 	All the strings in ideas are unique.
#
# Helpful references (internal KB):
# - String Hashing (string, array, hashing, enumeration)
#   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
#   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
#   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
#   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
#   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
# - Suffix Automaton (string, simulation)
#   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
#   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
#   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
#   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
#   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
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
    def distinctNames(self, ideas):
        """
        :type ideas: List[str]
        :rtype: int
        """
        # Group ideas by their first letter
        groups = [set() for _ in range(26)]
        for idea in ideas:
            groups[ord(idea[0]) - ord('a')].add(idea[1:])

        # Calculate the number of valid combinations
        total = 0
        for i in range(26):
            for j in range(i + 1, 26):
                common = len(groups[i] & groups[j])
                total += 2 * (len(groups[i]) - common) * (len(groups[j]) - common)

        return total