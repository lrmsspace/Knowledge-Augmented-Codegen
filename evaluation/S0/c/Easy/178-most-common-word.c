// Source: https://leetcode.com/problems/most-common-word/   |   Difficulty: Easy
//
// Problem Description:
// Given a string paragraph and a string array of the banned words banned, return the most frequent word that is not banned. It is guaranteed there is at least one word that is not banned, and that the answer is unique.
//
// The words in paragraph are case-insensitive and the answer should be returned in lowercase.
//
// Note that words can not contain punctuation symbols.
//
// Example:
// Input: paragraph = "Bob hit a ball, the hit BALL flew far after it was hit.", banned = ["hit"]
// Output: "ball"
// Explanation: 
// "hit" occurs 3 times, but it is a banned word.
// "ball" occurs twice (and no other word does), so it is the most frequent non-banned word in the paragraph. 
// Note that words in the paragraph are not case sensitive,
// that punctuation is ignored (even if adjacent to words, such as "ball,"), 
// and that "hit" isn't the answer even though it occurs more because it is banned.
//
// Constraints:
// 1 <= paragraph.length <= 1000
// 	paragraph consists of English letters, space ' ', or one of the symbols: "!?',;.".
// 	0 <= banned.length <= 100
// 	1 <= banned[i].length <= 10
// 	banned[i] consists of only lowercase English letters.
//

char* mostCommonWord(char* paragraph, char** banned, int bannedSize) {
    // Create a hash map to store word counts
    #define TABLE_SIZE 2048
    typedef struct Node {
        char* word;
        int count;
        struct Node* next;
    } Node;

    Node* table[TABLE_SIZE] = {0};

    unsigned int hash(const char* str) {
        unsigned int hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        return hash % TABLE_SIZE;
    }

    void insert(const char* word) {
        unsigned int idx = hash(word);
        Node* curr = table[idx];
        while (curr) {
            if (strcmp(curr->word, word) == 0) {
                curr->count++;
                return;
            }
            curr = curr->next;
        }
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->word = strdup(word);
        newNode->count = 1;
        newNode->next = table[idx];
        table[idx] = newNode;
    }

    int isBanned(const char* word) {
        for (int i = 0; i < bannedSize; i++) {
            if (strcmp(banned[i], word) == 0)
                return 1;
        }
        return 0;
    }

    // Process the paragraph
    char* token;
    char* delimiters = " !?',;.";
    char* lowerParagraph = strdup(paragraph);
    for (char* p = lowerParagraph; *p; p++) {
        *p = tolower(*p);
    }

    token = strtok(lowerParagraph, delimiters);
    while (token) {
        if (!isBanned(token)) {
            insert(token);
        }
        token = strtok(NULL, delimiters);
    }
    free(lowerParagraph);

    // Find the most common word
    char* result = NULL;
    int maxCount = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* curr = table[i];
        while (curr) {
            if (curr->count > maxCount) {
                maxCount = curr->count;
                result = curr->word;
            }
            curr = curr->next;
        }
    }

    // Free memory
    for (int i  = 0; i < TABLE_SIZE; i++) {
        Node* curr = table[i];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp->word);
            free(temp);
        }
    }
    return result;
}
