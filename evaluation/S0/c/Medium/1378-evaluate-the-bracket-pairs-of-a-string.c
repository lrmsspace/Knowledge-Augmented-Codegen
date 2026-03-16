// Source: https://leetcode.com/problems/evaluate-the-bracket-pairs-of-a-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s that contains some bracket pairs, with each pair containing a non-empty key.
//
//
// 	For example, in the string "(name)is(age)yearsold", there are two bracket pairs that contain the keys "name" and "age".
//
//
// You know the values of a wide range of keys. This is represented by a 2D string array knowledge where each knowledge[i] = [keyi, valuei] indicates that key keyi has a value of valuei.
//
// You are tasked to evaluate all of the bracket pairs. When you evaluate a bracket pair that contains some key keyi, you will:
//
//
// 	Replace keyi and the bracket pair with the key's corresponding valuei.
// 	If you do not know the value of the key, you will replace keyi and the bracket pair with a question mark "?" (without the quotation marks).
//
//
// Each key will appear at most once in your knowledge. There will not be any nested brackets in s.
//
// Return the resulting string after evaluating all of the bracket pairs.
//
// Example:
// Input: s = "(name)is(age)yearsold", knowledge = [["name","bob"],["age","two"]]
// Output: "bobistwoyearsold"
// Explanation:
// The key "name" has a value of "bob", so replace "(name)" with "bob".
// The key "age" has a value of "two", so replace "(age)" with "two".
//
// Constraints:
// 1 <= s.length <= 105
// 	0 <= knowledge.length <= 105
// 	knowledge[i].length == 2
// 	1 <= keyi.length, valuei.length <= 10
// 	s consists of lowercase English letters and round brackets '(' and ')'.
// 	Every open bracket '(' in s will have a corresponding close bracket ')'.
// 	The key in each bracket pair of s will be non-empty.
// 	There will not be any nested bracket pairs in s.
// 	keyi and valuei consist of lowercase English letters.
// 	Each keyi in knowledge is unique.
//

char* evaluate(char* s, char*** knowledge, int knowledgeSize, int* knowledgeColSize) {
    // Create a hash map to store the knowledge pairs
    #define HASH_SIZE 100003
    typedef struct Node {
        char* key;
        char* value;
        struct Node* next;
    } Node;

    Node* hashMap[HASH_SIZE] = {0};

    unsigned long hash(char* str) {
        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        return hash % HASH_SIZE;
    }

    void insert(char* key, char* value) {
        unsigned long idx = hash(key);
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->value = value;
        newNode->next = hashMap[idx];
        hashMap[idx] = newNode;
    }

    char* search(char* key) {
        unsigned long idx = hash(key);
        Node* curr = hashMap[idx];
        while (curr) {
            if (strcmp(curr->key, key) == 0)
                return curr->value;
            curr = curr->next;
        }
        return NULL;
    }

    // Populate the hash map with knowledge pairs
    for (int i = 0; i < knowledgeSize; i++) {
        insert(knowledge[i][0], knowledge[i][1]);
    }

    // Evaluate the string s
    int len = strlen(s);
    char* result = (char*)malloc(len * 2 + 1); // Allocate enough space
    int resIdx = 0;

    for (int i = 0; i < len; ) {
        if (s[i] == '(') {
            int j = i + 1;
            while (s[j] != ')') j++;
            char key[21]; // max key length is 10, plus null terminator
            strncpy(key, s + i + 1, j - i - 1);
            key[j - i - 1] = '\0';
            char* value = search(key);
            if (value) {
                int vlen = strlen(value);
                strcpy(result + resIdx, value);
                resIdx += vlen;
            } else {
                result[resIdx++] = '?';
            }
            i = j + 1;
        } else {
            result[resIdx++] = s[i++];
        }
    }
    result[resIdx] = '\0';
    // Free the hash map
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* curr = hashMap[i];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    return result;
    
}
