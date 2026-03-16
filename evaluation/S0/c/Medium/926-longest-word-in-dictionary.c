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

char* longestWord(char** words, int wordsSize) {
    // Trie Node Definition
    typedef struct TrieNode {
        struct TrieNode* children[26];
        int isEndOfWord;
    } TrieNode;

    // Create a new Trie Node
    TrieNode* createNode() {
        TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
        node->isEndOfWord = 0;
        for (int i = 0; i < 26; i++) {
            node->children[i] = NULL;
        }
        return node;
    }

    // Insert a word into the Trie
    void insert(TrieNode* root, const char* word) {
        TrieNode* current = root;
        while (*word) {
            int index = *word - 'a';
            if (!current->children[index]) {
                current->children[index] = createNode();
            }
            current = current->children[index];
            word++;
        }
        current->isEndOfWord = 1;
    }

    // Check if a word can be built one character at a time
    int canBuildWord(TrieNode* root, const char* word) {
        TrieNode* current = root;
        while (*word) {
            int index = *word - 'a';
            if (!current->children[index] || !current->children[index]->isEndOfWord) {
                return 0;
            }
            current = current->children[index];
            word++;
        }
        return 1;
    }

    // Initialize Trie and insert all words
    TrieNode* root = createNode();
    for (int i = 0; i < wordsSize; i++) {
        insert(root, words[i]);
    }

    // Find the longest word that can be built
    char* longest = "";
    for (int i = 0; i < wordsSize; i++) {
        if (canBuildWord(root, words[i])) {
            if (strlen(words[i]) > strlen(longest) || 
               (strlen(words[i]) == strlen(longest) && strcmp(words[i], longest) < 0)) {
                longest = words[i];
            }
        }
    }

    // Free Trie memory (not shown here for brevity)

    return longest;     
}
