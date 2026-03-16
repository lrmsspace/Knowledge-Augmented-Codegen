// Source: https://leetcode.com/problems/longest-common-suffix-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given two arrays of strings wordsContainer and wordsQuery.
//
// For each wordsQuery[i], you need to find a string from wordsContainer that has the longest common suffix with wordsQuery[i]. If there are two or more strings in wordsContainer that share the longest common suffix, find the string that is the smallest in length. If there are two or more such strings that have the same smallest length, find the one that occurred earlier in wordsContainer.
//
// Return an array of integers ans, where ans[i] is the index of the string in wordsContainer that has the longest common suffix with wordsQuery[i].
//
// Example:
// Input: wordsContainer = ["abcd","bcd","xbcd"], wordsQuery = ["cd","bcd","xyz"]
//
// Output: [1,1,1]
//
// Explanation:
//
// Let's look at each wordsQuery[i] separately:
//
//
// 	For wordsQuery[0] = "cd", strings from wordsContainer that share the longest common suffix "cd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
// 	For wordsQuery[1] = "bcd", strings from wordsContainer that share the longest common suffix "bcd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
// 	For wordsQuery[2] = "xyz", there is no string from wordsContainer that shares a common suffix. Hence the longest common suffix is "", that is shared with strings at index 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
//
// Constraints:
// 1 <= wordsContainer.length, wordsQuery.length <= 104
// 	1 <= wordsContainer[i].length <= 5 * 103
// 	1 <= wordsQuery[i].length <= 5 * 103
// 	wordsContainer[i] consists only of lowercase English letters.
// 	wordsQuery[i] consists only of lowercase English letters.
// 	Sum of wordsContainer[i].length is at most 5 * 105.
// 	Sum of wordsQuery[i].length is at most 5 * 105.
//

class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        struct TrieNode {
            unordered_map<char, TrieNode*> children;
            int index = -1;  // index of the word in wordsContainer
            int length = INT_MAX;  // length of the word
        };
        
        TrieNode* root = new TrieNode();
        
        // Build the trie with reversed words from wordsContainer
        for (int i = 0; i < wordsContainer.size(); i++) {
            string& word = wordsContainer[i];
            TrieNode* node = root;
            for (int j = word.size() - 1; j >= 0; j--) {
                char c = word[j];
                if (!node->children.count(c)) {
                    node->children[c] = new TrieNode();
                }
                node = node->children[c];
                
                // Update index and length if this word is better
                if (word.size() < node->length || 
                    (word.size() == node->length && i < node->index)) {
                    node->index = i;
                    node->length = word.size();
                }
            }
        }
        
        vector<int> result;
        
        // Query the trie with reversed words from wordsQuery
        for (string& query : wordsQuery) {
            TrieNode* node = root;
            int bestIndex = -1;
            int bestLength = INT_MAX;
            
            for (int j = query.size() - 1; j >= 0; j--) {
                char c = query[j];
                if (!node->children.count(c)) {
                    break;
                }
                node = node->children[c];
                
                // Update best index and length if this node is better
                if (node->index != -1) {
                    if (node->length < bestLength || 
                        (node->length == bestLength && node->index < bestIndex)) {
                        bestIndex = node->index;
                        bestLength = node->length;
                    }
                }
            }
            
            result.push_back(bestIndex);
        }
        
        return result;          
    }
};
