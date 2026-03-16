// Source: https://leetcode.com/problems/remove-invalid-parentheses/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.
//
// Return a list of unique strings that are valid with the minimum number of removals. You may return the answer in any order.
//
// Example:
// Input: s = "()())()"
// Output: ["(())()","()()()"]
//
// Constraints:
// 1 <= s.length <= 25
// 	s consists of lowercase English letters and parentheses '(' and ')'.
// 	There will be at most 20 parentheses in s.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** removeInvalidParentheses(char* s, int* returnSize) {
    // Implementation of remove invalid parentheses using BFS
    
    #define MAX_QUEUE_SIZE 10000
    #define MAX_RESULT_SIZE 1000
    #define MAX_STRING_LENGTH 25

    char** results = (char**)malloc(sizeof(char*) * MAX_RESULT_SIZE);
    *returnSize = 0;

    typedef struct {
        char str[MAX_STRING_LENGTH + 1];
    } Node;

    Node queue[MAX_QUEUE_SIZE];
    int front = 0, rear = 0;
    int found = 0;

    // Enqueue initial string
    strcpy(queue[rear++].str, s);

    int isValid(char* str) {
        int balance = 0;
        for (int i = 0; str[i]; i++) {
            if (str[i] == '(') balance++;
            else if (str[i] == ')') {
                if (balance == 0) return 0;
                balance--;
            }
        }
        return balance == 0;
    }

    while (front < rear) {
        Node current = queue[front++];
        
        if (isValid(current.str)) {
            results[*returnSize] = strdup(current.str);
            (*returnSize)++;
            found = 1;
        }

        if (found) continue;

        for (int i = 0; current.str[i]; i++) {
            if (current.str[i] != '(' && current.str[i] != ')') continue;

            char nextStr[MAX_STRING_LENGTH + 1];
            strncpy(nextStr, current.str, i);
            strcpy(&nextStr[i], &current.str[i + 1]);

            // Check for duplicates before enqueueing
            int duplicate = 0;
            for (int j = front; j < rear; j++) {
                if (strcmp(queue[j].str, nextStr) == 0) {
                    duplicate = 1;
                    break;
                }
            }
            if (!duplicate && rear < MAX_QUEUE_SIZE) {
                strcpy(queue[rear++].str, nextStr);
            }
        }
    }

    return results;
}
