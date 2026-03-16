# Source: https://leetcode.com/problems/vowel-spellchecker/   |   Difficulty: Medium
#
# Problem Description:
# Given a wordlist, we want to implement a spellchecker that converts a query word into a correct word.
#
# For a given query word, the spell checker handles two categories of spelling mistakes:
#
#
# 	Capitalization: If the query matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the case in the wordlist.
#
# Example:
# wordlist = ["yellow"], query = "YellOw": correct = "yellow"
#
# Constraints:
# 1 <= wordlist.length, queries.length <= 5000
# 	1 <= wordlist[i].length, queries[i].length <= 7
# 	wordlist[i] and queries[i] consist only of only English letters.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def spellchecker(self, wordlist, queries):
        """
        :type wordlist: List[str]
        :type queries: List[str]
        :rtype: List[str]
        """
        def devowel(word):
            return ''.join('*' if c in 'aeiouAEIOU' else c for c in word)
        
        exact_match = set(wordlist)
        case_insensitive = {}
        vowel_error = {}
        
        for word in wordlist:
            lower_word = word.lower()
            if lower_word not in case_insensitive:
                case_insensitive[lower_word] = word
            devoweled_word = devowel(lower_word)
            if devoweled_word not in vowel_error:
                vowel_error[devoweled_word] = word
        
        result = []
        for query in queries:
            if query in exact_match:
                result.append(query)
            elif query.lower() in case_insensitive:
                result.append(case_insensitive[query.lower()])
            elif devowel(query.lower()) in vowel_error:
                result.append(vowel_error[devowel(query.lower())])
            else:
                result.append("")
        
        return result