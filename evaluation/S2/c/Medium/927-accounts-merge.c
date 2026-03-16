// Source: https://leetcode.com/problems/accounts-merge/   |   Difficulty: Medium
//
// Problem Description:
// Given a list of accounts where each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the account.
//
// Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some common email to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.
//
// After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.
//
// Example:
// Input: accounts = [["John","johnsmith@mail.com","john_newyork@mail.com"],["John","johnsmith@mail.com","john00@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
// Output: [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]
// Explanation:
// The first and second John's are the same person as they have the common email "johnsmith@mail.com".
// The third John and Mary are different people as none of their email addresses are used by other accounts.
// We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
// ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
//
// Constraints:
// 1 <= accounts.length <= 1000
// 	2 <= accounts[i].length <= 10
// 	1 <= accounts[i][j].length <= 30
// 	accounts[i][0] consists of English letters.
// 	accounts[i][j] (for j > 0) is a valid email.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** accountsMerge(char*** accounts, int accountsSize, int* accountsColSize, int* returnSize, int** returnColumnSizes) {
    // Step 1: Use a hash map to group emails by their corresponding names and to find connected components of emails.
    typedef struct EmailNode {
        char* email;
        struct EmailNode* next;
    } EmailNode;

    typedef struct {
        char* name;
        EmailNode* emails;
    } Account;

    Account* accountMap = (Account*)malloc(accountsSize * sizeof(Account));
    int accountCount = 0;

    for (int i = 0; i < accountsSize; i++) {
        char* name = accounts[i][0];
        EmailNode* emailList = NULL;

        for (int j = 1; j < accountsColSize[i]; j++) {
            EmailNode* newNode = (EmailNode*)malloc(sizeof(EmailNode));
            newNode->email = accounts[i][j];
            newNode->next = emailList;
            emailList = newNode;
        }

        accountMap[accountCount].name = name;
        accountMap[accountCount].emails = emailList;
        accountCount++;
    }

    // Step 2: Merge accounts with common emails using a union-find structure or DFS to find connected components.
    // For simplicity, we will use a union-find structure here.

    // Union-Find implementation
    int parent[accountsSize];
    for (int i = 0; i < accountsSize; i++) {
        parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void union(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootY] = rootX;
        }
    }

    // Map from email to account index
    typedef struct EmailMap {
        char* email;
        int index;
        struct EmailMap* next;
    } EmailMap;

    EmailMap* emailMapHead = NULL;

    for (int i = 0; i < accountCount; i++) {
        EmailNode* currentEmail = accountMap[i].emails;
        while (currentEmail != NULL) {
            // Check if the email is already in the map
            EmailMap* currentMap = emailMapHead;
            int foundIndex = -1;
            while (currentMap != NULL) {
                if (strcmp(currentMap->email, currentEmail->email) == 0) {
                    foundIndex = currentMap->index;
                    break;
                }
                currentMap = currentMap->next;
            }
            if (foundIndex != -1) {
                union(i, foundIndex);
            } else {
                // Add the email to the map
                EmailMap* newMapNode = (EmailMap*)malloc(sizeof(EmailMap));
                newMapNode->email = currentEmail->email;
                newMapNode->index = i;
                newMapNode->next = emailMapHead;
                emailMapHead = newMapNode;
            }   
            currentEmail = currentEmail->next;
        }
    }
    
    // Step 3: Collect merged accounts
    int* rootIndices = (int*)malloc(accountsSize * sizeof(int));
    int rootCount = 0;
    for (int i = 0; i < accountsSize; i++) {
        if (parent[i] == i) {
            rootIndices[rootCount++] = i;
        }
    }

    // Return the merged accounts
    *returnSize = rootCount;
    *returnColumnSizes = (int*)malloc(rootCount * sizeof(int));
    char*** result = (char***)malloc(rootCount * sizeof(char**));

    for (int i = 0; i < rootCount; i++) {
        int rootIndex = rootIndices[i];
        int colSize = 1; // Start with name column
        EmailNode* currentEmail = accountMap[rootIndex].emails;
        while (currentEmail != NULL) {
            colSize++;
            currentEmail = currentEmail->next;
        }
        (*returnColumnSizes)[i] = colSize;
        result[i] = (char**)malloc(colSize * sizeof(char*));
        result[i][0] = accountMap[rootIndex].name;
        
        currentEmail = accountMap[rootIndex].emails;
        int emailIndex = 1;
        while (currentEmail != NULL) {
            result[i][emailIndex++] = currentEmail->email;
            currentEmail = currentEmail->next;
        }
    }

    // Free allocated memory
    for (int i = 0; i < accountCount; i++) {
        EmailNode* currentEmail = accountMap[i].emails;
        while (currentEmail != NULL) {
            EmailNode* nextEmail = currentEmail->next;
            free(currentEmail);
            currentEmail = nextEmail;
        }
    }
    free(accountMap);
    
    return result;
}
