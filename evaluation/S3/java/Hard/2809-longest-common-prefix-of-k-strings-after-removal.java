// Source: https://leetcode.com/problems/longest-common-prefix-of-k-strings-after-removal/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of strings words and an integer k.
//
// For each index i in the range [0, words.length - 1], find the length of the longest common prefix among any k strings (selected at distinct indices) from the remaining array after removing the ith element.
//
// Return an array answer, where answer[i] is the answer for ith element. If removing the ith element leaves the array with fewer than k strings, answer[i] is 0.
//
// Example:
// Input: words = ["jump","run","run","jump","run"], k = 2
//
// Output: [3,4,4,3,4]
//
// Explanation:
//
//
// 	Removing index 0 ("jump"):
//
// 	
// 		words becomes: ["run", "run", "jump", "run"]. "run" occurs 3 times. Choosing any two gives the longest common prefix "run" (length 3).
// 	
// 	
// 	Removing index 1 ("run"):
// 	
// 		words becomes: ["jump", "run", "jump", "run"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).
// 	
// 	
// 	Removing index 2 ("run"):
// 	
// 		words becomes: ["jump", "run", "jump", "run"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).
// 	
// 	
// 	Removing index 3 ("jump"):
// 	
// 		words becomes: ["jump", "run", "run", "run"]. "run" occurs 3 times. Choosing any two gives the longest common prefix "run" (length 3).
// 	
// 	
// 	Removing index 4 ("run"):
// 	
// 		words becomes: ["jump", "run", "run", "jump"]. "jump" occurs twice. Choosing these two gives the longest common prefix "jump" (length 4).
//
// Constraints:
// 1 <= k <= words.length <= 105
// 	1 <= words[i].length <= 104
// 	words[i] consists of lowercase English letters.
// 	The sum of words[i].length is smaller than or equal 105.
//
// Helpful references (internal KB):
// - Aho-Corasick Algorithm for Pattern Searching (string, array, aho-corasick, enumeration)
//   • When to use: Use when you need to find all occurrences of a fixed set of patterns (a dictionary) within a larger text efficiently. It is particularly effective for scenarios with many patterns or long texts where patterns might overlap.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses this automaton to search for all pattern occurrences in a text in a single pass. It achieves a time complexity of O(N + M + K) where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: The trie structure correctly represents all prefixes of all patterns in the dictionary.; Each node's failure link points to the longest proper suffix of the string ending at that node which is also a prefix in the trie.
//   • Tips: Build the trie first from all patterns, marking terminal nodes.; Compute failure links using a BFS-like approach, similar to KMP's LPS array.
//   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to handle output links (dictionary links) will miss patterns found via failure transitions.
// - Suffix Automaton (string, enumeration)
//   • When to use: When you need to efficiently represent all substrings of a given string and perform various string operations like counting distinct substrings or pattern matching in linear time.
//   • Idea: A Suffix Automaton is a minimal finite automaton that accepts all suffixes of a given string. It implicitly represents all substrings and can be constructed in linear time, O(N) where N is the string length.
//   • Invariants: Every path from the initial state spells a substring of the original string.; Each state represents a set of substrings that share the same end positions in the original string.
//   • Tips: Understand the concept of `endpos` sets and how they define states.; The number of states and transitions in a suffix automaton is linear with respect to string length.
//   • Pitfalls: The construction algorithm can be complex and prone to off-by-one errors or incorrect link updates.; Debugging state transitions and suffix links requires careful attention.
// - Tries (trie, tree, trie-match)
//   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
//   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
//   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
//   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
//   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] longestCommonPrefix(String[] words, int k) {
        int n = words.length;
        int[] answer = new int[n];
        Map<String, Integer> freq = new HashMap<>();

        // Count the frequency of each word
        for (String word : words) {
            freq.put(word, freq.getOrDefault(word, 0) + 1);
        }

        // Calculate the longest common prefix for each word
        for (int i = 0; i < n; i++) {
            String currentWord = words[i];
            int currentFreq = freq.get(currentWord);

            // If the frequency of the current word is less than k, answer is 0
            if (currentFreq < k) {
                answer[i] = 0;
                continue;
            }

            // Calculate the longest common prefix length
            int maxPrefixLength = 0;
            for (Map.Entry<String, Integer> entry : freq.entrySet()) {
                if (entry.getValue() >= k) {
                    maxPrefixLength = Math.max(maxPrefixLength, longestCommonPrefixLength(currentWord, entry.getKey()));
                }
            }
            answer[i] = maxPrefixLength;
        }

        return answer;          
    }
}
