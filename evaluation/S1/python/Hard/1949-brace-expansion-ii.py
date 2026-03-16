# Source: https://leetcode.com/problems/brace-expansion-ii/   |   Difficulty: Hard
#
# Problem Description:
# Under the grammar given below, strings can represent a set of lowercase words. Let R(expr) denote the set of words the expression represents.
#
# The grammar can best be understood through simple examples:
#
#
# 	Single letters represent a singleton set containing that word.
# 	
# 		R("a") = {"a"}
# 		R("w") = {"w"}
# 	
# 	
# 	When we take a comma-delimited list of two or more expressions, we take the union of possibilities.
# 	
# 		R("{a,b,c}") = {"a","b","c"}
# 		R("{{a,b},{b,c}}") = {"a","b","c"} (notice the final set only contains each word at most once)
# 	
# 	
# 	When we concatenate two expressions, we take the set of possible concatenations between two words where the first word comes from the first expression and the second word comes from the second expression.
# 	
# 		R("{a,b}{c,d}") = {"ac","ad","bc","bd"}
# 		R("a{b,c}{d,e}f{g,h}") = {"abdfg", "abdfh", "abefg", "abefh", "acdfg", "acdfh", "acefg", "acefh"}
# 	
# 	
#
#
# Formally, the three rules for our grammar:
#
#
# 	For every lowercase letter x, we have R(x) = {x}.
# 	For expressions e1, e2, ... , ek with k >= 2, we have R({e1, e2, ...}) = R(e1) ∪ R(e2) ∪ ...
# 	For expressions e1 and e2, we have R(e1 + e2) = {a + b for (a, b) in R(e1) × R(e2)}, where + denotes concatenation, and × denotes the cartesian product.
#
#
# Given an expression representing a set of words under the given grammar, return the sorted list of words that the expression represents.
#
# Example:
# Input: expression = "{a,b}{c,{d,e}}"
# Output: ["ac","ad","ae","bc","bd","be"]
#
# Constraints:
# 1 <= expression.length <= 60
# 	expression[i] consists of '{', '}', ','or lowercase English letters.
# 	The given expression represents a set of words based on the grammar given in the description.
#
# Helpful references (internal KB):
# - Suffix Automaton (graph, tree, string, recursion)
#   • When to use: When needing to efficiently represent all substrings of a string and perform various string operations like counting occurrences, finding distinct substrings, or pattern matching. It is particularly useful for problems involving properties of all substrings or suffixes.
#   • Idea: A Suffix Automaton is a minimal deterministic finite automaton that accepts all suffixes of a given string. It efficiently encodes all substrings and their occurrences, typically constructed in O(N) time and space for a string of length N.
#   • Invariants: Each state in the automaton corresponds to a unique endpos set.; All substrings represented by a state are suffixes of the longest string in that state's endpos set.
#   • Tips: Understand the endpos equivalence classes and suffix links.; Construction is typically incremental, character by character.
#   • Pitfalls: Complexity of implementation can be high due to many edge cases.; Incorrectly handling suffix links during construction.
# - Disjoint Set Union (ds, linked-list, union-find, dfs)
#   • When to use: Use when you need to maintain a collection of disjoint sets and perform union operations to merge sets or find the representative of an element's set efficiently. It's suitable for problems involving dynamic connectivity or grouping elements.
#   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. It achieves nearly constant time complexity for these operations with path compression and union by rank/size optimizations.
#   • Invariants: Every element `i` belongs to exactly one set, represented by `find(i)`.; If `parent[i] == i`, then `i` is the representative (root) of its set.
#   • Tips: Implement path compression in `find` for optimal performance.; Use union by size or rank to maintain balanced trees.
#   • Pitfalls: Omitting path compression or union by rank/size can degrade performance to O(N).; Failing to correctly update auxiliary data stored at representatives during a union operation.
# - String Sorts (array, string, recursion)
#   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
#   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
#   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
#   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
#   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def braceExpansionII(self, expression):
        """
        :type expression: str
        :rtype: List[str]
        """
        stack = []
        current_set = set()
        current_string = ""
        
        for char in expression:
            if char == '{':
                stack.append((current_set, current_string))
                current_set = set()
                current_string = ""
            elif char == '}':
                if current_string:
                    current_set.add(current_string)
                    current_string = ""
                prev_set, prev_string = stack.pop()
                combined_set = set()
                for s in prev_set:
                    for t in current_set:
                        combined_set.add(s + t)
                combined_set.update(prev_set)
                combined_set.update(current_set)
                current_set = combined_set
                current_string = prev_string
            elif char == ',':
                if current_string:
                    current_set.add(current_string)
                    current_string = ""
            else:
                current_string += char
        
        if current_string:
            current_set.add(current_string)
        
        return sorted(current_set)