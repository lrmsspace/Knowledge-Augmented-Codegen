// Source: https://leetcode.com/problems/longest-word-in-dictionary/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of strings words representing an English Dictionary, return the longest word in words that can be built one character at a time by other words in words.
//
// If there is more than one possible answer, return the longest word with the smallest lexicographical order. If there is no answer, return the empty string.
//
// Note that the word should be built from left to right with each additional character being added to the end of a previous word.
//
// Example:
// Input: words = ["w","wo","wor","worl","world"]
// Output: "world"
// Explanation: The word "world" can be built one character at a time by "w", "wo", "wor", and "worl".
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 30
// 	words[i] consists of lowercase English letters.
//
// Helpful references (internal KB):
// - Tries (trie, tree, trie-match)
//   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
//   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
//   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
//   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
//   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Aho-Corasick algorithm (trie, graph, dfs, trie-match)
//   • When to use: Use when searching for all occurrences of a fixed set of multiple patterns within a larger text efficiently. It is ideal for problems requiring simultaneous matching of a dictionary of strings.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, enabling efficient simultaneous searching for all pattern occurrences within a given text. It operates in O(N + M + K) time, where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: Every node in the trie represents a prefix of at least one pattern.; A suffix link from node 'u' points to the node representing the longest proper suffix of 'u' that is also a prefix of some pattern.
//   • Tips: Build the trie for all patterns first, then compute suffix links.; Use BFS to construct suffix links level by level for efficiency.
//   • Pitfalls: Incorrectly building suffix links, especially for the root's children or when no direct transition exists.; High memory consumption if using arrays for transitions with a very large alphabet.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string longestWord(vector<string>& words) {
        struct TrieNode {
            TrieNode* children[26];
            bool isEnd;
            TrieNode() : isEnd(false) {
                for (int i = 0; i < 26; ++i) children[i] = nullptr;
            }
        };

        TrieNode* root = new TrieNode();

        // Insert words into the trie
        for (const string& word : words) {
            TrieNode* node = root;
            for (char c : word) {
                int idx = c - 'a';
                if (!node->children[idx]) {
                    node->children[idx] = new TrieNode();
                }
                node = node->children[idx];
            }
            node->isEnd = true;
        }

        string longest = "";

        // DFS to find the longest word
        function<void(TrieNode*, string)> dfs = [&](TrieNode* node, string current) {
            if (node->isEnd) {
                if (current.length() > longest.length() || 
                    (current.length() == longest.length() && current < longest)) {
                    longest = current;
                }
                for (int i = 0; i < 26; ++i) {
                    if (node->children[i]) {
                        dfs(node->children[i], current + char('a' + i));
                    }
                }
            }
        };

        for (int i = 0; i < 26; ++i) {
            if (root->children[i]) {
                dfs(root->children[i], string(1, char('a' + i)));
            }
        }

        // Clean up trie memory
        function<void(TrieNode*)> freeTrie = [&](TrieNode* node) {
            for (int i = 0; i < 26; ++i) {
                if (node->children[i]) {
                    freeTrie(node->children[i]);
                }
            }
            delete node;
        };
        freeTrie(root);

        return longest;         
    }
};
