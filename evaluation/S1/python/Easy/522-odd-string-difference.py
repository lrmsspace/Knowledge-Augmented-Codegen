# Source: https://leetcode.com/problems/odd-string-difference/   |   Difficulty: Easy
#
# Problem Description:
# You are given an array of equal-length strings words. Assume that the length of each string is n.
#
# Each string words[i] can be converted into a difference integer array difference[i] of length n - 1 where difference[i][j] = words[i][j+1] - words[i][j] where 0 <= j <= n - 2. Note that the difference between two letters is the difference between their positions in the alphabet i.e. the position of 'a' is 0, 'b' is 1, and 'z' is 25.
#
#
# 	For example, for the string "acb", the difference integer array is [2 - 0, 1 - 2] = [2, -1].
#
#
# All the strings in words have the same difference integer array, except one. You should find that string.
#
# Return the string in words that has different difference integer array.
#
# Example:
# Input: words = ["adc","wzy","abc"]
# Output: "abc"
# Explanation: 
# - The difference integer array of "adc" is [3 - 0, 2 - 3] = [3, -1].
# - The difference integer array of "wzy" is [25 - 22, 24 - 25]= [3, -1].
# - The difference integer array of "abc" is [1 - 0, 2 - 1] = [1, 1]. 
# The odd array out is [1, 1], so we return the corresponding string, "abc".
#
# Constraints:
# 3 <= words.length <= 100
# 	n == words[i].length
# 	2 <= n <= 20
# 	words[i] consists of lowercase English letters.
#
# Helpful references (internal KB):
# - String Hashing (string, array, hashing, enumeration)
#   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
#   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
#   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
#   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
#   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
#   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
#   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
#   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
#   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
#   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def oddString(self, words):
        """
        :type words: List[str]
        :rtype: str
        """
        def get_diff_array(word):
            return tuple(ord(word[i+1]) - ord(word[i]) for i in range(len(word)-1))
        
        diff_map = {}
        
        for word in words:
            diff_array = get_diff_array(word)
            if diff_array in diff_map:
                diff_map[diff_array].append(word)
            else:
                diff_map[diff_array] = [word]
        
        for diff_array, word_list in diff_map.items():
            if len(word_list) == 1:
                return word_list[0]
        
        return ""