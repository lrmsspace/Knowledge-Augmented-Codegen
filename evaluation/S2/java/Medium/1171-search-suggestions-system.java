// Source: https://leetcode.com/problems/search-suggestions-system/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings products and a string searchWord.
//
// Design a system that suggests at most three product names from products after each character of searchWord is typed. Suggested products should have common prefix with searchWord. If there are more than three products with a common prefix return the three lexicographically minimums products.
//
// Return a list of lists of the suggested products after each character of searchWord is typed.
//
// Example:
// Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
// Output: [["mobile","moneypot","monitor"],["mobile","moneypot","monitor"],["mouse","mousepad"],["mouse","mousepad"],["mouse","mousepad"]]
// Explanation: products sorted lexicographically = ["mobile","moneypot","monitor","mouse","mousepad"].
// After typing m and mo all products match and we show user ["mobile","moneypot","monitor"].
// After typing mou, mous and mouse the system suggests ["mouse","mousepad"].
//
// Constraints:
// 1 <= products.length <= 1000
// 	1 <= products[i].length <= 3000
// 	1 <= sum(products[i].length) <= 2 * 104
// 	All the strings of products are unique.
// 	products[i] consists of lowercase English letters.
// 	1 <= searchWord.length <= 1000
// 	searchWord consists of lowercase English letters.
//
// Helpful references (internal KB):
// - Aho-Corasick algorithm (trie, array, trie-match)
//   • When to use: Use when you need to find all occurrences of a fixed set of multiple patterns within a larger text efficiently. It's particularly effective when patterns can overlap or share prefixes.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a set of patterns using a trie and failure links, enabling efficient simultaneous search for all patterns in a text. It achieves a time complexity of O(N + M + K).
//   • Invariants: Every path from the root to a node in the trie represents a unique prefix of at least one pattern.; After processing a character, the current automaton state corresponds to the longest suffix of the processed text that is also a prefix of some pattern.
//   • Tips: Construct the trie from all patterns first, then compute failure links.; Compute failure links using a BFS-like traversal from the root.
//   • Pitfalls: Incorrectly computing failure links, especially for nodes at depth 1 or for non-existent transitions.; Failing to implement output links, leading to missed matches for patterns that are suffixes of others.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<List<String>> suggestedProducts(String[] products, String searchWord) {
        List<List<String>> res = new ArrayList<>();
        Arrays.sort(products);
        for (int i = 0; i < searchWord.length(); i++) {
            String prefix = searchWord.substring(0, i + 1);
            List<String> suggestions = new ArrayList<>();
            for (String product : products) {
                if (product.startsWith(prefix)) {
                    suggestions.add(product);
                    if (suggestions.size() == 3) {
                        break;
                    }
                }
            }
            res.add(suggestions);
        }
        return res;         
    }
}
