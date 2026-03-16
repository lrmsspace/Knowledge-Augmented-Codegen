# Source: https://leetcode.com/problems/count-beautiful-substrings-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s and a positive integer k.
#
# Let vowels and consonants be the number of vowels and consonants in a string.
#
# A string is beautiful if:
#
#
# 	vowels == consonants.
# 	(vowels * consonants) % k == 0, in other terms the multiplication of vowels and consonants is divisible by k.
#
#
# Return the number of non-empty beautiful substrings in the given string s.
#
# A substring is a contiguous sequence of characters in a string.
#
# Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
#
# Consonant letters in English are every letter except vowels.
#
# Example:
# Input: s = "baeyh", k = 2
# Output: 2
# Explanation: There are 2 beautiful substrings in the given string.
# - Substring "baeyh", vowels = 2 (["a",e"]), consonants = 2 (["y","h"]).
# You can see that string "aeyh" is beautiful as vowels == consonants and vowels * consonants % k == 0.
# - Substring "baeyh", vowels = 2 (["a",e"]), consonants = 2 (["b","y"]).
# You can see that string "baey" is beautiful as vowels == consonants and vowels * consonants % k == 0.
# It can be shown that there are only 2 beautiful substrings in the given string.
#
# Constraints:
# 1 <= s.length <= 5 * 104
# 	1 <= k <= 1000
# 	s consists of only English lowercase letters.
#
# Helpful references (internal KB):
# - String Hashing (string, array, hashing, enumeration)
#   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
#   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
#   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
#   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
#   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
# - Sqrt Decomposition (array, enumeration, difference-array)
#   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
#   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
#   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
#   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
#   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
# - Suffix Array (array, string, simulation, two-pointers)
#   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
#   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
#   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
#   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
#   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def beautifulSubstrings(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        vowels = set('aeiou')
        count = 0
        n = len(s)

        for i in range(n):
            vowel_count = 0
            consonant_count = 0

            for j in range(i, n):
                if s[j] in vowels:
                    vowel_count += 1
                else:
                    consonant_count += 1

                if vowel_count == consonant_count and (vowel_count * consonant_count) % k == 0:
                    count += 1

        return count