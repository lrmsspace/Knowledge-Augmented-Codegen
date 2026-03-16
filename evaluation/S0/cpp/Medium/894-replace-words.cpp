// Source: https://leetcode.com/problems/replace-words/   |   Difficulty: Medium
//
// Problem Description:
// In English, we have a concept called root, which can be followed by some other word to form another longer word - let's call this word derivative. For example, when the root "help" is followed by the word "ful", we can form a derivative "helpful".
//
// Given a dictionary consisting of many roots and a sentence consisting of words separated by spaces, replace all the derivatives in the sentence with the root forming it. If a derivative can be replaced by more than one root, replace it with the root that has the shortest length.
//
// Return the sentence after the replacement.
//
// Example:
// Input: dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled by the battery"
// Output: "the cat was rat by the bat"
//
// Constraints:
// 1 <= dictionary.length <= 1000
// 	1 <= dictionary[i].length <= 100
// 	dictionary[i] consists of only lower-case letters.
// 	1 <= sentence.length <= 106
// 	sentence consists of only lower-case letters and spaces.
// 	The number of words in sentence is in the range [1, 1000]
// 	The length of each word in sentence is in the range [1, 1000]
// 	Every two consecutive words in sentence will be separated by exactly one space.
// 	sentence does not have leading or trailing spaces.
//

class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        struct TrieNode {
            unordered_map<char, TrieNode*> children;
            bool isEnd = false;
        };

        TrieNode* root = new TrieNode();

        // Build the Trie
        for (const string& word : dictionary) {
            TrieNode* node = root;
            for (char c : word) {
                if (!node->children.count(c)) {
                    node->children[c] = new TrieNode();
                }
                node = node->children[c];
            }
            node->isEnd = true;
        }

        // Function to find the shortest root for a given word
        auto findRoot = [&](const string& word) -> string {
            TrieNode* node = root;
            string prefix;
            for (char c : word) {
                if (!node->children.count(c)) {
                    break;
                }
                prefix += c;
                node = node->children[c];
                if (node->isEnd) {
                    return prefix;
                }
            }
            return word; // No root found, return the original word
        };

        // Process the sentence
        istringstream iss(sentence);
        string word;
        string result;
        while (iss >> word) {
            if (!result.empty()) {
                result += " ";
            }
            result += findRoot(word);
        }

        return result;          
    }
};
