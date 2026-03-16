# Source: https://leetcode.com/problems/unique-morse-code-words/   |   Difficulty: Easy
#
# Problem Description:
# International Morse Code defines a standard encoding where each letter is mapped to a series of dots and dashes, as follows:
#
#
# 	'a' maps to ".-",
# 	'b' maps to "-...",
# 	'c' maps to "-.-.", and so on.
#
#
# For convenience, the full table for the 26 letters of the English alphabet is given below:
#
#
# [".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."]
#
# Given an array of strings words where each word can be written as a concatenation of the Morse code of each letter.
#
#
# 	For example, "cab" can be written as "-.-..--...", which is the concatenation of "-.-.", ".-", and "-...". We will call such a concatenation the transformation of a word.
#
#
# Return the number of different transformations among all words we have.
#
# Example:
# Input: words = ["gin","zen","gig","msg"]
# Output: 2
# Explanation: The transformation of each word is:
# "gin" -> "--...-."
# "zen" -> "--...-."
# "gig" -> "--...--."
# "msg" -> "--...--."
# There are 2 different transformations: "--...-." and "--...--.".
#
# Constraints:
# 1 <= words.length <= 100
# 	1 <= words[i].length <= 12
# 	words[i] consists of lowercase English letters.
#
# Helpful references (internal KB):
# - String Hashing (string, array, hashing, enumeration)
#   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
#   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
#   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
#   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
#   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
# - String Hashing (string, number, hashing, prefix-sum)
#   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
#   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
#   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
#   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
#   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
# - String Hashing (string, number, hashing)
#   • When to use: Use when needing to efficiently compare strings or substrings, especially in scenarios involving large texts or numerous comparisons. It's also useful for pattern matching and detecting duplicates in collections of strings.
#   • Idea: String hashing converts a string into a numerical value (hash) to enable fast comparisons and lookups. This technique typically uses polynomial hashing with a base and a modulus, offering O(L) for initial hash computation and O(1) for substring hashes after O(N) precomputation.
#   • Invariants: The hash of a string S of length L is (S[0]*P^(L-1) + S[1]*P^(L-2) + ... + S[L-1]*P^0) % M.; For any substring S[i...j], its hash can be derived from precomputed prefix hashes in O(1) time.
#   • Tips: Use multiple hash functions with different bases and moduli to reduce collision probability.; Choose a large prime modulus (e.g., 10^9 + 7) and a random base for robustness.
#   • Pitfalls: Hash collisions are possible; always verify equality for critical applications or use multiple hashes.; Choosing a small or non-prime modulus significantly increases the risk of collisions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def uniqueMorseRepresentations(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        morse_code = [".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
                      "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
                      "..-","...-",".--","-..-","-.--","--.."]

        transformations = set()

        for word in words:
            transformation = "".join(morse_code[ord(char) - ord('a')] for char in word)
            transformations.add(transformation)

        return len(transformations)