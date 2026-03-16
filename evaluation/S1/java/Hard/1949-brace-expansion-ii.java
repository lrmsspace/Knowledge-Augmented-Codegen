// Source: https://leetcode.com/problems/brace-expansion-ii/   |   Difficulty: Hard
//
// Problem Description:
// Under the grammar given below, strings can represent a set of lowercase words. Let R(expr) denote the set of words the expression represents.
//
// The grammar can best be understood through simple examples:
//
//
// 	Single letters represent a singleton set containing that word.
// 	
// 		R("a") = {"a"}
// 		R("w") = {"w"}
// 	
// 	
// 	When we take a comma-delimited list of two or more expressions, we take the union of possibilities.
// 	
// 		R("{a,b,c}") = {"a","b","c"}
// 		R("{{a,b},{b,c}}") = {"a","b","c"} (notice the final set only contains each word at most once)
// 	
// 	
// 	When we concatenate two expressions, we take the set of possible concatenations between two words where the first word comes from the first expression and the second word comes from the second expression.
// 	
// 		R("{a,b}{c,d}") = {"ac","ad","bc","bd"}
// 		R("a{b,c}{d,e}f{g,h}") = {"abdfg", "abdfh", "abefg", "abefh", "acdfg", "acdfh", "acefg", "acefh"}
// 	
// 	
//
//
// Formally, the three rules for our grammar:
//
//
// 	For every lowercase letter x, we have R(x) = {x}.
// 	For expressions e1, e2, ... , ek with k >= 2, we have R({e1, e2, ...}) = R(e1) ∪ R(e2) ∪ ...
// 	For expressions e1 and e2, we have R(e1 + e2) = {a + b for (a, b) in R(e1) × R(e2)}, where + denotes concatenation, and × denotes the cartesian product.
//
//
// Given an expression representing a set of words under the given grammar, return the sorted list of words that the expression represents.
//
// Example:
// Input: expression = "{a,b}{c,{d,e}}"
// Output: ["ac","ad","ae","bc","bd","be"]
//
// Constraints:
// 1 <= expression.length <= 60
// 	expression[i] consists of '{', '}', ','or lowercase English letters.
// 	The given expression represents a set of words based on the grammar given in the description.
//
// Helpful references (internal KB):
// - Suffix Automaton (graph, tree, string, recursion)
//   • When to use: When needing to efficiently represent all substrings of a string and perform various string operations like counting occurrences, finding distinct substrings, or pattern matching. It is particularly useful for problems involving properties of all substrings or suffixes.
//   • Idea: A Suffix Automaton is a minimal deterministic finite automaton that accepts all suffixes of a given string. It efficiently encodes all substrings and their occurrences, typically constructed in O(N) time and space for a string of length N.
//   • Invariants: Each state in the automaton corresponds to a unique endpos set.; All substrings represented by a state are suffixes of the longest string in that state's endpos set.
//   • Tips: Understand the endpos equivalence classes and suffix links.; Construction is typically incremental, character by character.
//   • Pitfalls: Complexity of implementation can be high due to many edge cases.; Incorrectly handling suffix links during construction.
// - Disjoint Set Union (ds, linked-list, union-find, dfs)
//   • When to use: Use when you need to maintain a collection of disjoint sets and perform union operations to merge sets or find the representative of an element's set efficiently. It's suitable for problems involving dynamic connectivity or grouping elements.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. It achieves nearly constant time complexity for these operations with path compression and union by rank/size optimizations.
//   • Invariants: Every element `i` belongs to exactly one set, represented by `find(i)`.; If `parent[i] == i`, then `i` is the representative (root) of its set.
//   • Tips: Implement path compression in `find` for optimal performance.; Use union by size or rank to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size can degrade performance to O(N).; Failing to correctly update auxiliary data stored at representatives during a union operation.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private Set<String> dfs(String expression, int left, int right) {
        Set<String> result = new HashSet<>();
        Set<String> currentSet = new HashSet<>();
        currentSet.add("");
        int i = left;
        while (i <= right) {
            char c = expression.charAt(i);
            if (c == '{') {
                int braceCount = 1;
                int j = i + 1;
                while (j <= right && braceCount > 0) {
                    if (expression.charAt(j) == '{') braceCount++;
                    else if (expression.charAt(j) == '}') braceCount--;
                    j++;
                }
                Set<String> subSet = dfs(expression, i + 1, j - 2);
                Set<String> newCurrentSet = new HashSet<>();
                for (String prefix : currentSet) {
                    for (String suffix : subSet) {
                        newCurrentSet.add(prefix + suffix);
                    }
                }
                currentSet = newCurrentSet;
                i = j;
            } else if (c == ',') {
                result.addAll(currentSet);
                currentSet.clear();
                currentSet.add("");
                i++;
            } else {
                Set<String> newCurrentSet = new HashSet<>();
                for (String prefix : currentSet) {
                    newCurrentSet.add(prefix + c);
                }
                currentSet = newCurrentSet;
                i++;
            }
        }
        result.addAll(currentSet);
        return result;
    }
    public List<String> braceExpansionII(String expression) {
        return new ArrayList<>(dfs(expression, 0, expression.length() - 1));            
    }
}
