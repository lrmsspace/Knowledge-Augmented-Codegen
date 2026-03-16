# Source: https://leetcode.com/problems/find-the-k-th-character-in-string-game-ii/   |   Difficulty: Hard
#
# Problem Description:
# Alice and Bob are playing a game. Initially, Alice has a string word = "a".
#
# You are given a positive integer k. You are also given an integer array operations, where operations[i] represents the type of the ith operation.
#
# Now Bob will ask Alice to perform all operations in sequence:
#
#
# 	If operations[i] == 0, append a copy of word to itself.
# 	If operations[i] == 1, generate a new string by changing each character in word to its next character in the English alphabet, and append it to the original word. For example, performing the operation on "c" generates "cd" and performing the operation on "zb" generates "zbac".
#
#
# Return the value of the kth character in word after performing all the operations.
#
# Note that the character 'z' can be changed to 'a' in the second type of operation.
#
# Example:
# Input: k = 5, operations = [0,0,0]
#
# Output: "a"
#
# Explanation:
#
# Initially, word == "a". Alice performs the three operations as follows:
#
#
# 	Appends "a" to "a", word becomes "aa".
# 	Appends "aa" to "aa", word becomes "aaaa".
# 	Appends "aaaa" to "aaaa", word becomes "aaaaaaaa".
#
# Constraints:
# 1 <= k <= 1014
# 	1 <= operations.length <= 100
# 	operations[i] is either 0 or 1.
# 	The input is generated such that word has at least k characters after all operations.
#
# Helpful references (internal KB):
# - Operations on polynomials and series (array, recursion)
#   • When to use: When you need to model and solve combinatorial counting problems using algebraic methods, especially when dealing with recurrence relations or products of independent choices. It's also useful for analyzing properties of sequences.
#   • Idea: This involves performing algebraic operations like addition, multiplication, and composition on polynomials or formal power series, represented by coefficients. These operations model combinatorial structures and solve recurrence relations, typically with complexities from O(N) to O(N log N).
#   • Invariants: The array `coefficients[i]` stores the coefficient of `x^i` for the current polynomial.; For any intermediate product `C(x) = A(x) * B(x)`, the coefficient `C[k]` correctly accumulates `A[i] * B[j]` for all `i+j=k`.
#   • Tips: Represent polynomials as arrays of coefficients; Understand the combinatorial meaning of operations (e.g., product for independent choices)
#   • Pitfalls: Confusing ordinary and exponential generating functions; Incorrectly applying convolution for non-independent events
# - Z-function and its calculation (string, array, counting)
#   • When to use: Use when you need to find all occurrences of a pattern within a text, or to identify repeated prefixes within a string efficiently.
#   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the string and its suffix starting at index i. It runs in linear time, O(N), where N is the length of the string.
#   • Invariants: For all j < i, z[j] correctly stores the length of the longest common prefix between S and S[j...].; The segment [l, r-1] represents the rightmost segment that is a prefix of S and has been fully processed.
#   • Tips: Initialize z[0] to 0 (or N, depending on definition) and handle it as a base case.; Utilize previously computed Z-values to avoid redundant comparisons, especially within the 'rightmost matching segment' [l, r].
#   • Pitfalls: Incorrectly updating or using the 'rightmost matching segment' boundaries (l and r).; Off-by-one errors when calculating indices or lengths, especially with 0-based vs. 1-based indexing.
# - Suffix Automaton (graph, string, simulation)
#   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
#   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
#   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
#   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
#   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def kthCharacter(self, k, operations):
        """
        :type k: int
        :type operations: List[int]
        :rtype: str
        """
        length = 1  # 初始字符串长度
        for op in operations:
            if op == 0:
                length *= 2  # 字符串长度翻倍
            else:
                length *= 2  # 字符串长度翻倍
                # 对于操作1，字符会变成下一个字母，所以我们需要调整k的位置
                if k > length // 2:
                    k -= length // 2  # 调整k的位置到第二部分

        # 最后k所在的位置对应的字符是 'a' + (k-1) % 26
        return chr((k - 1) % 26 + ord('a'))