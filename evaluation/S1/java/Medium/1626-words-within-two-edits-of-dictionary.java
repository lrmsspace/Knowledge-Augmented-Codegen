// Source: https://leetcode.com/problems/words-within-two-edits-of-dictionary/   |   Difficulty: Medium
//
// Problem Description:
// You are given two string arrays, queries and dictionary. All words in each array comprise of lowercase English letters and have the same length.
//
// In one edit you can take a word from queries, and change any letter in it to any other letter. Find all words from queries that, after a maximum of two edits, equal some word from dictionary.
//
// Return a list of all words from queries, that match with some word from dictionary after a maximum of two edits. Return the words in the same order they appear in queries.
//
// Example:
// Input: queries = ["word","note","ants","wood"], dictionary = ["wood","joke","moat"]
// Output: ["word","note","wood"]
// Explanation:
// - Changing the 'r' in "word" to 'o' allows it to equal the dictionary word "wood".
// - Changing the 'n' to 'j' and the 't' to 'k' in "note" changes it to "joke".
// - It would take more than 2 edits for "ants" to equal a dictionary word.
// - "wood" can remain unchanged (0 edits) and match the corresponding dictionary word.
// Thus, we return ["word","note","wood"].
//
// Constraints:
// 1 <= queries.length, dictionary.length <= 100
// 	n == queries[i].length == dictionary[j].length
// 	1 <= n <= 100
// 	All queries[i] and dictionary[j] are composed of lowercase English letters.
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Aho-Corasick Algorithm for Pattern Searching (string, array, aho-corasick, enumeration)
//   • When to use: Use when you need to find all occurrences of a fixed set of patterns (a dictionary) within a larger text efficiently. It is particularly effective for scenarios with many patterns or long texts where patterns might overlap.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses this automaton to search for all pattern occurrences in a text in a single pass. It achieves a time complexity of O(N + M + K) where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: The trie structure correctly represents all prefixes of all patterns in the dictionary.; Each node's failure link points to the longest proper suffix of the string ending at that node which is also a prefix in the trie.
//   • Tips: Build the trie first from all patterns, marking terminal nodes.; Compute failure links using a BFS-like approach, similar to KMP's LPS array.
//   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to handle output links (dictionary links) will miss patterns found via failure transitions.
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private boolean isWithinTwoEdits(String query, String dictWord) {
        int differences = 0;
        for (int i = 0; i < query.length(); i++) {
            if (query.charAt(i) != dictWord.charAt(i)) {
                differences++;
                if (differences > 2) {
                    return false;
                }
            }
        }
        return differences <= 2;
    }
    public List<String> twoEditWords(String[] queries, String[] dictionary) {
        List<String> result = new ArrayList<>();
        for (String query : queries) {
            for (String dictWord : dictionary) {
                if (isWithinTwoEdits(query, dictWord)) {
                    result.add(query);
                    break; // No need to check other dictionary words
                }
            }
        }
        return result;          
    }
}
