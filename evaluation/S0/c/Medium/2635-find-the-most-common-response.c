// Source: https://leetcode.com/problems/find-the-most-common-response/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D string array responses where each responses[i] is an array of strings representing survey responses from the ith day.
//
// Return the most common response across all days after removing duplicate responses within each responses[i]. If there is a tie, return the lexicographically smallest response.
//
// Example:
// Input: responses = [["good","ok","good","ok"],["ok","bad","good","ok","ok"],["good"],["bad"]]
//
// Output: "good"
//
// Explanation:
//
//
// 	After removing duplicates within each list, responses = [["good", "ok"], ["ok", "bad", "good"], ["good"], ["bad"]].
// 	"good" appears 3 times, "ok" appears 2 times, and "bad" appears 2 times.
// 	Return "good" because it has the highest frequency.
//
// Constraints:
// 1 <= responses.length <= 1000
// 	1 <= responses[i].length <= 1000
// 	1 <= responses[i][j].length <= 10
// 	responses[i][j] consists of only lowercase English letters
//

char* findCommonResponse(char*** responses, int responsesSize, int* responsesColSize) {
    #define MAX_RESPONSE_LENGTH 11
    #define HASH_MAP_SIZE 2003

    typedef struct HashNode {
        char response[MAX_RESPONSE_LENGTH];
        int count;
        struct HashNode* next;
    } HashNode;

    HashNode* hashMap[HASH_MAP_SIZE] = {0};

    unsigned int hash(const char* str) {
        unsigned int h = 0;
        while (*str) {
            h = (h * 31) + (*str++);
        }
        return h % HASH_MAP_SIZE;
    }

    for (int i = 0; i < responsesSize; i++) {
        int colSize = responsesColSize[i];
        // Use a temporary hash set to avoid duplicates in the same day
        HashNode* tempSet[HASH_MAP_SIZE] = {0};

        for (int j = 0; j < colSize; j++) {
            const char* response = responses[i][j];
            unsigned int h = hash(response);

            // Check if already in tempSet
            HashNode* node = tempSet[h];
            int found = 0;
            while (node) {
                if (strcmp(node->response, response) == 0) {
                    found = 1;
                    break;
                }
                node = node->next;
            }
            if (found) continue;

            // Add to tempSet
            HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
            strcpy(newNode->response, response);
            newNode->count = 1;
            newNode->next = tempSet[h];
            tempSet[h] = newNode;

            // Now add to main hashMap
            h = hash(response);
            node = hashMap[h];
            found = 0;
            while (node) {
                if (strcmp(node->response, response) == 0) {
                    node->count++;
                    found = 1;
                    break;
                }
                node = node->next;
            }
            if (!found) {
                HashNode* mainNode = (HashNode*)malloc(sizeof(HashNode));
                strcpy(mainNode->response, response);
                mainNode->count = 1;
                mainNode->next = hashMap[h];
                hashMap[h] = mainNode;
            }
        }

        // Free tempSet
        for (int k = 0; k < HASH_MAP_SIZE; k++) {
            HashNode* node = tempSet[k];
            while (node) {
                HashNode* temp = node;
                node = node->next;
                free(temp);
            }
        }
    }
    // Find the most common response
    char* mostCommon = NULL;
    int maxCount = 0;
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        HashNode* node = hashMap[i];
        while (node) {
            if (node->count > maxCount || (node->count == maxCount && (mostCommon == NULL || strcmp(node->response, mostCommon) < 0))) {
                maxCount = node->count;
                mostCommon = node->response;
            }
            node = node->next;
        }
    }
    // Free hashMap
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        HashNode* node = hashMap[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    return mostCommon;
}
