# Source: https://leetcode.com/problems/goat-latin/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string sentence that consist of words separated by spaces. Each word consists of lowercase and uppercase letters only.
#
# We would like to convert the sentence to "Goat Latin" (a made-up language similar to Pig Latin.) The rules of Goat Latin are as follows:
#
#
# 	If a word begins with a vowel ('a', 'e', 'i', 'o', or 'u'), append "ma" to the end of the word.
#
# 	
# 		For example, the word "apple" becomes "applema".
# 	
# 	
# 	If a word begins with a consonant (i.e., not a vowel), remove the first letter and append it to the end, then add "ma".
# 	
# 		For example, the word "goat" becomes "oatgma".
# 	
# 	
# 	Add one letter 'a' to the end of each word per its word index in the sentence, starting with 1.
# 	
# 		For example, the first word gets "a" added to the end, the second word gets "aa" added to the end, and so on.
# 	
# 	
#
#
# Return the final sentence representing the conversion from sentence to Goat Latin.
#
# Example:
# Input: sentence = "I speak Goat Latin"
# Output: "Imaa peaksmaaa oatGmaaaa atinLmaaaaa"
#
# Constraints:
# 1 <= sentence.length <= 150
# 	sentence consists of English letters and spaces.
# 	sentence has no leading or trailing spaces.
# 	All the words in sentence are separated by a single space.
#
# Helpful references (internal KB):
# - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
#   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
#   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
#   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
#   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
#   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
# - Aho-Corasick algorithm (trie, graph, bfs, trie-match)
#   • When to use: Use this algorithm to efficiently find all occurrences of a fixed set of patterns within a larger text. It is ideal for scenarios requiring simultaneous searching for multiple dictionary words.
#   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a set of patterns, allowing linear time searching for all pattern occurrences in a text. It extends a trie with suffix links and failure transitions for efficient traversal, achieving O(N + M + K) complexity where N is text length, M is total pattern length, and K is total matches.
#   • Invariants: All nodes at depth 'd' have their suffix links correctly computed before processing nodes at depth 'd+1'.; For any node 'u', its suffix link points to the longest proper suffix of the string represented by 'u' that is also a prefix of some pattern.
#   • Tips: Build the trie from all patterns first, marking nodes that represent the end of a pattern.; Compute suffix links using a breadth-first search (BFS) starting from the root.
#   • Pitfalls: Incorrectly computing suffix links can lead to wrong matches or infinite loops.; High memory usage can occur for large alphabets or a vast number of patterns.
# - Calculating the determinant using Kraut method in O(N^3) (matrix, enumeration)
#   • When to use: Use this method to compute the determinant of a square matrix efficiently by decomposing it into lower and upper triangular matrices. It is suitable for problems requiring O(N^3) complexity for matrix operations.
#   • Idea: The Kraut method computes the determinant of a square matrix by first decomposing it into a lower triangular matrix (L) and an upper triangular matrix (U), such that A = LU. The determinant is then the product of the diagonal elements of L and U, achieving O(N^3) time complexity.
#   • Invariants: After processing column k, the first k columns of L and first k rows of U are correctly computed.; For any i <= k and j <= k, the partial sum for A[i][j] from L and U elements up to index min(i,j) is maintained.
#   • Tips: Ensure the input matrix is square for determinant calculation.; The determinant of a triangular matrix is the product of its diagonal elements.
#   • Pitfalls: Division by zero can occur if a pivot element is zero, requiring pivoting strategies.; Floating-point precision issues can accumulate, especially for large matrices.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def toGoatLatin(self, sentence):
        """
        :type sentence: str
        :rtype: str
        """
        vowels = set('aeiouAEIOU')
        words = sentence.split()
        goat_latin_words = []

        for i, word in enumerate(words):
            if word[0] in vowels:
                goat_word = word + 'ma'
            else:
                goat_word = word[1:] + word[0] + 'ma'
            goat_word += 'a' * (i + 1)
            goat_latin_words.append(goat_word)

        return ' '.join(goat_latin_words)