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
// - Disjoint Set Union (ds, linked-list, union-find, dfs)
//   • When to use: Use when you need to maintain a collection of disjoint sets and perform union operations to merge sets or find the representative of an element's set efficiently. It's suitable for problems involving dynamic connectivity or grouping elements.
//   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. It achieves nearly constant time complexity for these operations with path compression and union by rank/size optimizations.
//   • Invariants: Every element `i` belongs to exactly one set, represented by `find(i)`.; If `parent[i] == i`, then `i` is the representative (root) of its set.
//   • Tips: Implement path compression in `find` for optimal performance.; Use union by size or rank to maintain balanced trees.
//   • Pitfalls: Omitting path compression or union by rank/size can degrade performance to O(N).; Failing to correctly update auxiliary data stored at representatives during a union operation.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Finding Bridges Online (graph, ds, union-find, counting)
//   • When to use: Use when edges are added one by one to an initially empty graph and you need to efficiently track the number of bridges or 2-edge-connected components after each addition.
//   • Idea: This algorithm dynamically maintains the number of bridges in an undirected graph as edges are added incrementally. It leverages a Disjoint Set Union (DSU) data structure to achieve an amortized time complexity of O((N+M) log N).
//   • Invariants: Each DSU set represents a 2-edge-connected component or a collection of such components connected by bridges.; The total count of bridges accurately reflects edges whose removal increases connected components.
//   • Tips: Understand the properties of 2-edge-connected components and how they relate to bridges.; Carefully manage DSU operations, including path compression and union by rank/size, for optimal performance.
//   • Pitfalls: Incorrectly updating the bridge count after an edge addition, especially when cycles are formed.; Inefficient DSU operations leading to a higher than expected time complexity.
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
    typedef struct {
        int parent;
        int rank;
    } DSU;

    DSU* dsu = (DSU*)malloc(accountsSize * sizeof(DSU));
    for (int i = 0; i < accountsSize; i++) {
        dsu[i].parent = i;
        dsu[i].rank = 0;
    }

    int find(int x) {
        if (dsu[x].parent != x) {
            dsu[x].parent = find(dsu[x].parent);
        }
        return dsu[x].parent;
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (dsu[rootX].rank < dsu[rootY].rank) {
                dsu[rootX].parent = rootY;
            } else if (dsu[rootX].rank > dsu[rootY].rank) {
                dsu[rootY].parent = rootX;
            } else {
                dsu[rootY].parent = rootX;
                dsu[rootX].rank++;
            }
        }
    }

    typedef struct EmailNode {
        char* email;
        int accountIndex;
        struct EmailNode* next;
    } EmailNode;

    #define HASH_SIZE 10007

    EmailNode* hashTable[HASH_SIZE] = {0};

    unsigned int hash(const char* str) {
        unsigned int hash = 5381;
        int c;
        while ((c = *str++)) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash % HASH_SIZE;
    }

    for (int i = 0; i < accountsSize; i++) {
        for (int j = 1; j < accountsColSize[i]; j++) {
            char* email = accounts[i][j];
            unsigned int h = hash(email);
            EmailNode* node = hashTable[h];
            int found = 0;
            while (node) {
                if (strcmp(node->email, email) == 0) {
                    unionSets(i, node->accountIndex);
                    found = 1;
                    break;
                }
                node = node->next;
            }
            if (!found) {
                EmailNode* newNode = (EmailNode*)malloc(sizeof(EmailNode));
                newNode->email = email;
                newNode->accountIndex = i;
                newNode->next = hashTable[h];
                hashTable[h] = newNode;
            }
        }
    }
    // Group emails by root account
    typedef struct EmailList {
        char** emails;
        int size;
        int capacity;
    } EmailList;
    EmailList* emailLists = (EmailList*)malloc(accountsSize * sizeof(EmailList));
    for (int i = 0; i < accountsSize; i++) {
        emailLists[i].emails = (char**)malloc(10 * sizeof(char*));
        emailLists[i].size = 0;
        emailLists[i].capacity = 10;
    }
    for (int i = 0; i < HASH_SIZE; i++) {
        EmailNode* node = hashTable[i];
        while (node) {
            int root = find(node->accountIndex);
            if (emailLists[root].size >= emailLists[root].capacity) {
                emailLists[root].capacity *= 2;
                emailLists[root].emails = (char**)realloc(emailLists[root].emails, emailLists[root].capacity * sizeof(char*));
            }
            emailLists[root].emails[emailLists[root].size++] = node->email;
            node = node->next;
        }
    }
    // Prepare result
    char*** result = (char***)malloc(accountsSize * sizeof(char**));
    *returnColumnSizes = (int*)malloc(accountsSize * sizeof(int));
    int resultCount = 0;
    for (int i = 0; i < accountsSize; i++) {
        if (emailLists[i].size > 0) {
            // Sort emails
            qsort(emailLists[i].emails, emailLists[i].size, sizeof(char*), (int (*)(const void*, const void*))strcmp);
            // Remove duplicates
            int uniqueCount = 1;
            for (int j = 1; j < emailLists[i].size; j++) {
                if (strcmp(emailLists[i].emails[j], emailLists[i].emails[j - 1]) != 0) {
                    emailLists[i].emails[uniqueCount++] = emailLists[i].emails[j];
                }
            }
            // Prepare account entry
            result[resultCount] = (char**)malloc((uniqueCount + 1) * sizeof(char*));
            result[resultCount][0] = accounts[i][0]; // Name
            for (int j = 0; j < uniqueCount; j++) {
                result[resultCount][j + 1] = emailLists[i].emails[j];
            }
            (*returnColumnSizes)[resultCount] = uniqueCount + 1;
            resultCount++;
        }
    }
    *returnSize = resultCount;
    // Free memory
    for (int i = 0; i < accountsSize; i++) {
        free(emailLists[i].emails);
    }
    free(emailLists);
    for (int i = 0; i < HASH_SIZE; i++) {
        EmailNode* node = hashTable[i];
        while (node) {
            EmailNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(dsu);
    return result;
}
