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

class Solution {
public:
    vector<int> longestCommonPrefix(vector<string>& words, int k) {
        int n = words.size();
        vector<int> result(n, 0);
        
        // Build a trie to count prefixes
        struct TrieNode {
            unordered_map<char, TrieNode*> children;
            int count;
            TrieNode() : count(0) {}
        };
        
        TrieNode* root = new TrieNode();
        
        // Insert all words into the trie
        for (const string& word : words) {
            TrieNode* node = root;
            for (char c : word) {
                if (!node->children.count(c)) {
                    node->children[c] = new TrieNode();
                }
                node = node->children[c];
                node->count++;
            }
        }
        
        // For each word, find the longest prefix with at least k occurrences
        for (int i = 0; i < n; i++) {
            TrieNode* node = root;
            int prefixLength = 0;
            for (char c : words[i]) {
                if (node->children.count(c) && node->children[c]->count >= k) {
                    prefixLength++;
                    node = node->children[c];
                } else {
                    break;
                }
            }
            result[i] = prefixLength;
        }
        
        // Clean up trie memory
        function<void(TrieNode*)> deleteTrie = [&](TrieNode* node) {
            for (auto& pair : node->children) {
                deleteTrie(pair.second);
            }
            delete node;
        };
        deleteTrie(root);
        
        return result;          
    }
};
