// Source: https://leetcode.com/problems/count-pairs-with-xor-in-a-range/   |   Difficulty: Hard
//
// Problem Description:
// Given a (0-indexed) integer array nums and two integers low and high, return the number of nice pairs.
//
// A nice pair is a pair (i, j) where 0 <= i < j < nums.length and low <= (nums[i] XOR nums[j]) <= high.
//
// Example:
// Input: nums = [1,4,2,7], low = 2, high = 6
// Output: 6
// Explanation: All nice pairs (i, j) are as follows:
//     - (0, 1): nums[0] XOR nums[1] = 5 
//     - (0, 2): nums[0] XOR nums[2] = 3
//     - (0, 3): nums[0] XOR nums[3] = 6
//     - (1, 2): nums[1] XOR nums[2] = 6
//     - (1, 3): nums[1] XOR nums[3] = 3
//     - (2, 3): nums[2] XOR nums[3] = 5
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i] <= 2 * 104
// 	1 <= low <= high <= 2 * 104
//
// Helpful references (internal KB):
// - Tries (trie, tree, trie-match)
//   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
//   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
//   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
//   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
//   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Aho-Corasick algorithm (trie, array, trie-match)
//   • When to use: Use when you need to find all occurrences of a fixed set of multiple patterns within a larger text efficiently. It's particularly effective when patterns can overlap or share prefixes.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a set of patterns using a trie and failure links, enabling efficient simultaneous search for all patterns in a text. It achieves a time complexity of O(N + M + K).
//   • Invariants: Every path from the root to a node in the trie represents a unique prefix of at least one pattern.; After processing a character, the current automaton state corresponds to the longest suffix of the processed text that is also a prefix of some pattern.
//   • Tips: Construct the trie from all patterns first, then compute failure links.; Compute failure links using a BFS-like traversal from the root.
//   • Pitfalls: Incorrectly computing failure links, especially for nodes at depth 1 or for non-existent transitions.; Failing to implement output links, leading to missed matches for patterns that are suffixes of others.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int countPairs(vector<int>& nums, int low, int high) {
        return countLessEqual(nums, high) - countLessEqual(nums, low - 1);          
    }
private:
    struct TrieNode {
        TrieNode* children[2] = {nullptr};
        int count = 0;
    };
    
    int countLessEqual(const vector<int>& nums, int limit) {
        TrieNode* root = new TrieNode();
        int result = 0;
        for (int num : nums) {
            result += countPairsWithLimit(root, num, limit);
            insert(root, num);
        }
        return result;
    }

    int countPairsWithLimit(TrieNode* root, int num, int limit) {
        TrieNode* node = root;
        int count = 0;
        for (int i = 15; i >= 0 && node; --i) {
            int bitNum = (num >> i) & 1;
            int bitLimit = (limit >> i) & 1;
            if (bitLimit == 1) {
                if (node->children[bitNum]) {
                    count += node->children[bitNum]->count;
                }
                node = node->children[1 - bitNum];
            } else {
                node = node->children[bitNum];
            }
        }
        if (node) {
            count += node->count;
        }
        return count;
    }

    void insert(TrieNode* root, int num) {
        TrieNode* node = root;
        for (int i = 15; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if (!node->children[bit]) {
                node->children[bit] = new TrieNode();
            }
            node = node->children[bit];
            node->count++;
        }
    }
};