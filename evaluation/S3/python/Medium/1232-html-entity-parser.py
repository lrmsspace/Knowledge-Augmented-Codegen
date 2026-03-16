# Source: https://leetcode.com/problems/html-entity-parser/   |   Difficulty: Medium
#
# Problem Description:
# HTML entity parser is the parser that takes HTML code as input and replace all the entities of the special characters by the characters itself.
#
# The special characters and their entities for HTML are:
#
#
# 	Quotation Mark: the entity is &quot; and symbol character is ".
# 	Single Quote Mark: the entity is &apos; and symbol character is '.
# 	Ampersand: the entity is &amp; and symbol character is &.
# 	Greater Than Sign: the entity is &gt; and symbol character is >.
# 	Less Than Sign: the entity is &lt; and symbol character is <.
# 	Slash: the entity is &frasl; and symbol character is /.
#
#
# Given the input text string to the HTML parser, you have to implement the entity parser.
#
# Return the text after replacing the entities by the special characters.
#
# Example:
# Input: text = "&amp; is an HTML entity but &ambassador; is not."
# Output: "& is an HTML entity but &ambassador; is not."
# Explanation: The parser will replace the &amp; entity by &
#
# Constraints:
# 1 <= text.length <= 105
# 	The string may contain any possible characters out of all the 256 ASCII characters.
#
# Helpful references (internal KB):
# - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
#   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
#   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
#   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
#   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
#   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
# - Prüfer code (tree, array, simulation, two-pointers)
#   • When to use: Use when needing to uniquely encode or decode a labeled tree into a sequence of numbers, or to count the number of spanning trees for a complete graph. It's also useful for problems involving tree properties like degree sequences.
#   • Idea: Prüfer code is a unique sequence representing a labeled tree, allowing conversion between a tree and a sequence of numbers. Its generation and decoding typically involve an iterative process of finding and removing leaves, achieving O(N log N) or O(N) complexity with optimized leaf finding.
#   • Invariants: The Prüfer sequence always has N-2 elements for an N-vertex tree.; Each vertex's degree is correctly maintained throughout the process.
#   • Tips: Maintain a degree array to efficiently find leaves.; Use a min-priority queue or a two-pointer approach for finding the smallest leaf.
#   • Pitfalls: Off-by-one errors in sequence length or vertex indexing.; Incorrectly handling the last two vertices during decoding.
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
    def entityParser(self, text):
        """
        :type text: str
        :rtype: str
        """
        entities = {
            "&quot;": '"',
            "&apos;": "'",
            "&amp;": '&',
            "&gt;": '>',
            "&lt;": '<',
            "&frasl;": '/'
        }
        
        for entity, char in entities.items():
            text = text.replace(entity, char)
        
        return text