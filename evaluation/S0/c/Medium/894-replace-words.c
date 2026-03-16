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

char* replaceWords(char** dictionary, int dictionarySize, char* sentence) {
    // Trie Node Definition
    typedef struct TrieNode {
        struct TrieNode* children[26];
        int isEndOfWord;
    } TrieNode;

    // Create a new Trie Node
    TrieNode* createNode() {
        TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
        for (int i = 0; i < 26; i++) {
            node->children[i] = NULL;
        }
        node->isEndOfWord = 0;
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

    // Search for the shortest root in the Trie
    char* searchRoot(TrieNode* root, const char* word) {
        TrieNode* current = root;
        static char buffer[100]; // Assuming max root length is less than 100
        int length = 0;

        while (*word) {
            int index = *word - 'a';
            if (!current->children[index]) {
                break;
            }
            buffer[length++] = *word;
            current = current->children[index];
            if (current->isEndOfWord) {
                buffer[length] = '\0';
                return buffer;
            }
            word++;
        }
        return NULL;
    }

    // Build the Trie from the dictionary
    TrieNode* trieRoot = createNode();
    for (int i = 0; i < dictionarySize; i++) {
        insert(trieRoot, dictionary[i]);
    }

    // Process the sentence
    char* result = (char*)malloc(2000000 * sizeof(char)); // Allocate enough space for result
    result[0] = '\0';
    char* word = strtok(sentence, " ");
    while (word) {
        char* root = searchRoot(trieRoot, word);
        if (root) {
            strcat(result, root);
        } else {
            strcat(result, word);
        }
        word = strtok(NULL, " ");
        if (word) {
            strcat(result, " ");
        }

    }
    return result;
}
