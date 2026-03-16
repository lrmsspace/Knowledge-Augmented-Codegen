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
// - Tries (trie, tree, trie-match)
//   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
//   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
//   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
//   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
//   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
// - Lowest Common Ancestor (tree, array, dfs)
//   • When to use: Use this algorithm to efficiently find the lowest common ancestor of two nodes in a tree. It is particularly effective for answering multiple LCA queries on a static tree after initial preprocessing.
//   • Idea: This algorithm preprocesses a tree using a DFS to build an Euler tour and record node depths. It transforms Lowest Common Ancestor (LCA) queries into Range Minimum Queries (RMQ) on the Euler tour, enabling O(1) query time after O(N log N) preprocessing.
//   • Invariants: During DFS, `euler` contains the sequence of visited nodes, and `height` stores each node's depth from the root.; The `first` array correctly maps each node to its initial index in the `euler` tour.
//   • Tips: Perform a single DFS to compute node depths and construct the Euler tour along with first occurrences.; Utilize a Sparse Table or Segment Tree for O(1) or O(log N) Range Minimum Query after preprocessing.
//   • Pitfalls: Incorrectly building the Euler tour, especially missing the 'return' visits to parent nodes.; Off-by-one errors when defining the range for the Range Minimum Query on the Euler tour.
// - Manacher's Algorithm - Finding all sub-p (string, array, enumeration)
//   • When to use: Use when you need to find all palindromic substrings within a given string, or determine the longest palindromic substring, in optimal linear time.
//   • Idea: Manacher's Algorithm efficiently finds the length of the longest palindromic substring centered at each position in a given string, handling both odd and even lengths uniformly via preprocessing. It achieves this in optimal O(N) time complexity.
//   • Invariants: p[i] correctly stores the radius of the longest palindrome centered at i in the transformed string.; The right_boundary always marks the rightmost extent of the largest palindrome found so far.
//   • Tips: Preprocess the string with a unique delimiter to unify odd and even length palindromes.; Leverage the mirror property around the current center to initialize palindrome radii.
//   • Pitfalls: Off-by-one errors when converting `p` array values back to original string indices or lengths.; Incorrectly handling the boundaries of the preprocessed string.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    static class TrieNode {
        TrieNode[] children;
        int count;

        TrieNode() {
            children = new TrieNode[26];
            count = 0;
        }
    }
    private void insertWord(TrieNode root, String word) {
        TrieNode node = root;
        for (char ch : word.toCharArray()) {
            int index = ch - 'a';
            if (node.children[index] == null) {
                node.children[index] = new TrieNode();
            }
            node = node.children[index];
            node.count++;
        }
    }
    private int findLCPAfterRemoval(TrieNode root, String word, int k) {
        TrieNode node = root;
        int lcpLength = 0;
        for (char ch : word.toCharArray()) {
            int index = ch - 'a';
            if (node.children[index] == null) {
                break;
            }
            TrieNode nextNode = node.children[index];
            if (nextNode.count >= k + 1) {
                lcpLength++;
                node = nextNode;
            } else {
                break;
            }
        }
        return lcpLength;
    }
    public int[] longestCommonPrefix(String[] words, int k) {
        int n = words.length;
        int[] result = new int[n];
        if (n < k) {
            return result; // All zeros if fewer than k strings
        }

        TrieNode root = new TrieNode();
        for (String word : words) {
            insertWord(root, word);
        }

        for (int i = 0; i < n; i++) {
            result[i] = findLCPAfterRemoval(root, words[i], k);
        }

        return result;          
    }
}
