# Source: https://leetcode.com/problems/sum-of-k-mirror-numbers/   |   Difficulty: Hard
#
# Problem Description:
# A k-mirror number is a positive integer without leading zeros that reads the same both forward and backward in base-10 as well as in base-k.
#
#
# 	For example, 9 is a 2-mirror number. The representation of 9 in base-10 and base-2 are 9 and 1001 respectively, which read the same both forward and backward.
# 	On the contrary, 4 is not a 2-mirror number. The representation of 4 in base-2 is 100, which does not read the same both forward and backward.
#
#
# Given the base k and the number n, return the sum of the n smallest k-mirror numbers.
#
# Example:
# Input: k = 2, n = 5
# Output: 25
# Explanation:
# The 5 smallest 2-mirror numbers and their representations in base-2 are listed as follows:
#   base-10    base-2
#     1          1
#     3          11
#     5          101
#     7          111
#     9          1001
# Their sum = 1 + 3 + 5 + 7 + 9 = 25.
#
# Constraints:
# 2 <= k <= 9
# 	1 <= n <= 30
#
# Helpful references (internal KB):
# - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
#   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
#   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
#   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
#   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
#   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Balanced Ternary (number, string, enumeration, simulation)
#   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
#   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
#   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
#   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
#   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def kMirror(self, k, n):
        """
        :type k: int
        :type n: int
        :rtype: int
        """
        # Step 1: Generate palindromic numbers in base 10
        def generate_palindromes(limit):
            palindromes = []
            for length in range(1, 6):  # Generate palindromes of length 1 to 5
                # Odd length palindromes
                for half in range(10**((length - 1) // 2), 10**((length + 1) // 2)):
                    s = str(half)
                    palindromes.append(int(s + s[-2::-1]))  # Odd length
                    palindromes.append(int(s + s[::-1]))    # Even length
            return sorted(set(palindromes))[:limit]

        # Step 2: Check if a number is a k-mirror
        def is_k_mirror(num, k):
            if num < k:
                return True
            base_k = ""
            n = num
            while n > 0:
                base_k = str(n % k) + base_k
                n //= k
            return base_k == base_k[::-1]

        # Step 3: Find the sum of the n smallest k-mirror numbers
        palindromic_numbers = generate_palindromes(1000)  # Generate enough palindromic numbers
        k_mirrors = []
        for num in palindromic_numbers:
            if is_k_mirror(num, k):
                k_mirrors.append(num)
                if len(k_mirrors) == n:
                    break

        return sum(k_mirrors)