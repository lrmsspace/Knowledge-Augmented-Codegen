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

class Solution(object):
    def spellchecker(self, wordlist, queries):
        """
        :type wordlist: List[str]
        :type queries: List[str]
        :rtype: List[str]
        """
        def devowel(word):
            return ''.join('*' if c in 'aeiou' else c for c in word.lower())
        
        exact_words = set(wordlist)
        cap_words = {}
        vowel_words = {}
        
        for word in wordlist:
            lower_word = word.lower()
            if lower_word not in cap_words:
                cap_words[lower_word] = word
            devoweled_word = devowel(word)
            if devoweled_word not in vowel_words:
                vowel_words[devoweled_word] = word
        
        result = []
        for query in queries:
            if query in exact_words:
                result.append(query)
            else:
                lower_query = query.lower()
                if lower_query in cap_words:
                    result.append(cap_words[lower_query])
                else:
                    devoweled_query = devowel(query)
                    if devoweled_query in vowel_words:
                        result.append(vowel_words[devoweled_query])
                    else:
                        result.append("")
        
        return result