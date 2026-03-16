// Source: https://leetcode.com/problems/short-encoding-of-words/   |   Difficulty: Medium
//
// Problem Description:
// A valid encoding of an array of words is any reference string s and array of indices indices such that:
//
//
// 	words.length == indices.length
// 	The reference string s ends with the '#' character.
// 	For each index indices[i], the substring of s starting from indices[i] and up to (but not including) the next '#' character is equal to words[i].
//
//
// Given an array of words, return the length of the shortest reference string s possible of any valid encoding of words.
//
// Example:
// Input: words = ["time", "me", "bell"]
// Output: 10
// Explanation: A valid encoding would be s = "time#bell#" and indices = [0, 2, 5].
// words[0] = "time", the substring of s starting from indices[0] = 0 to the next '#' is underlined in "time#bell#"
// words[1] = "me", the substring of s starting from indices[1] = 2 to the next '#' is underlined in "time#bell#"
// words[2] = "bell", the substring of s starting from indices[2] = 5 to the next '#' is underlined in "time#bell#"
//
// Constraints:
// 1 <= words.length <= 2000
// 	1 <= words[i].length <= 7
// 	words[i] consists of only lowercase letters.
//

int minimumLengthEncoding(char** words, int wordsSize) {
    // Using a trie to store the reversed words
    typedef struct TrieNode {
        struct TrieNode* children[26];
        int isEnd;
    } TrieNode;

    TrieNode* createNode() {
        TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
        for (int i = 0; i < 26; i++) {
            node->children[i] = NULL;
        }
        node->isEnd = 0;
        return node;
    }

    void insert(TrieNode* root, const char* word) {
        TrieNode* curr = root;
        int len = strlen(word);
        for (int i = len - 1; i >= 0; i--) {
            int index = word[i] - 'a';
            if (!curr->children[index]) {
                curr->children[index] = createNode();
            }
            curr = curr->children[index];
        }
        curr->isEnd = 1; // Mark the end of a word
    }

    int calculateLength(TrieNode* root, int depth) {
        int length = 0;
        int isLeaf = 1;
        for (int i = 0; i < 26; i++) {
            if (root->children[i]) {
                isLeaf = 0;
                length += calculateLength(root->children[i], depth + 1);
            }
        }
        if (isLeaf) {
            return depth + 1; // +1 for the '#' character
        }
        return length;
    }

    TrieNode* root = createNode();
    for (int i = 0; i < wordsSize; i++) {
        insert(root, words[i]);
    }

    int result = calculateLength(root, 0);

    // Free the trie memory (not shown here for brevity)

    return result;      
}
