// Source: https://leetcode.com/problems/report-spam-message/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of strings message and an array of strings bannedWords.
//
// An array of words is considered spam if there are at least two words in it that exactly match any word in bannedWords.
//
// Return true if the array message is spam, and false otherwise.
//
// Example:
// Input: message = ["hello","world","leetcode"], bannedWords = ["world","hello"]
//
// Output: true
//
// Explanation:
//
// The words "hello" and "world" from the message array both appear in the bannedWords array.
//
// Constraints:
// 1 <= message.length, bannedWords.length <= 105
// 	1 <= message[i].length, bannedWords[i].length <= 15
// 	message[i] and bannedWords[i] consist only of lowercase English letters.
//

bool reportSpam(char** message, int messageSize, char** bannedWords, int bannedWordsSize) {
    // Create a hash set to store banned words
    #define TABLE_SIZE 131071  // A large prime number for better distribution
    typedef struct Node {
        char* word;
        struct Node* next;
    } Node;

    Node* hashTable[TABLE_SIZE] = {0};

    unsigned long hash(char* str) {
        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        return hash % TABLE_SIZE;
    }

    void insert(char* word) {
        unsigned long idx = hash(word);
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->word = word;
        newNode->next = hashTable[idx];
        hashTable[idx] = newNode;
    }

    int contains(char* word) {
        unsigned long idx = hash(word);
        Node* current = hashTable[idx];
        while (current) {
            if (strcmp(current->word, word) == 0)
                return 1;
            current = current->next;
        }
        return 0;
    }

    // Insert banned words into the hash set
    for (int i = 0; i < bannedWordsSize; i++) {
        insert(bannedWords[i]);
    }

    // Check message for spam
    int spamCount = 0;
    for (int i = 0; i < messageSize; i++) {
        if (contains(message[i])) {
            spamCount++;
            if (spamCount >= 2) {
                // Free allocated memory before returning
                for (int j = 0; j < TABLE_SIZE; j++) {
                    Node* current = hashTable[j];
                    while (current) {
                        Node* temp = current;
                        current = current->next;
                        free(temp);
                    }
                }
                return true;
            }
        }
    }

    // Free allocated memory before returning
    for (int j = 0; j < TABLE_SIZE; j++) {
        Node* current = hashTable[j];
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    return false;       
}
