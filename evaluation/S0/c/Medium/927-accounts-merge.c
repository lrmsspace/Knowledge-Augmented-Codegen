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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** accountsMerge(char*** accounts, int accountsSize, int* accountsColSize, int* returnSize, int** returnColumnSizes) {
    // Union-Find Data Structure
    typedef struct {
        int parent;
        int rank;
    } UF;

    UF uf[10000];
    for (int i = 0; i < 10000; i++) {
        uf[i].parent = i;
        uf[i].rank = 0;
    }

    int find(int x) {
        if (uf[x].parent != x) {
            uf[x].parent = find(uf[x].parent);
        }
        return uf[x].parent;
    }

    void unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (uf[rootX].rank < uf[rootY].rank) {
                uf[rootX].parent = rootY;
            } else if (uf[rootX].rank > uf[rootY].rank) {
                uf[rootY].parent = rootX;
            } else {
                uf[rootY].parent = rootX;
                uf[rootX].rank++;
            }
        }
    }

    // Map email to index and name
    typedef struct EmailNode {
        char* email;
        int index;
        struct EmailNode* next;
    } EmailNode;

    EmailNode* emailMap[10000] = {0};
    int emailCount = 0;

    for (int i = 0; i < accountsSize; i++) {
        char* name = accounts[i][0];
        for (int j = 1; j < accountsColSize[i]; j++) {
            char* email = accounts[i][j];
            EmailNode* node = emailMap[hash(email) % 10000];
            int found = 0;
            while (node) {
                if (strcmp(node->email, email) == 0) {
                    unionSet(i, node->index);
                    found = 1;
                    break;
                }
                node = node->next;
            }
            if (!found) {
                EmailNode* newNode = malloc(sizeof(EmailNode));
                newNode->email = email;
                newNode->index = i;
                newNode->next = emailMap[hash(email) % 10000];
                emailMap[hash(email) % 10000] = newNode;
            }
        }
    }

    // Collect merged accounts
    // ...      
    // Free email map
    for (int i = 0; i < 10000; i++) {
        EmailNode* node = emailMap[i];
        while (node) {
            EmailNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    return result;
}
